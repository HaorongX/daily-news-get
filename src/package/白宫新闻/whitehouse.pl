# 美国白宫新闻
use LWP::UserAgent;
$request = LWP::UserAgent->new;
$request->mirror("https://www.whitehouse.gov/briefing-room/","test.html");
