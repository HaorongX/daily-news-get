import requests
import lxml
from bs4 import BeautifulSoup
import os
import  re

# 把今日谈上的“要闻”一栏的HTML爬下来
news_list_url = "https://news.gmw.cn/"
news_list_page = requests.get(news_list_url)
news_list_page.encoding = "utf-8"

# 接下来获取<ul class="title2_box">中的url(新闻)
news_list_page_details = BeautifulSoup(news_list_page.text,'lxml')
news_list_html = str(news_list_page_details.find_all('span', class_='newsTitle'))

temp = news_list_html.split()

print (18)

news_url = []

for i in temp:
    if i[0:4]=="href" and i[6:11]=="https":
        news_url.append(i[6:-1]) # 将要闻中新闻的url加到列表里

num = 1

print(news_url)

for i in news_url:
    # 爬下该篇新闻
    news = requests.get(i)
    news.encoding = "utf-8"
    news_page_details = BeautifulSoup(news.text,'lxml')
    # 获取内容&标题栏
    news_title_html = str(news_page_details.find_all('h1'))
    news_html = str(news_page_details.find_all('div', class_='u-mainText'))
    ex = "<(\S*?)*[^>]*>.*?|<.*? />" # 删除所有html标签
    news_title_html = re.sub(ex,"",news_title_html)
    news_html = re.sub(ex,"",news_html)
    # 写入文件
    file = open(f"gmw{num}.txt", mode='w')
    file.write(news_title_html[5:-6])
    file.write("\n\n\n")
    file.write(news_html)
    file.close()
    num+=1