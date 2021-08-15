# 美国国务新闻-公开新闻稿获取部分

# 获取链接

sub GatherPressLinks {
    my $page = undef;
    my $content = undef;
    my $start = undef;
    my $end = undef;
    my $first_flag = 0;
    my $block_content = undef;
    my $date = undef;
    my $first_date = undef;
    my $links;
    my @url = undef;
    my $count = 0;
    $page = LWP::UserAgent->new;
    $content = $page->get("https://www.state.gov/press-releases/")->content;
    while (true) {
	$start = index($content,"<p class=\"collection-result__date\">");
	if(-1 == $start)
	{
	    last;
	}
	$content = substr($content,$start);
	$end = index($content,"</div>");
	$block_content = substr($content,0,$end);
	$content = substr($content,$end);
	# 提取日期(将最前面的文章当作最新日期)
	$block_content =~ m/<span dir="ltr">.*<\/span>/;
	$date = $&;
	$start = index($date,">");
	$date = substr($date,$start + length(">"));
	$end = index($date,"<");
	$date = substr($date,0,$end);
	if($first_flag == 0)
	{
	    $first_flag = 1;
	    $first_date = $date;
	}
	if(($date cmp $first_date)) # 如果日期不符合,则停止
	{
	    last;
	}
	# 获取对应的页面URL
	$block_content =~ m/=".*\/"/;
	$url = $&;
	$url = substr($url,length("=\""));
	$end = rindex($url,"\"");
	$url[$count] = substr($url,0,$end);
	$count++;
    }
    return @url;
}

# 获取单个页面的文章

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
    # 有无视频播放
    if(-1 == ($start = index($content,"<!-- End of Brightcove Player -->")))
    {
	$start = index($content,"<div class=\"entry-content\">");
	$end = index($content,"<!-- .entry-content -->");
	$content = substr($content,$start,$end - $start);
    }
    else
    {
	$end = index($content,"<!-- .entry-content -->");
	$content = substr($content,$start,$end - $start);
    }
    return ($title,$content);
}
