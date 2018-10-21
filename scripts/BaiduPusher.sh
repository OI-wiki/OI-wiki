#!/usr/bin/env bash
source /etc/profile
ORG=24OI
REPO=OI-wiki
# Baidu Pusher 

# Sitemap Parser
pip install bs4
python scripts/Sitemap_Parser.py

cd site
#Use Curl
head='http://data.zz.baidu.com/urls?site='
tokenhead='&token='
URL=$head$site$tokenhead$BaiduToken
curl -H 'Content-Type:text/plain' --data-binary @sitemap.txt "$URL"

