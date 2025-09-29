"""Some websites have been blocked by web.archive.org.
This file saves the blacklist domains.
"""

blacklist = ["quora.com", "web.archive.org", "men.ci", "tristanpenman.com"]
graylist = ["zhihu.com", "loj.ac", "codeforces.com"]
# gray list is a list of websites that can be saved by web.archive.org but does not save contents

def inBlacklist(url, gray = True):
    """The function checks whether a certain url is in blacklist
    """
    for domain in blacklist:
        if domain in url:
            return True
    if gray == True:
        for domain in graylist:
            if domain in url:
                return True
    return False