from curl_cffi import requests

def retry_request(func, *args, retries=3, **kwargs):
    for attempt in range(retries):
        try:
            return func(*args, **kwargs)
        except Exception as e:
            if attempt == retries - 1:
                raise

def shortLink(url):
    urldata = {'url': url}
    try:
        shorten_link_data = retry_request(requests.post, 'https://d.00.mk/create', json=urldata)
        link = shorten_link_data.json().get('link')
        if link:
            return link
        else:
            print(f"No link returned for {key}: {shorten_link_data.text}")
            return None

    except Exception as e:
        return None