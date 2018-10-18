# Sitemap Parser - Convert XML into TXT (Baidu Pusher)
from bs4 import BeautifulSoup as bs
filename = '../site/sitemap.xml'
f = open(filename)
file = f.read()
soup = bs(file, "html.parser")
links = soup.find_all('loc')
with open('../site/sitemap.txt','w') as f1: 
    for link in links:
        f1.write(link.text + '\n')


