#coding:utf-8
if __name__ == '__main__':
    import subprocess
    # subprocess.call("scrapy crawl 6v -o movies.json", shell=True)
    # subprocess.call("scrapy crawl 6v -o movies.xml", shell=True)
    subprocess.call("scrapy crawl 6v -o movies.csv", shell=True)
