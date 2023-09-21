from glob import glob


def getUriSet(root: str):
    return set(glob("**/*.html", root_dir=root, recursive=True))


oldSet = getUriSet("old-site")
newSet = getUriSet("site")
if not newSet.issuperset(oldSet):
    print(f"Some pages are missing in new site, please update docs/_redirects")
    for p in oldSet - newSet:
        print(p)
    exit(1)
