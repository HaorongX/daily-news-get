# Portions Copyright 2021 (c) Public Domain

import requests
import lxml
from bs4 import BeautifulSoup
import os
import  re
import time

def get_news_list(base_url,headers):
    news_list_page = requests.get(base_url,headers=headers)
    news_list_page.encoding = "utf-8"
    news_list_page_html = BeautifulSoup(news_list_page.text,'lxml')

    news_list = str(news_list_page_html.find_all("h3",class_="rundown-segment__title"))

    news_url=[]
    news_list=news_list.split('"')
    for i in news_list:
        if i[0:4]=="http":
            # print(i,"\n")
            i = i.replace("\\","")
            news_url.append(i)
    return news_url

def get_news(news_url):
    news = requests.get(news_url)
    news.encoding = "utf-8"
    news_page_details = BeautifulSoup(news.text,'lxml')
    news_title_html = str(news_page_details.find_all('h1'))
    news_html = str(news_page_details.find_all('div', class_='storytext storylocation linkLocation'))
    news_html += str(news_page_details.find_all('div', class_='transcript storytext'))
    return {"title":news_title_html,"news":news_html}

# 该函数用于删除字符串中的所有html标签
def delete_html_tag(string):
    ex = "<(\\S*?)*[^>]*>.*?|<.*? />"
    return re.sub(ex,"",string)

# 将新闻写入文件
def write_into_file(file_name,title,article):
    file = open(file_name,"w")
    file.write(title)
    file.write("\n")
    file.write(article)
    file.close()

# ----------以下为主程序----------

header = {"User-Agent":"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.107 Safari/537.36"}

news_list_url = "https://www.npr.org/programs/morning-edition/"
news_url = get_news_list(news_list_url,header)

for i in news_url:
    news = get_news(i)
    # 删除标签及正文中的html标签
    news["title"] = delete_html_tag(news["title"])
    news["news"] = delete_html_tag(news["news"])
    filename = time.strftime("%Y-%b-%d", time.localtime())+"NPR"+news["title"]
    write_into_file(filename, news["title"], news["news"])
