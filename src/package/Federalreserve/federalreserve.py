# Portions Copyright 2021 (c) Public Domain

import requests
import lxml
from bs4 import BeautifulSoup
import os
import sys
import re
import time

# 该函数用于删除字符串中的所有html标签
def delete_html_tag(string):
    ex = "<(\\S*?)*[^>]*>.*?|<.*? />" # 用于选中HTML标签的正则
    return re.sub(ex,"",string) # 将string中被表达式ex选中的元素替换为空

# 将新闻写入文件
def write_into_file(file_name,title,article):
    file = open(sys.path[0]+"/result/"+file_name,"w+")
    file.write(title)
    file.write("\n")
    file.write(article)
    file.close()

def get_news_list(base_url):
    news_list_page = requests.get(base_url)
    news_list_page.encoding = "utf-8"  
    # 获取<p class="news news__title">中的url(新闻)
    news_list_page_details = BeautifulSoup(news_list_page.text,'lxml')
    news_list_html = news_list_page_details.find_all('p', class_='news news__title')
    news_list_temp = ""
    news_list_temp = str(news_list_html)
    temp = news_list_temp.split()
    NOTFOUND = -1
    news_url = []
    for i in temp:
        # 这个网站有个叫做什么“证词”的栏目，我觉得没啥用，就过滤掉了
        if i[0:4]=="href" and (i.find("testimony") == NOTFOUND):
            string = "https://www.federalreserve.gov"+i[6:]
            result = ""
            for j in string:
                if j == "\"":
                    break
                result+=j
            news_url.append(result) 
            # 将要闻中新闻的url加到列表里
            # 注意，这个网站的URL用的是相对路径，要手动把它的域名加上。
    return news_url

def get_news(news_url):
    news = requests.get(i)
    news.encoding = "utf-8"
    news_page_details = BeautifulSoup(news.text,'lxml')
    # 获取内容&标题栏
    news_title_html = str(news_page_details.find('h3', class_='title'))
    news_html = str(news_page_details.find('div', class_='col-xs-12 col-sm-8 col-md-8'))
    news_title_html = delete_html_tag(news_title_html)
    news_html = delete_html_tag(news_html)
    return {"title":news_title_html,"news":news_html}

# -------------------------

os.system("rm -rf result")
os.mkdir("result")

news_list = get_news_list("https://www.federalreserve.gov/newsevents.htm")

for i in news_list:
    news = get_news(i)
    filename = time.strftime("%Y-%b-%d", time.localtime())+"\\美联储\\"+news["title"]
    print("已获取<美联储新闻>:",news["title"]);
    write_into_file(filename, news["title"], news["news"])
