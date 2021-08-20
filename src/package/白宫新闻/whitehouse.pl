# 美国白宫新闻

# 程序所需要的Perl拓展

use LWP::UserAgent; # 引入网络支持
use POSIX qw(strftime); # 时间函数

# 程序所需要的自定义实现函数

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

# 获取列表

sub GatherBriefingRoomLinks {
    my $page = undef;
    my $content = undef;
    my $start;
    my $end;
    my $blockcontent = undef;
    my $today = undef;
    my $date = undef;
    my $count = 0;
    my @url;
    my $first_flag = 0;
    $page = LWP::UserAgent->new;
    $content = $page->get("https://www.whitehouse.gov/briefing-room/")->content;
    while (1) {
	$start = index($content,"<a class=\"news-item__title\" href=");
	if(-1 == $start)
	{
	    last;
	}
	$content = substr($content,$start);
	$end = index($content,"</time>");
	# 按块获取链接
	$blockcontent = substr($content,0,$end);
	$content = substr($content,$end);
	$start = index($blockcontent,"<time class=\"posted-on entry-date published updated\">");
	# 读取日期
	$date = substr($blockcontent,$start);
	$date = substr($date,length("<time class=\"posted-on entry-date published updated\">"));
	if(0 == $first_flag)
	{
	    $first_flag = 1;
	    $today_date = $date;
	}
	if(($date cmp $today_date)) # 如果日期不符合,则停止
	{
	    last;
	}
	# 读取URL
	$start = index($blockcontent,"href=\"");
	$url[$count] = substr($blockcontent,$start);
	$end = rindex($url[$count],"/\">");
	$url[$count] = substr($url[$count],length("href=\""),$end);
	$url[$count] = substr($url[$count],0,length($url[$count]) - length("/\">   "));
	$count++;
    }
    return @url;
}

# 获取单个页面的文章

sub SaveContentToFile {
    my ($title,$content) = @_;
    my $year = GetYear();
    my $mouth = GetMouth();
    my $day = GetDay();
    open (FILE,">./result/$year-$mouth-$day\\白宫新闻\\$title.txt");
    print FILE $content;
    close FILE;
}

sub GatherSinglePressArticle {
    my ($url) = @_;
    my $page = LWP::UserAgent->new;
    my $content = $page->get($url)->content;
    my $start = undef;
    my $end = undef;
    my $title = undef;
    # 获取文章标题
    $start = index($content,"<title>");
    $end = index($content,"</title>");
    $title = substr($content,$start + length("<title>"),$end - $start - length("</title"));
    $start = index($content,"<section class=\"body-content\">");
    $end = index($content,"</section>");
    $content = substr($content,$start,$end - $start + length("</section>"));
    return ($title,$content);
}

@url = GatherBriefingRoomLinks();
$i = 0;
$count = scalar @url;
while($i < $count)
{
    ($title,$content) = GatherSinglePressArticle($url[$i]);
    SaveContentToFile($title,$content);
    print "已获取<白宫新闻>:$title\n";
    $i++;
}

