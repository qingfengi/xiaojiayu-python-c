# -*- coding: utf-8 -*-
"""Batch downloader for 小甲鱼 (鱼C) B站 C语言 / Python courses.

Reads _tools/manifest.json and downloads every listed BV (all parts) into
its target directory, preferring HEVC video streams to save disk space.
Progress is tracked via yt-dlp's own download-archive, so re-running the
script resumes and skips finished parts.

Usage:
    python _tools/download.py                # download everything
    python _tools/download.py 01 03          # only groups whose dir starts with these prefixes
    python _tools/download.py --list         # dry-run, show the plan
"""
import json
import os
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
MANIFEST = os.path.join(HERE, "manifest.json")
ARCHIVE = os.path.join(HERE, "downloaded.txt")
COOKIE_FILE = os.path.join(HERE, "cookies.txt")

# winget's Gyan.FFmpeg install location (its shim dir is only on PATH for new shells)
FFMPEG_DIR = os.path.join(
    os.environ.get("LOCALAPPDATA", ""),
    "Microsoft", "WinGet", "Packages",
    "Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe",
    "ffmpeg-9.0.1-full_build", "bin",
)

UA = ("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36")

# Prefer HEVC (hev1) -> AV1 -> AVC, best available height, best m4a audio.
FORMAT = (
    "bestvideo[vcodec^=hev]+bestaudio/"
    "bestvideo[vcodec^=av01]+bestaudio/"
    "bestvideo+bestaudio/best"
)

BASE_ARGS = [
    sys.executable, "-m", "yt_dlp",
    "-f", FORMAT,
    "--merge-output-format", "mp4",
    "--download-archive", ARCHIVE,
    "--no-overwrites",
    "--continue",
    "--retries", "10",
    "--fragment-retries", "10",
    "--retry-sleep", "linear=2:30:3",
    "--sleep-requests", "1.5",
    "--sleep-interval", "2",
    "--max-sleep-interval", "5",
    "--concurrent-fragments", "4",
    "--write-subs",
    "--sub-langs", "all",
    "--write-thumbnail",
    "--write-info-json",
    "--embed-metadata",
    "--no-warnings",
    "--ignore-errors",
    "--newline",
    "--user-agent", UA,
    "--referer", "https://www.bilibili.com/",
    "--add-header", "Origin:https://www.bilibili.com",
    "--add-header", "Accept-Language:zh-CN,zh;q=0.9,en;q=0.8",
]

if os.path.isdir(FFMPEG_DIR):
    BASE_ARGS += ["--ffmpeg-location", FFMPEG_DIR]


def load():
    with open(MANIFEST, encoding="utf-8") as f:
        return json.load(f)


def target_dir(group, item):
    parts = [ROOT, "视频", group["dir"]]
    if item.get("sub"):
        parts.append(item["sub"])
    return os.path.join(*parts)


def run_one(group, item, dry=False):
    out = target_dir(group, item)
    tmpl = os.path.join(out, "%(playlist_index|1)03d-%(title)s.%(ext)s")
    url = f"https://www.bilibili.com/video/{item['bvid']}"
    cmd = list(BASE_ARGS) + ["-o", tmpl]
    if os.path.exists(COOKIE_FILE):
        cmd += ["--cookies", COOKIE_FILE]
    elif os.environ.get("BILI_BROWSER"):
        cmd += ["--cookies-from-browser", os.environ["BILI_BROWSER"]]
    cmd.append(url)

    print(f"\n=== {group['dir']} / {item.get('sub') or '-'} "
          f"[{item['bvid']}] {item['title']}", flush=True)
    print(f"    -> {out}", flush=True)
    if dry:
        return 0
    os.makedirs(out, exist_ok=True)

    # B站 throws HTTP 412 (risk control) on bursts; back off and retry.
    rc = 1
    for attempt in range(1, 4):
        proc = subprocess.run(cmd)
        rc = proc.returncode
        if rc == 0:
            break
        wait = 30 * attempt
        print(f"    [retry {attempt}/3] rc={rc}, sleeping {wait}s", flush=True)
        time.sleep(wait)
    return rc


def main():
    args = [a for a in sys.argv[1:]]
    dry = "--list" in args
    prefixes = [a for a in args if not a.startswith("--")]

    data = load()
    failures = []
    for group in data["groups"]:
        if prefixes and not any(group["dir"].startswith(p) for p in prefixes):
            continue
        for item in group["items"]:
            rc = run_one(group, item, dry)
            if rc != 0:
                failures.append(f"{group['dir']}/{item['bvid']} rc={rc}")
            if not dry:
                time.sleep(8)

    print("\n" + "=" * 60)
    if failures:
        print("FAILED / partial:")
        for f in failures:
            print("  " + f)
    else:
        print("all requested items processed")


if __name__ == "__main__":
    main()
