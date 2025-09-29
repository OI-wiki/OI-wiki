import markdown
from bs4 import BeautifulSoup

# extension list should be align with mkdocs's extension list

md = markdown.Markdown(
    extensions=['admonition', 'def_list', 'footnotes', 'meta', 'toc', 
                'pymdownx.arithmatex', 'pymdownx.caret', 'pymdownx.critic',
                'pymdownx.details', 'pymdownx.emoji', 'pymdownx.highlight', 
                'pymdownx.inlinehilite', 'pymdownx.keys', 'pymdownx.magiclink',
                'pymdownx.mark', 'pymdownx.snippets', 'pymdownx.progressbar',
                'pymdownx.smartsymbols', 'pymdownx.superfences', 'pymdownx.tasklist',
                'pymdownx.tilde', 'pymdownx.tabbed'])


def extract_links(md_text):
    html = markdown.markdown(md_text, extensions=['admonition', 'def_list', 'footnotes', 'meta', 'toc', 
                'pymdownx.arithmatex', 'pymdownx.caret', 'pymdownx.critic', 'pymdownx.details', 
                'pymdownx.emoji', 'pymdownx.highlight', 'pymdownx.inlinehilite', 'pymdownx.keys',
                'pymdownx.magiclink', 'pymdownx.mark', 'pymdownx.snippets', 'pymdownx.progressbar',
                'pymdownx.smartsymbols', 'pymdownx.superfences', 'pymdownx.tasklist',
                'pymdownx.tilde', 'pymdownx.tabbed'])
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