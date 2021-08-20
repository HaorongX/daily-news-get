# 美国国务新闻

# 程序所需要的Perl拓展

use LWP::UserAgent; # 引入网络支持
use POSIX qw(strftime); # 时间函数

# 程序所需要的自定义实现函数
# 这个程序一分为三
# 每一个包含的脚本实现一部分函数

do './public_schedule.pl'; # 获取每日行程
do './press_release.pl'; # 获取公开演讲,文献发布
do './public_briefings.pl'; # 获取每日简报

# 获取今日时间

sub GetYear {
    strftime "%Y", localtime;
}

sub GetMouth {
    strftime "%m", localtime;
}

sub GetDay {
    strftime "%d", localtime;
}

# 创建result文件夹用于保存获取的文章

mkdir("result");

# 遍历并获取文章

sub SaveContentToFile {
    my ($title,$content) = @_;
    my $year = GetYear();
    my $mouth = GetMouth();
    my $day = GetDay();
    open (FILE,">./result/$year-$mouth-$day\\国务新闻\\$title.txt");
    print FILE $content;
    close FILE;
}
# 公开行程

$content = GatherScheduleArticle();
print "已获取<国务新闻>:美国国务院最新行程\n";
SaveContentToFile("美国国务最新行程安排",$content);

# 公开简报

@url = GatherBrefingsLinks();
$i = 0;
$count = scalar @url;
while($i < $count)
{
    ($title,$content) = GatherSingleArticle($url[$i]);
    SaveContentToFile($title,$content);
    print "已获取<国务新闻>:$title\n";
    $i++;
}

# 演说

@url = GatherPressLinks();
$i = 0;
$count = scalar @url;
while($i < $count)
{
    ($title,$content) = GatherSinglePressArticle($url[$i]);
    SaveContentToFile($title,$content);
    print "已获取<国务新闻>:$title\n";
    $i++;
}
