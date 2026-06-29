# Find related files to conduct correctness check and undefined behavior checks.
# input: changed files (from tj-actions/changed-files, read from res.txt)
# output: related files to test (write to $GITHUB_OUTPUT, access by setting env to the output and with os.environ.get())

import os

def get_files_to_test(filenames):
    mainfiles_to_test = set()
    mainfiles, auxfiles, examples, skiptest = [], [], [], []

    for filename in filenames:
        dirname, basename, extname = os.path.dirname(filename), os.path.splitext(os.path.basename(filename))[0], os.path.splitext(filename)[1]
        
        if extname.endswith('.cpp'):
            mainfile = os.path.normpath(os.path.join(dirname, basename.split('.')[0] + '.cpp'))
            if mainfile in mainfiles_to_test:
                continue
            else:
                mainfiles_to_test.add(mainfile)
            temp_auxfiles = []
            for root, _, files in os.walk(dirname):
                for file in files:
                    if file.split('.')[0] == basename.split('.')[0] and file.endswith('.cpp'):
                        temp_auxfiles.append(os.path.normpath(os.path.join(root, file)))
            temp_examples = []
            for root, _, files in os.walk(dirname.replace('code', 'examples')):
                for file in files:
                    if file.split('.')[0] == basename.split('.')[0] and file.endswith('.in') and os.path.exists(os.path.join(root, file.replace('.in', '.ans'))):
                        temp_examples.append(os.path.normpath(os.path.join(root, file)))
            
        elif extname.endswith(('.in', '.ans')):
            mainfile = os.path.normpath(os.path.join(dirname.replace('examples', 'code'), basename.split('.')[0] + '.cpp'))
            if mainfile in mainfiles_to_test:
                continue
            else:
                mainfiles_to_test.add(mainfile)
            temp_auxfiles = []
            for root, _, files in os.walk(dirname.replace('examples', 'code')):
                for file in files:
                    if file.split('.')[0] == basename.split('.')[0] and file.endswith('.cpp'):
                        temp_auxfiles.append(os.path.normpath(os.path.join(root, file)))
            temp_examples = [os.path.normpath(os.path.join(dirname, basename + '.in'))]

        temp_skiptest = False
        if os.path.exists(os.path.join(dirname, basename + '.skip_test')):
            temp_skiptest = True
        
        mainfiles.append(mainfile)
        auxfiles.append(temp_auxfiles)
        examples.append(temp_examples)
        skiptest.append(temp_skiptest)
        with open(os.environ.get("GITHUB_OUTPUT"), 'w') as f:
            print(f'mainfiles={mainfiles}, auxfiles={auxfiles}, examples={examples}, skiptest={skiptest}')
            f.write(f'files_to_test={(mainfiles, auxfiles, examples, skiptest)}')

with open("res.txt") as file_object:
    lines = file_object.readlines()
changed_files = [name for line in lines for name in line.split()]
get_files_to_test(changed_files)
