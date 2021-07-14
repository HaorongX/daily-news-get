# Portions Copyright 2021 (c) Public Domain

import requests
import lxml
from bs4 import BeautifulSoup
import os
import  re
import time
# 导入所需模块

# 获取新闻的URL列表
# 参数base_url为获取Top10新闻的页面链接
def get_news_list(base_url):
    news_list_page = requests.get(news_list_url) # 获取该页面
    news_list_page.encoding = "utf-8"
    news_list_page_html = BeautifulSoup(news_list_page.text,'lxml')
    # 经观察，今日谈的要闻一栏保存在一个列表中，且指向具体页面的链接在一对a标签中，其class属性为special1
    news_list = str(news_list_page_html.find_all('a', class_='special1'))
    # split 函数按空格将字符串进行切割，正好在<a href="xxx" ...>标签中，上下文与href间由一个空格隔开, 因此所有的要闻链接将被单独切割出来
    temp = news_list.split()
    news_url = [] # 用于存储新闻URL的列表
    for i in temp:
        if i[0:4]=="href": # 如果该元素存储的是链接
            # 字符串切片：从第7个字符截取到倒数第2个（-1是倒数第一个，不被截取）, 能正好截下链接部分
            news_url.append(i[6:-1])
    return news_url

# 获取具体新闻(HTML)
# 参数news_url为新闻的网址
def get_news(news_url):
    news = requests.get(news_url) # 先把新闻爬下来
    news.encoding = "utf-8"
    news_page_details = BeautifulSoup(news.text,'lxml')
    # 获取文章标题
    # 这个网站的新闻页面只有一个h1标签，其中就是新闻的标题
    news_title_html = str(news_page_details.find_all('h1'))
    # 该网站新闻的正文被包裹在一个class为detail_content的div标签中
    news_html = str(news_page_details.find_all('div', class_='detail_content'))
    # 请注意，由此获取的正文将包含很多HTML标签
    # 简而言之，此时正文任处在HTML格式
    return {"title":news_title_html,"news":news_html} # 返回一个包含新闻标题和内容的字典

# 该函数用于删除字符串中的所有html标签
def delete_html_tag(string):
    ex = "<(\\S*?)*[^>]*>.*?|<.*? />" # 用于选中HTML标签的正则
    return re.sub(ex,"",string) # 将string中被表达式ex选中的元素替换为空

# 将新闻写入文件
def write_into_file(file_name,title,article):
    file = open(file_name,"w")
    file.write(title)
    file.write("\n")
    file.write(article)
    file.close()

# ----------以下为主程序----------

news_list_url = "http://www.banyuetan.org/byt/jinritan/index.html"
news_url = get_news_list(news_list_url)

for i in news_url:
    news = get_news(i)
    # 删除标签及正文中的html标签
    news["title"] = delete_html_tag(news["title"])
    news["news"] = delete_html_tag(news["news"])
    filename = time.strftime("%Y-%b-%d", time.localtime())+"Banyuetan"+news["title"]
    write_into_file(filename, news["title"], news["news"])