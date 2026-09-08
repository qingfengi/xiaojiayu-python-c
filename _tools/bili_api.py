# -*- coding: utf-8 -*-
"""Bilibili WBI-signed API helper for listing an uploader's videos/collections."""
import functools
import hashlib
import json
import sys
import time
import urllib.parse

import urllib.request

MIXIN_KEY_ENC_TAB = [
    46, 47, 18, 2, 53, 8, 23, 32, 15, 50, 10, 31, 58, 3, 45, 35, 27, 43, 5, 49,
    33, 9, 42, 19, 29, 28, 14, 39, 12, 38, 41, 13, 37, 48, 7, 16, 24, 55, 40,
    61, 26, 17, 0, 1, 60, 51, 30, 4, 22, 25, 54, 21, 56, 59, 6, 63, 57, 62, 11,
    36, 20, 34, 44, 52,
]

UA = ("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36")


def _open(url, referer="https://www.bilibili.com/", cookie=""):
    req = urllib.request.Request(url)
    req.add_header("User-Agent", UA)
    req.add_header("Referer", referer)
    req.add_header("Accept", "application/json, text/plain, */*")
    if cookie:
        req.add_header("Cookie", cookie)
    with urllib.request.urlopen(req, timeout=30) as resp:
        return json.loads(resp.read().decode("utf-8"))


def _get_mixin_key(orig: str) -> str:
    return "".join(orig[i] for i in MIXIN_KEY_ENC_TAB)[:32]


@functools.lru_cache(maxsize=1)
def _wbi_keys():
    data = _open("https://api.bilibili.com/x/web-interface/nav")
    img = data["data"]["wbi_img"]["img_url"].rsplit("/", 1)[1].split(".")[0]
    sub = data["data"]["wbi_img"]["sub_url"].rsplit("/", 1)[1].split(".")[0]
    return img, sub


def wbi_sign(params: dict) -> str:
    img, sub = _wbi_keys()
    mixin = _get_mixin_key(img + sub)
    params = dict(params)
    params["wts"] = int(time.time())
    items = sorted(params.items())
    query = urllib.parse.urlencode(
        [(k, "".join(c for c in str(v) if c not in "!'()*")) for k, v in items]
    )
    params["w_rid"] = hashlib.md5((query + mixin).encode()).hexdigest()
    return urllib.parse.urlencode(sorted(params.items()))


def space_videos(mid: int, keyword: str = "", pages: int = 40, cookie: str = ""):
    out = []
    for page in range(1, pages + 1):
        params = {
            "mid": mid, "ps": 30, "tid": 0, "pn": page,
            "keyword": keyword, "order": "pubdate",
            "platform": "web", "web_location": 1550101,
            "order_avoided": "true",
        }
        url = "https://api.bilibili.com/x/space/wbi/arc/search?" + wbi_sign(params)
        data = _open(url, f"https://space.bilibili.com/{mid}/video", cookie)
        if data.get("code") != 0:
            print(f"[warn] page {page}: code={data.get('code')} {data.get('message')}",
                  file=sys.stderr)
            break
        vlist = data["data"]["list"]["vlist"]
        if not vlist:
            break
        out.extend(vlist)
        total = data["data"]["page"]["count"]
        if len(out) >= total:
            break
        time.sleep(1.2)
    return out


def collections(mid: int, cookie: str = ""):
    seasons, series = [], []
    for page in range(1, 12):
        params = {"mid": mid, "page_num": page, "page_size": 20,
                  "web_location": 333.999}
        url = ("https://api.bilibili.com/x/polymer/web-space/seasons_series_list?"
               + wbi_sign(params))
        data = _open(url, f"https://space.bilibili.com/{mid}", cookie)
        if data.get("code") != 0:
            print(f"[warn] collections page {page}: {data.get('message')}",
                  file=sys.stderr)
            break
        lists = data["data"]["items_lists"]
        s1 = lists.get("seasons_list") or []
        s2 = lists.get("series_list") or []
        seasons.extend(s1)
        series.extend(s2)
        if not s1 and not s2:
            break
        time.sleep(1.2)
    return seasons, series


def season_archives(mid: int, season_id: int, cookie: str = ""):
    out = []
    for page in range(1, 30):
        params = {"mid": mid, "season_id": season_id, "sort_reverse": "false",
                  "page_num": page, "page_size": 30}
        url = ("https://api.bilibili.com/x/polymer/web-space/seasons_archives_list?"
               + wbi_sign(params))
        data = _open(url, f"https://space.bilibili.com/{mid}", cookie)
        if data.get("code") != 0:
            break
        arcs = data["data"].get("archives") or []
        if not arcs:
            break
        out.extend(arcs)
        if len(out) >= data["data"]["page"]["total"]:
            break
        time.sleep(1.0)
    return out


def series_archives(mid: int, series_id: int, cookie: str = ""):
    out = []
    for page in range(1, 30):
        url = (f"https://api.bilibili.com/x/series/archives?mid={mid}"
               f"&series_id={series_id}&only_normal=true&sort=asc"
               f"&pn={page}&ps=30")
        data = _open(url, f"https://space.bilibili.com/{mid}", cookie)
        if data.get("code") != 0:
            break
        arcs = data["data"].get("archives") or []
        if not arcs:
            break
        out.extend(arcs)
        if len(out) >= data["data"]["page"]["total"]:
            break
        time.sleep(1.0)
    return out


if __name__ == "__main__":
    mid = 314076440
    cookie = ""
    if len(sys.argv) > 1 and sys.argv[1] == "collections":
        seasons, series = collections(mid, cookie)
        print(json.dumps({"seasons": seasons, "series": series},
                         ensure_ascii=False, indent=2))
    else:
        kw = sys.argv[1] if len(sys.argv) > 1 else ""
        vids = space_videos(mid, kw, cookie=cookie)
        print(json.dumps(vids, ensure_ascii=False, indent=2))
