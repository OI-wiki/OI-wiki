"""Return the final redirect of a certain url
"""
from curl_cffi import requests

def finalRedirect(url):
	"""Return the address of url redirects(301/302).
	Returns the final URL as a string, or None if it cannot be determined.
	"""
		# follow redirects (max_redirs may be accepted by curl_cffi)
	try:
		resp = requests.get(url, allow_redirects=True, timeout=10)
		return resp.url
	except Exception as e:
		print(f"Exception: {str(e)}")
		return None

    