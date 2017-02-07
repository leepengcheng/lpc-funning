#!/usr/bin/env python
# -*- encoding: utf-8 -*-
# Created on 2017-02-04 15:29:34
# Project: my6v

from pyspider.libs.base_handler import *


class Handler(BaseHandler):
    crawl_config = {
    }

    @every(minutes=24 * 60)
    def on_start(self):
        self.crawl('http://www.6vhao.net/', callback=self.index_page)

    @config(age=10 * 24 * 60 * 60)
    def index_page(self, response):
        for each in list(response.doc('div.menutv > ul >li > a').items())[1:3]:
            self.crawl(each.attr.href, callback=self.index_page1)
            
    @config(age=10 * 24 * 60 * 60)
    def index_page1(self, response):
        items=list(response.doc('div.pagebox > a[href]').items())
        last_url=items[-1].attr.href
        sum_page=int(last_url.split(".")[0].split("_")[1])
        self.crawl(response.url, callback=self.detail_page)
        for i in xrange(2,sum_page+1):
            url="%s/index_%s"%(response.url,i)
            self.crawl(url, callback=self.detail_page)

    @config(priority=3)
    def detail_page(self, response):
        return {
            "url": response.url,
            "title": response.doc('title').text(),
        }

    @catch_status_code_error  
    def callback(self, response):
        with open(r"d:\error.txt") as f:
            f.write(response.url)