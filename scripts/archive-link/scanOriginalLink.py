import json
from curl_cffi import requests

def readExistingFile(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        c = f.read()
    j = json.loads(c)
    return j
    
def retry_request(func, *args, retries=3, **kwargs):
    for attempt in range(retries):
        try:
            return func(*args, **kwargs)
        except Exception as e:
            if attempt == retries - 1:
                raise

def codeToStatus(status):
    """Generate the status of the website
    0: fail, 1: success, -1: unknown
    """
    if status == None:
        return 0
    if status == 403: #needs to know whether the server is banned
        return -1
    elif status == 429: # too many requests
        return -1
    elif status >= 400:
        return 0
    else:
        return 1

def detectURL(link):
    try:
        webContent = retry_request(requests.get, link, 
            impersonate="chrome136", timeout=15, verify=False) # 禁用ssl
        status = webContent.status_code
        return codeToStatus(status)
    except Exception as e:
        print("Exception: ", e)
        return -2 # Need to check later
    
def main():
    content = readExistingFile('archiveLink/data/data.json')
    updateContent = content
    cnt = 0
    tot = len(content)
    for key, value in content.items():
        if value["fail"] == True:
            continue
        cnt += 1
        status = detectURL(key)
        print(f"{cnt}/{tot}: Dealing with {key} with status {status}")
        updateContent[key]["status"] = status
        if status == 0:
            updateContent[key]["failTime"] = content[key]["failTime"] + 1
        if updateContent[key]["failTime"] >= 3:
            updateContent[key]["fail"] = True

    j = json.dumps(updateContent, indent=4, ensure_ascii=False)
    with open("archiveLink/data/data.json", "w", encoding="utf-8") as f:
        f.write(j)

if __name__ == '__main__':
    main()