#!/usr/bin/env bash
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=24OI
REPO=OI-wiki
# This probably should match an email for one of your users.
EMAIL=sirius.caffrey@gmail.com

set -e

# Clone Theme for Editing
if [ ! -d "mkdocs-material" ] ; then
  git clone --depth 1 https://github.com/squidfunk/mkdocs-material.git
  sed -i '9a\<meta http-equiv="x-dns-prefetch-control" content="on">\n\<link rel="dns-prefetch" href="//fonts.loli.net">\n\<link rel="dns-prefetch" href="//cdn.bootcss.com">\n\<link rel="dns-prefetch" href="//unpkg.com">\n\<link rel="dns-prefetch" href="//npmcdn.com">\n\<link rel="dns-prefetch" href="//oi-wiki.org">\n\<link rel="dns-prefetch" href="//api.github.com">\n\<link rel="dns-prefetch" href="//www.google-analytics.com">' mkdocs-material/material/base.html
fi
sed -i "s/name: 'material'/name: null\n  custom_dir: 'mkdocs-material\/material'\n  static_templates:\n    - 404.html/g" mkdocs.yml
sed -i "s/- 'https:\/\/cdn.bootcss.com\/mathjax\/2.7.2\/MathJax.js?config=TeX-MML-AM_CHTML'//g" mkdocs.yml 


# Change Google CDN to loli.net
sed -i 's/fonts.gstatic.com/gstatic.loli.net/g' mkdocs-material/material/base.html
sed -i 's/fonts.googleapis.com/fonts.loli.net/g' mkdocs-material/material/base.html
# sed -i 's/script/script data-no-instant/g' mkdocs-material/material/base.html
# sed -i 's/<head>/<head data-no-instant>/g' mkdocs-material/material/base.html
sed -i 's/{{ page.content }}/{% set pagetime = config.extra.pagetime %} {% if page and page.meta and page.meta.pagetime is string %} {% set pagetime = page.meta.pagetime %} {% endif %}{% if pagetime %}<blockquote class="page-time"><\/blockquote>{% endif %}\n                {{ page.content }}/g' mkdocs-material/material/base.html
cp ./static/disqus.html mkdocs-material/material/partials/integrations/disqus.html
cp ./static/footer.html mkdocs-material/material/partials/footer.html

mv ./mkdocs-material/material/partials/language/zh.html ./mkdocs-material/material/partials/language/zh-Hans.html
cp ./static/extra.js docs/_static/js/extra.js 

mkdocs build -v

node render_math.js
