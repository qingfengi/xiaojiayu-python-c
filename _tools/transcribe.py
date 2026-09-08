# -*- coding: utf-8 -*-
"""Driver: for each video, run transcribe_worker.py as a separate process
with a hard timeout. On success, verify md, then delete the source mp4.
Fully resumable via transcribed.txt.
"""
import glob
import os
import re
import subprocess
import sys
import time

ROOT = r"F:\小甲鱼"
VIDEO = os.path.join(ROOT, "视频")
OUT = os.path.join(ROOT, "文字稿")
LOG = os.path.join(ROOT, "_tools", "transcribe.log")
DONE = os.path.join(ROOT, "_tools", "transcribed.txt")
WORKER = os.path.join(ROOT, "_tools", "transcribe_worker.py")
PY = os.path.join(ROOT, "_venv", "Scripts", "python.exe")

# per-video wall clock cap; medium model on 5070Ti transcribes 10-min clip in ~1-2 min
TIMEOUT = 25 * 60


def log(msg):
    line = f"[{time.strftime('%H:%M:%S')}] {msg}"
    print(line, flush=True)
    with open(LOG, "a", encoding="utf-8") as f:
        f.write(line + "\n")


def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--shards", type=int, default=1, help="并行分片总数")
    ap.add_argument("--shard-index", type=int, default=0, help="当前分片 0..shards-1")
    ap.add_argument("--model", default="medium")
    args = ap.parse_args()

    os.makedirs(os.path.dirname(LOG), exist_ok=True)
    done = set()
    if os.path.exists(DONE):
        with open(DONE, encoding="utf-8") as f:
            done = {x.strip() for x in f if x.strip()}

    targets = sorted(
        os.path.join(dp, f) for dp, _, fs in os.walk(VIDEO) for f in fs
        if f.lower().endswith(".mp4") and not re.search(r"\.f\d{3,}\.mp4$", f))
    todo = [p for p in targets if os.path.normcase(p) not in done]
    # shard partition: each instance takes files with index % shards == shard_index
    todo = [p for i_, p in enumerate(todo) if i_ % args.shards == args.shard_index]
    log(f"[shard {args.shard_index}/{args.shards}] "
        f"total={len(targets)}  todo={len(todo)}")

    for i, src in enumerate(todo, 1):
        rel = os.path.relpath(src, VIDEO)
        base = os.path.splitext(os.path.basename(src))[0]
        out_dir = os.path.join(OUT, os.path.dirname(rel))
        md_path = os.path.join(out_dir, base + ".md")

        if os.path.exists(md_path) and not os.path.exists(src):
            with open(DONE, "a", encoding="utf-8") as f:
                f.write(os.path.normcase(src) + "\n")
            continue

        log(f"[{i}/{len(todo)}] {rel}")
        t0 = time.time()
        try:
            env = dict(os.environ)
            env["PYTHONIOENCODING"] = "utf-8"
            proc = subprocess.run(
                [PY, "-u", WORKER, src, out_dir],
                capture_output=True, text=True, encoding="utf-8",
                errors="replace", env=env, timeout=TIMEOUT)
            took = time.time() - t0
            ok = proc.returncode == 0 and os.path.exists(md_path)
            tail = ((proc.stdout or "").strip().splitlines() or ["?"])[-1][:120]
            if ok:
                log(f"    OK  ({took:.0f}s)  {tail}")
                try:
                    os.remove(src)
                except OSError as e:
                    log(f"    note: could not delete video: {e}")
                with open(DONE, "a", encoding="utf-8") as f:
                    f.write(os.path.normcase(src) + "\n")
            else:
                err = ((proc.stderr or "").strip().splitlines() or ["?"])[-1][:250]
                log(f"    FAIL rc={proc.returncode} ({took:.0f}s)  {err}")
        except subprocess.TimeoutExpired:
            log(f"    TIMEOUT > {TIMEOUT//60}min — 跳过：{base}")
            # leave the file; user can retry later
        except Exception as e:
            import traceback
            log(f"    EXC {type(e).__name__}: {e}\n{traceback.format_exc()}")

    log("ALL DONE")


if __name__ == "__main__":
    main()
