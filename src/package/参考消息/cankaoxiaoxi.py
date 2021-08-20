# Portions Copyright 2021 (c) Public Domain

import requests
import lxml
import os
from bs4 import BeautifulSoup
import sys
import  re
import time
import datetime

def get_news_list(base_url):
        end_of_news = True
        page_cnt = 1
        page_url = ""
        news_url = []
        while end_of_news:
                page_url = base_url + str(page_cnt) + ".shtml"
                # print(page_url)
                news_list_page = requests.get(page_url)
                news_list_page.encoding = "utf-8"
                news_list_page_html = BeautifulSoup(news_list_page.text,'lxml')
                news_list = news_list_page_html.find('ul',class_="txt-list-a fz-14 clear").find_all("li")
                yesterday_date =  (datetime.date.today() + datetime.timedelta(days=-1)).strftime("%Y-%m-%d")
                flag = False
                for i in news_list:
                        if i.find("a") == None:
                                continue
                        if str(i.find("span",class_="f-r arial cor999")).find(yesterday_date) == -1 and flag:
                                end_of_news = False
                                break
                        if str(i.find("span",class_="f-r arial cor999")).find(yesterday_date) == -1 or str(i.find("a")).find("photo") != -1:
                                continue
                        flag = True
                        # print("Found!")
                        now = str(i.find("a")).split('"')
                        result = ""
                        for j in now:
                                if j.find("http") != -1:
                                        result = str(j)
                                        break
                        news_url.append(result)
                        # print(result,news_url)
                page_cnt += 1
        # print(news_url)
        return news_url

def get_news(news_url):
        news = requests.get(news_url)
        news.encoding = "utf-8"
        news_page_details = BeautifulSoup(news.text,'lxml')
        news_title_html = str(news_page_details.find('h1'))
        news_html = str(news_page_details.find('div', class_='articleText'))
        if news_page_details.find('ul',class_='pageUl') != None:
                page_cnt = len( news_page_details.find('ul',class_='pageUl').find_all('li') ) - 3 + 1
        else:
                # print("single page",news_url)
                return {"title":news_title_html,"news":news_html}
        cnt = 2
        while cnt <= page_cnt:
                page = news_url[:-6] + "_" + str(cnt) + ".shtml"
                news = requests.get(page)
                # print(page+"\n")
                news.encoding = "utf-8"
                news_page_details = BeautifulSoup(news.text,'lxml')
                news_html += str(news_page_details.find('div', class_='articleText'))
                cnt += 1
        return {"title":news_title_html,"news":news_html}

# 该函数用于删除字符串中的所有html标签
def delete_html_tag(string):
        ex = "<(\\S*?)*[^>]*>.*?|<.*? />"
        return re.sub(ex,"",string)

# 将新闻写入文件
def write_into_file(file_name,title,article):
        file = open(sys.path[0]+"/result/"+file_name,"w+")
        file.write(title)
        file.write("\n")
        file.write(article)
        file.close()

# ----------以下为主程序----------

os.system("rm -rf result")
os.mkdir("result")

news_list_url = "http://www.cankaoxiaoxi.com/roll/"
news_url = get_news_list(news_list_url)

if len(news_url) == 0:
        print("<参考消息今日未发布新闻>")

for i in news_url:
        news = get_news(i)
        # 删除标签及正文中的html标签
        news["title"] = delete_html_tag(news["title"])
        news["news"] = delete_html_tag(news["news"])
        filename = time.strftime("%Y-%m-%d", time.localtime())+"\\参考消息\\"+news["title"]+".txt"
        write_into_file(filename, news["title"], news["news"])
        print("已获取<参考消息>:",news["title"])
