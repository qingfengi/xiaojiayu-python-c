# -*- coding: utf-8 -*-
"""Merge leftover VIM fragments (video .f30xxxv + audio .f30280m4a) with ffmpeg."""
import glob
import os
import re
import subprocess
import sys

FFMPEG = os.path.join(
    os.environ.get("LOCALAPPDATA", ""),
    "Microsoft", "WinGet", "Packages",
    "Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe",
    "ffmpeg-9.0.1-full_build", "bin", "ffmpeg.exe")

VIM = r"C:\Users\xuqingfeng\Documents\Default Project\xiaojiayu\视频\01-C语言-带你学C带你飞\03-VIM快速入门"


def main():
    videos = sorted(
        p for p in glob.glob(os.path.join(VIM, "*.f3*.mp4")) if re.search(
            r"\.f3\d{4}\.mp4$", os.path.basename(p)))
    ok = 0
    for v in videos:
        base = re.sub(r"\.f3\d{4}\.mp4$", "", v)
        audio = base + ".f30280.m4a"
        out = base + ".mp4"
        if not os.path.exists(audio):
            print(f"[skip] no audio for {os.path.basename(v)}")
            continue
        if os.path.exists(out):
            os.remove(out)
        cmd = [FFMPEG, "-y", "-loglevel", "error",
               "-i", v, "-i", audio, "-c", "copy", out]
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode == 0:
            ok += 1
            os.remove(v)
            os.remove(audio)
            print(f"[ok] {os.path.basename(out)}")
        else:
            print(f"[fail] {os.path.basename(v)}: {r.stderr[:200]}")
    print(f"merged {ok}/{len(videos)}")


if __name__ == "__main__":
    sys.exit(main())
