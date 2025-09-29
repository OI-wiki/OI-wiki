from curl_cffi import requests
from urllib.parse import quote
from datetime import datetime, timezone
import time

SAVE_URL = "https://web.archive.org/save/{}"

def retry_request(func, *args, retries=3, **kwargs):
    for attempt in range(retries):
        try:
            return func(*args, **kwargs)
        except Exception as e:
            if attempt == retries - 1:
                raise

def save(url):
    time.sleep(4)
    encoded_url = quote(url, safe='')
    save_link = SAVE_URL.format(encoded_url)
    print("Start Archiving: " + datetime.now(timezone.utc).isoformat())
    
    payload = {
        "url": url,
        "capture_all": "on",
        "capture_screenshot": "on",
    }

    save_content = retry_request(
        requests.post,
        save_link,
        data=payload,
        impersonate="chrome136",
        timeout=1800,
        allow_redirects=True,
    )
    print("End Archiving: " + datetime.now(timezone.utc).isoformat())
    if save_content.history:
        final_url = save_content.url
        return final_url
    # We cannot get the archivedLink. And archiveLink needs to take some time until it is shown in the sparkline. So we may need further update later.
    return None