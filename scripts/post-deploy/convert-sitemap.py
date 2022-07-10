# Sitemap Parser - Convert XML into TXT (Baidu Pusher)
# python3 convert-sitemap.py <input.xml> <output.txt>

import sys
from bs4 import BeautifulSoup as bs

f = open(sys.argv[1])
file = f.read()
soup = bs(file, "html.parser")
links = soup.find_all('loc')
with open(sys.argv[2], 'w') as f1:
    for link in links:
        f1.write(link.text + '\n')
