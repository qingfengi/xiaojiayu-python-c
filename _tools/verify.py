# -*- coding: utf-8 -*-
"""Verify downloaded parts vs manifest expectations."""
import glob
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

sys.path.insert(0, HERE)

EXPECTED = {
    "BV1mK411n7vn": 1, "BV17s411N78s": 61, "BV1Pz4y1B7uZ": 2,
    "BV1Ws411N7JC": 7, "BV1c4411e77t": 86, "BV1Fs411A7HZ": 97,
    "BV1oHrYYwEnu": 48, "BV1m14y1R7Fc": 4, "BV1wp411o7dz": 6,
    "BV1wp411o71g": 6, "BV1Ub411P7g8": 3, "BV1bs411N7ny": 10,
}

with open(os.path.join(HERE, "manifest.json"), encoding="utf-8") as f:
    data = json.load(f)

print(f"{'BV号':<15}{'目录':<38}{'已下':>5}{'应下':>6}")
missing = []
for g in data["groups"]:
    for it in g["items"]:
        d = os.path.join(ROOT, "视频", g["dir"], it.get("sub") or "")
        files = [p for p in glob.glob(os.path.join(d, "*.mp4"))
                 if not re.search(r"\.f\d{3,}\.mp4$", p)]
        exp = EXPECTED.get(it["bvid"], None)
        mark = ""
        if exp is not None and len(files) != exp:
            mark = "  <-- DIFF"
            missing.append((it["bvid"], g["dir"], it.get("sub"), len(files), exp))
        print(f"{it['bvid']:<15}{os.path.relpath(d, ROOT):<38}{len(files):>5}"
              f"{str(exp or '?'):>6}{mark}")

print()
if missing:
    print("部分缺失（多半因为B站412风控），稍后重跑 download.py 对应的组即可补齐：")
    for b, gd, sub, got, exp in missing:
        print(f"  {b}  {gd}/{sub or ''}  {got}/{exp}")
else:
    print("全部清单内的分P均已下载完成。")
