f = open('site/_redirects')
nginx = open('site/redirect-nginx.conf', 'w')
for cur in f.readlines():
    s, t = cur.strip().split(' ')
    s = s.rstrip('/') + '(\/?(index\.html)?)'
    t += ';'
    nginx.write('~' + s + ' ' + t + "\n")
