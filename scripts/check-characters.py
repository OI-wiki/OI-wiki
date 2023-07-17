import json
import os

def str_2_unicode(s):
    return s.encode('unicode-escape').decode()

class ChangeNeeded(Exception):
    pass

changed = False
change_list = {}
cjk_map = None

cjk_map = json.load(open('scripts/cjk-map.json'))

for line in open('res.txt'):
    for filename in line.split(' '):
        name = filename[:filename.rfind('.')]
        num = name.rfind('/')
        filename = name[num:]
        md = name + '.md'
        skiptest = name + '.skip_test'

        if os.path.exists(skiptest):
            print(md + ' test skipped')
            continue
        mdfile = open(md)
        data = mdfile.read()
        for key, value in cjk_map.items():
            if data.find(key) != -1:
                changed = True
                if md in change_list.keys():
                    change_list[md] += key
                else:
                    change_list[md] = key

if changed:
    print('Some CJK radicals are found in modified files. ')
    print(
        'You should replace the character before the arrow in the list below (sorted by filename) with the character after the arrow. '
    )
    print('')
    for change_file, change_data in change_list.items():
        print(f'- {change_file}')
        for change_char in change_data:
            print(
                f'  - {change_char} ({str_2_unicode(change_char)}) -> {cjk_map[change_char]} ({str_2_unicode(cjk_map[change_char])})'
            )
    print('')

    raise ChangeNeeded('Some characters need to be changed. ')