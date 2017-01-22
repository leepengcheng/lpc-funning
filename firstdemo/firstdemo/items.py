# -*- coding: utf-8 -*-
import scrapy
from scrapy.loader.processors import Compose

class movieItem(scrapy.Item):
    # define the fields for your item here like:
    name = scrapy.Field(output_processor=Compose(lambda x:x[0].strip().strip("【】")))
    category=scrapy.Field()
    score=scrapy.Field()
    link =scrapy.Field()
