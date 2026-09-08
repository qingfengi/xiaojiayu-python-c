# -*- coding: utf-8 -*-
"""Dump 鱼C-小甲鱼 (mid 314076440) full video list + collections to JSON."""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import bili_api as B  # noqa: E402

MID = 314076440
HERE = os.path.dirname(os.path.abspath(__file__))


def save(name, obj):
    path = os.path.join(HERE, name)
    with open(path, "w", encoding="utf-8") as f:
        json.dump(obj, f, ensure_ascii=False, indent=2)
    print(f"[saved] {name} ({len(obj) if isinstance(obj, list) else 'obj'})")


def main():
    vids = B.space_videos(MID, pages=80)
    save("all_videos.json", vids)
    print(f"total videos: {len(vids)}")

    seasons, series = B.collections(MID)
    detail = {"seasons": [], "series": []}
    for s in seasons:
        meta = s["meta"]
        arcs = B.season_archives(MID, meta["season_id"])
        detail["seasons"].append({"meta": meta, "archives": arcs})
        print(f"  season {meta['name']}: {len(arcs)}")
    for s in series:
        meta = s["meta"]
        arcs = B.series_archives(MID, meta["series_id"])
        detail["series"].append({"meta": meta, "archives": arcs})
        print(f"  series {meta['name']}: {len(arcs)}")
    save("collections_detail.json", detail)


if __name__ == "__main__":
    main()
