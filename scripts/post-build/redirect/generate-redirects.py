import os
f = open('site/_redirects')
nginx = open('site/redirect-nginx.conf', 'w')
for cur in f.readlines():
    s, t = cur.strip().split(' ')
    # s = s.rstrip('/') + '(\/?(index\.html)?)'
    # t = 'https://oi-wiki.org' + t + ';'
    # nginx.write('~' + s + ' ' + t + "\n")
    html_path = os.path.join('site', s.lstrip('/'), 'index.html')
    os.makedirs(os.path.dirname(html_path), exist_ok=True)
    with open(html_path, 'w') as html_file:
        html_file.write(f'<!DOCTYPE html><html><head><link rel="canonical" href="https://oi-wiki.org{t}"/><meta name="robots" content="noindex"><meta charset="utf-8" /><meta http-equiv="refresh" content="0; url={t}" /></head></html>')
