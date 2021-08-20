# 人民日报脚本
# 所需函数库

do './formatarticle.pl';
use LWP::UserAgent;
use POSIX qw(strftime);

# 变量初始化

$request = 0; # 创建一个全新的网络对象
$count_pages = 0; # 今日人民日报版面数

# 电脑时间获取

sub GetYear {
    strftime "%Y", localtime;
}

sub GetMouth {
    strftime "%m", localtime;
}

sub GetDay {
    strftime "%d", localtime;
}


# 页面获取准备

$request = LWP::UserAgent->new;
$request->timeout(3); # 超时时间为3秒

# 获取今日的人民日报版数

sub GetPagesCount {
    my $count = 0;
    my $url = 0; # 准备构造的URL
    my $year = &GetYear();
    my $mouth = &GetMouth();
    my $day = &GetDay();
    while (1)
    {
        $count++;
        # 人民日报在10版以前的页面都是 01 02 03
        # 不添加0的话 会直接获取失败 从而导致错误
        if ($count < 10)
        {
            $url = "http://paper.people.com.cn/rmrb/html/$year-$mouth/$day/nbs.D110000renmrb_0$count.htm";
        }
        else
        {
            $url = "http://paper.people.com.cn/rmrb/html/$year-$mouth/$day/nbs.D110000renmrb_$count.htm";
        }
        if (!$request->head($url)->is_success)
        {
            last;
        }
    }
    $count - 1; # 返回值
}

# 获取单篇页面上的文章数目
# 所需参数为人民日报版面

sub GetPageArticleCount {
    my $count = 0;
    my $url = 0;
    my $page = 0;
    my $year = &GetYear();
    my $mouth = &GetMouth();
    my $day = &GetDay();
    ($page) = @_;
    while (1)
    {
        $count++;
        # 人民日报在10版以前的页面都是 01 02 03
        # 不添加0的话 会直接获取失败 从而导致错误
        if ($page < 10)
        {
            $url = "http://paper.people.com.cn/rmrb/html/$year-$mouth/$day/nw.D110000renmrb_$year$mouth$day\_$count-0$page.htm";
        }
        else
        {
            $url = "http://paper.people.com.cn/rmrb/html/$year-$mouth/$day/nw.D110000renmrb_$year$mouth$day\_$count-$page.htm";
        }
        if (!$request->head($url)->is_success)
        {
            last;
        }
    }
    $count - 1;
}

# 获取单个页面的文章

sub GetSinglePageArticle {
    my %result = (
        'content' => undef,
        'title' => undef
        );
    my ($source) = undef;
    my $page_html = undef;
    my $page_tag1 = undef;
    my $page_tag2 = undef;
    my $page_title = undef;
    ($source) = @_;
    $page_html = $request->get($source)->content;
    $page_tag1 = index($page_html,"<title>") + length("<title>");
    $page_tag2 = index($page_html,"</title>");
    $page_title = substr($page_html,$page_tag1,$page_tag2 - $page_tag1);
    $page_tag1 = index($page_html,"<!--enpcontent-->");
    $page_tag2 = index($page_html,"<!--/enpcontent-->");
    $page_html = substr($page_html,$page_tag1,$page_tag2 - $page_tag1);
    $result{'content'} = FormatArticle($page_html);
    $result{'title'} = $page_title;
    %result;
}

# 写入文章内容到文件 保存

sub SaveArticleToFile {
    my ($filename, $content) = @_;
    unlink $filename;
    open(FILE, '>', $filename);
    print FILE $content;
    close(FILE);
}

# 文件夹准备

mkdir("result");

# 基本内容准备

$count_pages = &GetPagesCount();
$year = &GetYear();
$mouth = &GetMouth();
$day = &GetDay();

# 遍历文章

$i = 0;
while ($i < $count_pages)
{
    $i++;

    # 遍历版面内文章

    $count_article = &GetPageArticleCount($i);
    $j = 0;
    while ($j < $count_article)
    {
        $j++;
        %page_info = undef;
        $url = 0;
        if ($i < 10)
        {
            $url = "http://paper.people.com.cn/rmrb/html/$year-$mouth/$day/nw.D110000renmrb_$year$mouth$day\_$j-0$i.htm";
        }
        else
        {
            $url = "http://paper.people.com.cn/rmrb/html/$year-$mouth/$day/nw.D110000renmrb_$year$mouth$day\_$j-$i.htm";
        }
        %page_info = &GetSinglePageArticle($url);
        SaveArticleToFile("result/$year-$mouth-$day\\人民日报\\$page_info{'title'}".".txt", $page_info{'content'});
        print "\n已获取<人民日报>:".$page_info{'title'};
    }
}
