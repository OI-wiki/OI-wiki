import markdown
from bs4 import BeautifulSoup
import yaml
import re

# extension list should be align with mkdocs's extension list

with open('mkdocs.yml', mode='r', encoding='utf-8') as f:
    s = f.read()

s = re.sub(r'!!python/name:([^\s]+)', r'"\1"', s)
data = yaml.safe_load(s)
extensions = []
for d in data['markdown_extensions']:
    if isinstance(d, str):
        extensions.append(d)
    elif isinstance(d, dict):
        extensions = extensions + list(d.keys())


def extract_links(md_text):
    html = markdown.markdown(md_text, extensions=extensions)
    soup = BeautifulSoup(html, 'html.parser')
    links = []
    for a in soup.find_all('a'):
        href = a.get('href')
        if href and a['href'].startswith('http'):
            links.append(a['href'])
    return links


def main():
    pass


if __name__ == "__main__":
    main()
