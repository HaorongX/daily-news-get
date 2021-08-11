# FormatArticle.pl
# 本文件用于清除脚本获取的页面标签,以及页面的其它多余内容
sub FormatArticle {
    my ($content) = @_;
    $content =~ s/&nbsp;//g;
    $content =~ s/nbsp;//g;
    $content =~ s/<P align=center>/<P>/g;
    $content;
}
