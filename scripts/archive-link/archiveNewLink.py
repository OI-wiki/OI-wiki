import fetchurl
import json
from Service.ArchiveOrg.history import latest_snapshot
from Service.ArchiveOrg.create import save
from blacklist import inBlacklist
from redirect import finalRedirect
from shortLink import shortLink
from scanOriginalLink import detectURL

def readExistingFile(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        c = f.read()
    j = json.loads(c)
    return j

def getLatestFile(path):
    oiwikifetch = fetchurl.fetchurl(path)
    all_files =  oiwikifetch.fetchfiles()
    oiwikifetch.fetch()
    return oiwikifetch.url.link

def getArchiveLink(link):
    archiveLink = latest_snapshot(link)
    return archiveLink

def newLink(key, value):
    """
    key: the link
    value: a dict that have: file
    return value that must have: file, status, failTime, fail, archiveLink, shortArchiveLink
    """
    # deal with status, failTime, fail
    status = detectURL(key)
    value["status"] = status
    if status == 0:
        value["failTime"] = 1
    else:
        value["failTime"] = 0
    value["fail"] = False

    if inBlacklist(key) == True:
        # deal with archiveLink, shortArchiveLink
        value["archiveLink"] = None
        value["shortArchiveLink"] = None
        return value
    
    # deal with archiveLink, shortArchiveLink
    redirectUrl = finalRedirect(key)
    a = latest_snapshot(key)

    print(f"redirectUrl: {redirectUrl}")
    print(f"key: {key}")
    if redirectUrl != key:
        # web.archive.org saves the content in the redirectUrl
        b = latest_snapshot(redirectUrl)
    if a != None:
        value["archiveLink"] = a
    elif b != None:
        value["archiveLink"] = b
    else:
        # 该链接从未被存档
        print(f"Saving: {key}")
        save(key)
        value["archiveLink"] = None
        value["shortArchiveLink"] = None

    if value["archiveLink"] != None:
        value["shortArchiveLink"] = shortLink(value["archiveLink"])
    return value

def retryUnarchiveLink(data):
    """Some links has been archived for the first time 
    when it was added into the document.
    This function will try to fetch these links.
    """
    updateContent = data
    for key, data in data.items(): #content is a dict
        if data["archiveLink"] == None and inBlacklist(key) == False:
            print("deal with " + key)
            redirectUrl = finalRedirect(key)
            a = latest_snapshot(key)
            if redirectUrl != key:
                b = latest_snapshot(redirectUrl)
            if a != []:
                print(f"write a: {a}")
                updateContent[key]["archiveLink"] = a
            elif b != []:
                print(f"write b: {b}")
                updateContent[key]["archiveLink"] = b
    return updateContent

def main():
    pastContent = readExistingFile('archiveLink/data/data.json')
    pastContent = retryUnarchiveLink(pastContent)
    currentContent = getLatestFile("docs")
    updateContent = {}

    for key, value in currentContent.items():
        if key in pastContent:
        # 去除冗余链接，只保留文档里还存在的链接
            updateContent[key] = pastContent[key]
        elif key.startswith("http"):
            # 处理新增的链接
            print(f"New link: {key}")
            updateContent[key] = newLink(key, value)
                
    j = json.dumps(updateContent, indent=4, ensure_ascii=False)
    with open("archiveLink/data/data.json", "w", encoding="utf-8") as f:
        f.write(j)
    # print(j)

if __name__ == "__main__":
    main()