# -*- coding: utf-8 -*-
"""Smoke-test: transcribe ONE given video, print first lines, DO NOT delete."""
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

def main():
    src = sys.argv[1]
    model = WhisperModel(sys.argv[2] if len(sys.argv) > 2 else "small",
                         device="cuda", compute_type="int8_float16",
                         download_root=r"F:\小甲鱼\_models")
    segments, info = model.transcribe(
        src, language="zh", beam_size=5, vad_filter=True)
    print(f"lang={info.language} conf={info.language_probability:.2f} dur={info.duration:.0f}s")
    for i, s in enumerate(segments):
        print(f"[{s.start:7.1f}-{s.end:7.1f}] {s.text}")
        if i >= 12:
            print("...")
            break

if __name__ == "__main__":
    main()
