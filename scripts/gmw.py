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
title = []

for i in index_html:
    if i[0:4] == "href":
        if i[6] == '.':
            index.append(base_url+i[8:-1])
            title.append(i[8:-1])
        else:
            index.append(base_url+i[6:-1])
            title.append(i[6:-1])
# 完成一级跳转

head = {'User-Agent': \
'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.101 Safari/537.36'}
num = 1
cnt = 0 
for i in index:
    for j in range(0,2):
        os.system(f"wget {str(i)} -o temp.temp")
    tempin = open(f"{title[cnt]}", mode='r')
    temple = tempin.read()
    tempin.close()
    article_html = \
        str(BeautifulSoup(str(temple),'lxml').find_all('div', class_='text_c'))
    # 此处的 <div class="text_c"> 是整片文章（标题作者正文）
    # 因为我懒得把标题和正文分开就这样做了
    ex = "<(\S*?)*[^>]*>.*?|<.*? />" # 删除所有html标签
    article_html = re.sub(ex,"",article_html)
    # 写入文件
    file = open(f"gmw{num}.txt", mode='w')
    file.write(article_html)
    file.close()
    num+=1
    cnt+=1
os.system("rm temp.temp")