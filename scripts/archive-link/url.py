
class links:
    def __init__(self):
        self.link = {}
    
    def add(self, url, file):
        if url in self.link:
            if file not in self.link[url]: #一个文件中有多个相同的链接
                self.link[url]['file'].append(file)
        else:
            self.link[url] = {'file': [file]}

    def __str__(self):
        return str(self.link)