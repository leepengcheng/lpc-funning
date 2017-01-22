# encoding:utf-8
import scrapy
import re
from collections import deque
from firstdemo.items import movieItem
from scrapy.loader import ItemLoader


class My6vSpider(scrapy.Spider):
    name = "6v"
    # allowed_domains = ["6vhao"]
    start_urls = [
        "http://www.6vhao.net/",
    ]

    # 解析分类链接
    def parse(self, response):
        for sel in response.xpath("//div[@class='menutv']/ul/li/a"):
            category = sel.xpath('text()').extract_first()
            link = sel.xpath('@href').extract_first()
            if category != u"首页":
                yield scrapy.Request(link, self.parse_category)

    # 解析分类页链接
    def parse_category(self, response):
        for sel in response.xpath("//div[@class='Total record']/a[last()]"):
            link = sel.xpath("@href").extract_first()
            # pagenums=link.split("_")[1].split(".")[0]
            pagenums = int(re.search(".*_(\d+).html", link).group(1))
            nums = range(1, pagenums + 1)
            url_nums = deque(nums)
            url_nums.popleft()
            url_nums.appendleft('index')
            for num in url_nums:
                url = response.urljoin("index_%s.html" % num)
                yield scrapy.Request(url, self.parse_page)

    def parse_page(self, response):
        for sel in response.xpath("//div[@class='listInfo']/h3/a"):
            movie_link = sel.xpath('@href').extract_first()
            yield scrapy.Request(movie_link, self.parse_movie)

    def parse_movie(self, response):
        loader = ItemLoader(movieItem(), response=response)
        loader.add_xpath("name", "//div[@class='contentinfo']/h1/a/text()")
        loader.add_xpath("score", "//div[@id='text']/p[first()+1]")
        loader.add_value("link", response.url)
