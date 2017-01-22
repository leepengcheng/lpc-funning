import scrapy
from scrapy.crawler import CrawlerProcess
from dirbot.spiders.dmoz import DmozSpider


process = CrawlerProcess({
    'USER_AGENT': 'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)'
})

process.crawl(DmozSpider)
process.start()
from scrapy.cmdline import execute
