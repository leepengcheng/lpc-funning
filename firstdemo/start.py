import scrapy
from scrapy.crawler import CrawlerProcess
from firstdemo.spiders.my6vspider import My6vSpider

process = CrawlerProcess({
    'USER_AGENT': 'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)'
})

process.crawl(My6vSpider)
process.start()

# from scrapy.cmdline import execute
# if __name__ == '__main__':
#     execute()