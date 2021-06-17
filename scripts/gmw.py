import requests
import lxml
from bs4 import BeautifulSoup
import os
import re
import time

#光明日报URL形如 https://epaper.gmw.cn/gmrb/html/2021-06/17/nbs.D110000gmrb_01.htm
# epaper.gwm.cn/gmrb/html/年-月/日/...
# nbs.D110000gmrb_01.htm固定是第一版的URL
base_url = "https://epaper.gmw.cn/gmrb/html/"
base_url += time.strftime("%Y-%m/%d", time.localtime()) + '/'
# 以上就是今日报纸的索引

plate_index = requests.get(base_url + '/nbs.D110000gmrb_01.htm')
plate_index.encoding = "utf-8"
index_html = \
    str(BeautifulSoup(plate_index.text,'lxml').find_all('a', id='pageLink'))
index_html = index_html.split()

index = []

for i in index_html:
    if i[0:4] == "href":
        if i[6] == '.':
            index.append(base_url+i[8:-1])
        else:
            index.append(base_url+i[6:-1])
print(index)