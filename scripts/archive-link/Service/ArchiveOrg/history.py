"""Generates the history snapshot in web.archive.org for a certain url
"""
from curl_cffi import requests
from urllib.parse import quote
from concurrent.futures import ThreadPoolExecutor, as_completed
import time

sparkline = "https://web.archive.org/__wb/sparkline?output=json&url="
detail = "https://web.archive.org/__wb/calendarcaptures/2?date={}&url={}"
archive_link = "https://web.archive.org/web/{}/{}"
referer_link = "https://web.archive.org/web/20250000000000*/{}"

def retry_request(func, *args, retries=3, **kwargs):
    for attempt in range(retries):
        try:
            return func(*args, **kwargs)
        except Exception as e:
            if attempt == retries - 1:
                raise

def latest_snapshot(url):
    """Get the latest snapshot of a certain url
    """
    time.sleep(4)
    encoded_url = quote(url, safe='')
    referer_url = referer_link.format(encoded_url)
    headers = {
        "Referer": referer_url
    }
    print(sparkline + encoded_url)
    # fetch sparkline (years list)
    try:
        page_sparkline = retry_request(
            requests.get,
            sparkline + encoded_url,
            impersonate="chrome136",
            headers=headers,
            timeout=15,
        )
        print(page_sparkline.content)
        print(page_sparkline.status_code)
        page_sparkline = page_sparkline.json()
        latest_ts = page_sparkline.get("last_ts", [])
        if latest_ts == None:
            return None
        else:
            return archive_link.format(latest_ts, url)
    except Exception as e:
        print(f"fail reason, {str(e)}")
        return None

def history_snapshot(url):
    """Get all the snapshots for a certain url.
    """
    time.sleep(4)
    encoded_url = quote(url, safe='')
    referer_url = referer_link.format(encoded_url)
    headers = {
        "Referer": referer_url
    }
    print(sparkline + encoded_url)
    # fetch sparkline (years list)
    page_sparkline = retry_request(
        requests.get,
        sparkline + encoded_url,
        impersonate="chrome136",
        headers=headers,
        timeout=15,
    )
    print(page_sparkline.content)
    print(page_sparkline.status_code)
    page_sparkline = page_sparkline.json()

    years = page_sparkline.get("years", [])
    snapshots = []

    # Parallelize requests for each year's detail to speed up overall fetch
    if not years:
        return snapshots

    max_workers = min(8, len(years))
    with ThreadPoolExecutor(max_workers=max_workers) as executor:
        future_to_year = {}
        for year in years:
            url_detail = detail.format(year, encoded_url)
            print(url_detail)
            # submit the retry_request wrapper so each task will retry on failure
            future = executor.submit(
                retry_request,
                requests.get,
                url_detail,
                impersonate="chrome136",
                headers=headers,
                timeout=15,
            )
            future_to_year[future] = year

        for future in as_completed(future_to_year):
            year = future_to_year[future]
            try:
                resp = future.result()
                year_detail = resp.json()
            except Exception:
                # skip this year on error and continue with others
                continue

            for item_time, status, times in year_detail.get("items", []): # times不是一天抓了几次
                if item_time < 1000000000: #date format: (M)MDDHHMMSS
                    item_time = "0" + str(item_time)
                exact_time = str(year) + str(item_time)
                snapshots.append({'url': int(exact_time),
                                  'link': archive_link.format(exact_time, url)})

    return snapshots
            
"""
{
    "items": [
        [
            101,
            301,
            2
        ]
    ]
}
"""