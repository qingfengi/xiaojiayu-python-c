# -*- coding: utf-8 -*-
"""Transcribe exactly one video; prints md path on success."""
import argparse
import glob
import os
import sys

VENV = os.path.join(r"F:\小甲鱼", "_venv")
for dll_dir in glob.glob(os.path.join(VENV, "Lib", "site-packages",
                                       "nvidia", "*", "bin")):
    if os.path.isdir(dll_dir):
        os.add_dll_directory(dll_dir)
        os.environ["PATH"] = dll_dir + os.pathsep + os.environ["PATH"]

from faster_whisper import WhisperModel

# worker writing into console pipes must never crash on emoji
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
sys.stderr.reconfigure(encoding="utf-8", errors="replace")


def fmt_ts(s):
    return f"{int(s//3600):02d}:{int(s%3600//60):02d}:{s%60:05.2f}"


def to_md(out_dir, title, dur, segments):
    os.makedirs(out_dir, exist_ok=True)
    path = os.path.join(out_dir, title + ".md")
    with open(path, "w", encoding="utf-8") as f:
        f.write(f"# {title}\n\n")
        f.write(f"> 时长 {int(dur//60)} 分 {int(dur%60)} 秒 ·"
                f" faster-whisper 自动转写\n\n---\n\n")
        buf, t0 = [], None
        for seg in segments:
            buf.append(seg.text.strip())
            if t0 is None:
                t0 = seg.start
            if (seg.end - t0 > 90) or (sum(len(x) for x in buf) > 400):
                f.write(f"（{fmt_ts(t0)}）" + " ".join(buf) + "\n\n")
                buf, t0 = [], None
        if buf:
            f.write(f"（{fmt_ts(t0)}）" + " ".join(buf) + "\n")
    return path


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("out_dir")
    ap.add_argument("--model", default="medium")
    args = ap.parse_args()

    model = WhisperModel(args.model, device="cuda", compute_type="int8_float16",
                         download_root=os.path.join(r"F:\小甲鱼", "_models"),
                         cpu_threads=8)
    segments, info = model.transcribe(
        args.src, language="zh", beam_size=5, vad_filter=True,
        vad_parameters={"min_silence_duration_ms": 500, "speech_pad_ms": 200})
    segs = list(segments)
    base = os.path.splitext(os.path.basename(args.src))[0]
    md = to_md(args.out_dir, base, info.duration, segs)
    try:
        shown = os.path.relpath(md)
    except ValueError:
        shown = os.path.basename(md)
    print(f"OK {shown} {len(segs)}", flush=True)


if __name__ == "__main__":
    sys.exit(main())
