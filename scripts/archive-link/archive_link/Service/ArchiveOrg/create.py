from curl_cffi import requests
from urllib.parse import quote
from datetime import datetime, timezone
from ratelimit import limits, sleep_and_retry
from archive_link.utils import retry_request

ONE_MINUTE = 60
SAVE_URL = "https://web.archive.org/save/{}"


@sleep_and_retry
@limits(calls=15, period=ONE_MINUTE)
def save(url):
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
    # We cannot get the archivedLink. And archiveLink needs to take some time
    # until it is shown in the sparkline. So we may need further update later.
    return None
