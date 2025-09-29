import fetchurl
import json
from Service.ArchiveOrg.history import latest_snapshot
from Service.ArchiveOrg.create import save
from blacklist import inBlacklist
import datetime

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

def is_older_than_days(ts_str, days=180):
    """ts_str 格式为 'YYYYmmddHHMMSS'（也可传 int），返回是否晚于 days 天之前（超过 days 天返回 True）。"""
    if not ts_str:
        return True
    s = str(ts_str)
    try:
        dt = datetime.datetime.strptime(s, "%Y%m%d%H%M%S")
    except Exception:
        return True
    return (datetime.datetime.now() - dt) > datetime.timedelta(days=days)

def get_timestamp():
    """返回形如 YYYYMMDDHHMMSS 的字符串
    """
    return datetime.datetime.now().strftime("%Y%m%d%H%M%S")

def links_to_be_saved(content, days=90):
    """获取需要存档的链接并存档
    """
    for key, value in content.items():
        if inBlacklist(key) == True:
            continue
        a = latest_snapshot(key)
        if a == None:
            print(f"network fail: {key}")
            continue
        try:
            latest_ts = int(a.split('/')[4])
            if is_older_than_days(latest_ts, days):
                save(key)
        except Exception as e:
            print(f"Error: {str(e)}")

def main():
    currentContent = getLatestFile("docs") # 默认是在OI-wiki根目录下调用执行
    currentTime = get_timestamp()
    links_to_be_saved(currentContent)
    endTime = get_timestamp()
    print("start time" + str(currentTime))
    print("end time", str(endTime))

if __name__ == "__main__":
    main()