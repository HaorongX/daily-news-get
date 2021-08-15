# 美国国务新闻-公开行程获取部分

# 获取当天公开行程的链接

sub GatherScheduleLink {
    my $page = undef;
    my $content = undef;
    my $start = undef;
    my $end = undef;
    $page = LWP::UserAgent->new;
    $content = $page->get("https://www.state.gov/public-schedule/")->content;
    $start = index($content,"<p class=\"collection-result__date\">Public Schedule</p>");
    $end = index($content,"<div class=\"collection-result-meta\" dir=\"ltr\">");
    $url = substr($content,$start,$end - $start);
    $url =~ m/https:\/\/.*\/"/;
    $url = $&;
    $url = substr($url,0,length($url) - length("\""));
    return $url;
}

# 获取公开行程的文章

sub GatherScheduleArticle {
    $url = GatherScheduleLink();
    my $page = undef;
    my $content = undef;
    my $start = undef;
    my $end = undef;
    $page = LWP::UserAgent->new;
    $content = $page->get($url)->content;
    $start = index($content,"<div class=\"entry-content\">");
    $end = index($content,"<!-- .entry-content -->");
    $content = substr($content,$start,$end - $start);
    return $content;
}
