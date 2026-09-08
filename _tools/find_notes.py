# -*- coding: utf-8 -*-
"""Search GitHub for 小甲鱼-related course notes / homework repos."""
import json
import urllib.parse
import urllib.request

QUERIES = [
    "小甲鱼 python",
    "小甲鱼 C语言",
    "零基础入门学习Python",
    "带你学C带你飞",
    "鱼C论坛",
    "零基础入门学习Python 作业",
    "小甲鱼 数据结构和算法",
    "鱼Cfork?",
    "python零基础入门学习Python课件",
]
for q in QUERIES:
    url = ("https://api.github.com/search/repositories?q=" +
           urllib.parse.quote(q) + "&sort=stars&per_page=8")
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    try:
        d = json.loads(urllib.request.urlopen(req, timeout=30).read())
        print("===", q)
        for it in d["items"]:
            desc = (it["description"] or "")[:100]
            print(f"  {it['stargazers_count']:>5}  {it['full_name']:<45} {desc}")
        print()
    except Exception as e:
        print("  ERR", q, e)
