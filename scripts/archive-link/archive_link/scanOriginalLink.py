import json
from curl_cffi import requests
from enum import Enum
from archive_link.utils import retry_request


class Web(Enum):
    FAIL = 0
    SUCCESS = 1
    UNKNOWN = -1
    REQUEST_FAIL = -2


def readExistingFile(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        c = f.read()
    j = json.loads(c)
    return j


def codeToStatus(status):
    """Generate the status of the website
    """
    if status is None:
        return Web.FAIL.value
    if status == 403:  # needs to know whether the server is banned
        return Web.UNKNOWN.value
    elif status == 429:  # too many requests
        return Web.UNKNOWN.value
    elif status >= 400:
        return Web.FAIL.value
    else:
        return Web.SUCCESS.value


def detectURL(link):
    try:
        webContent = retry_request(
            requests.get,
            link,
            impersonate="chrome136",
            timeout=15,
            verify=False)  # 禁用ssl
        status = webContent.status_code
        return codeToStatus(status)
    except Exception as e:
        print("Exception: ", e)
        return Web.REQUEST_FAIL.value  # Need to check later


def main(failTime=3):
    content = readExistingFile('data/data.json')
    updateContent = content
    cnt = 0
    tot = len(content)
    for key, value in content.items():
        if value["fail"]:
            continue
        cnt += 1
        status = detectURL(key)
        print(f"{cnt}/{tot}: Dealing with {key} with status {status}")
        updateContent[key]["status"] = status
        if status == Web.FAIL.value:
            updateContent[key]["failTime"] = content[key]["failTime"] + 1
        if updateContent[key]["failTime"] >= failTime:
            updateContent[key]["fail"] = True

    j = json.dumps(updateContent, indent=4, ensure_ascii=False)
    with open("data/data.json", "w", encoding="utf-8") as f:
        f.write(j)


if __name__ == '__main__':
    main()
