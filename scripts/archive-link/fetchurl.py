import os
import extracturl
from url import links

class fetchurl:
    def __init__(self, folder):
        self.folder = folder
        self.files = []
        self.url = links()
    
    def fetchfiles(self):
        """Get all the relative path of all files in the folder
        """
        files = os.walk(self.folder)
        for root, dirs, files in files:
            for file in files:
                if ".md" in file:
                    self.files.append(os.path.join(root, file))
        return self.files
        
    def fetchUrlFromFiles(self, file):
        """Get all the external urls from a given file
        """
        with open(file, "r", encoding="utf-8") as f:
            file_content = f.read()
        print("Deal with " + file)
        file_url = extracturl.extract_links(file_content)
        for url in file_url:
            self.url.add(url, file)

    def fetch(self):
        """Get all the external urls in all the files in the folder
        """
        for file in self.files:
            self.fetchUrlFromFiles(file)
        return self.url
