#!/usr/bin/env python3

if __name__ == '__main__':
    import sys
    import os

    try:
        import elaphure
    except ImportError:
        ROOT=os.path.dirname(os.path.abspath(__file__))
        sys.path.append(os.path.dirname(ROOT)+"/elaphure")

    import elaphure.__main__


TEMPLATE_DIRS = ['templates']
STATICFILES_DIRS = {'/static': 'static', '/': 'wiki'}
STATICFILES_EXCLUDE = ["*~", ".*"]

def author(filename, meta):
    slug = filename[8:-3]
    return {
        "type": "author",
        "slug": slug,
        "name": meta.get("name", [slug])[0],
        "emails": meta.get("email", [])}

def wiki(filename, meta):
    slug = filename[5:-3]
    return {
        "type": "wiki",
        "slug": slug,
        "title": meta.get("title", [slug])[0],
        "authors": meta.get("author", []),
        "tags": meta.get("tag", [])}

def prob(filename, meta):
    oj = os.path.dirname(filename[5:])
    pid = os.path.splitext(os.path.basename(filename))[0]
    slug = f"{oj}-{pid}"
    tags = meta.get("tag", [])
    if oj not in tags:
        tags = tags + [oj]

    return {
        "type": "wiki",
        "slug": slug,
        "title": slug + ": " + meta.get("title", [""])[0],
        "authors": meta.get("author", []),
        "tags": tags}


SOURCE_FILES = [
    ("authors/*.md", 'markdown', author),
    ("wiki/**/*.md", 'markdown', wiki),
    ("probs/**/*.md", 'markdown', prob)
]


URLS = Map([
    Rule(
        '/',
        defaults={'type': 'wiki', 'slug': 'index'},
        endpoint='wiki.html'),
    Rule(
        '/authors/',
        endpoint='authors.html'),
    Rule(
        '/authors/<slug>',
        defaults={'type': 'author'},
        endpoint='author.html'),
    Rule(
        '/<path:slug>',
        defaults={'type': 'wiki'},
        endpoint='wiki.html')])


def build_link(target, text=None):
    urls = URLS.bind("localhost", "/")

    if target.startswith("@"):
        url = urls.build('author.html', {'slug': target[1:]})
    else:
        url = urls.build('wiki.html', {'slug': target})

    if text is None:
        _, values = urls.match(url)
        entry = registry.find(values)
        if entry is None:
            warn("%s %r not found" % (
                "author" if target.startswith("@") else "wiki",
                target))
            text = target
        else:
            if values['type'] == 'author':
                text = entry["name"]
            else:
                text = entry["title"]

    return url, text

from markdown.extensions import Extension
from markdown.inlinepatterns import Pattern
from markdown.util import etree

class WikiLinkExtension(Extension):

    def extendMarkdown(self, md, md_globals):
        self.md = md
        WIKILINK_RE = r'\[\[(?P<target>[@\w/0-9:_ -]+)(?P<text>(?:\|[\w/0-9:_ -]+)?)\]\]'
        pattern = WikiLinks(WIKILINK_RE)
        pattern.md = md
        md.inlinePatterns.add('wikilink', pattern, "<not_strong")


class WikiLinks(Pattern):

    def handleMatch(self, m):
        target = m.group("target")
        text = m.group("text")
        text = text[1:] if text else None
        url, text = build_link(target, text)
        a = etree.Element('a')
        a.text = text
        a.set('href', url)
        return a



READERS = {
    'markdown': {
        'extensions':
        [ 'codehilite',
          'meta',
          WikiLinkExtension(),
          'tables',
          'pymdownx.arithmatex',
          'pymdownx.superfences',
        ],
        'extension_configs': {
            'codehilite': {
                'guess_lang': False,
                'linenums': True,
            },
            'pymdownx.arithmatex': {
                'generic': True,
            }
        }
    }
}

REGISTRIES = {
  'default': { 'name': 'dummy' }
}
