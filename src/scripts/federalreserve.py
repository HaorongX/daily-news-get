import requests
import lxml
from bs4 import BeautifulSoup
import os
import re

# 把“新闻稿”一栏的HTML爬下来
news_list_url = "https://www.federalreserve.gov/newsevents.htm"
news_list_page = requests.get(news_list_url)
news_list_page.encoding = "utf-8"

# 接下来获取<p class="news news__title">中的url(新闻)
news_list_page_details = BeautifulSoup(news_list_page.text,'lxml')
news_list_html = str(news_list_page_details.find_all('p', class_='news news__title'))

temp = news_list_html.split()

NOTFOUND = -1

news_url = []
for i in temp:
    if i[0:4]=="href" and (i.find("testimony") == NOTFOUND): # 那个啥证词就过滤掉吧，不要它了
        str = "https://www.federalreserve.gov"+i[6:]
        result = ""
        for j in str:
            if j == "\"":
                break
            result+=j
        news_url.append(result) 
        # 将要闻中新闻的url加到列表里
        # 注意，这个网站的URL用的是相对路径，要手动把它的域名加上。
del str

num = 1

for i in news_url:
    # 爬下该篇新闻
    news = requests.get(i)
    news.encoding = "utf-8"
    news_page_details = BeautifulSoup(news.text,'lxml')
    # 获取内容&标题栏
    news_title_html = str(news_page_details.find_all('h3', class_='title'))
    news_html = str(news_page_details.find_all('div', class_='col-xs-12 col-sm-8 col-md-8'))
    ex = "<(\S*?)*[^>]*>.*?|<.*? />" # 删除所有html标签
    news_title_html = re.sub(ex,"",news_title_html)
    news_html = re.sub(ex,"",news_html)
    # 写入文件
    file = open(f"fed{num}.txt", mode='w')
    file.write(news_title_html[19:-6])
    file.write("\n\n\n")
    file.write(news_html)
    file.close()
    num+=1