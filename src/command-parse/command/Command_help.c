/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_help.c
*    src/command-parse/command/Command_help.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
#include <stdio.h>
/*
    Command_help

    Describle:
      Print the help information

    Arguments:
      arguments:
        Accept the packed data
      extern_information
        Accept extural data

    Return value:
      CV_SUCCESS
        Success
      CV_USER_NOT_FOUNT
        Command not found
      CV_USER_FILE_NOT_FOUND
        Program not found
*/
CodeValue
Command_help(void *arguments, void *extern_information)
{
  puts("DNG -- 每日新闻收集程序");
  puts("");
  puts("使用方法: dng command");
  puts("");
  puts("主要信息列表:");
  puts("");
  puts("help");
  puts("  提供内置帮助信息");
  puts("");
  puts("--help");
  puts("  等同于 'help'");
  puts("-h");
  puts("  等同于 'help'");
  puts("version");
  puts("  提供DNG版本信息");
  puts("-v");
  puts("  等同于 'version'");
  puts("install [install.note]");
  puts("  安装一个拓展程序以用于获取新闻");
  puts("  重要提示:");
  puts("    1.拓展程序必须包含如下文件");
  puts("      install.note");
  puts("      > 使用 'dng note-maker' 指令生成的拓展配置文件");
  puts("      help.txt");
  puts("      > 拓展自身的帮助信息");
  puts("      connect program(通信程序)");
  puts("      > 用于同DNG主程序通信的拓展程序");
  puts("      result(文件夹)");
  puts("      > 用于储存获取的新闻及有关新闻的材料(如mp3音频)");
  puts("      > 所有的新闻文本请以.txt后缀结尾");
  puts("      > 文件的命名规范是: 日期(年-月-日)\\新闻源名称\\新闻标题.txt");
  puts("    2.请直接使用拓展程序包含的 install.note 配置文件完成安装");
  puts("remove [name]");
  puts("  使一个拓展处于关闭状态");
  puts("  如果需要完全移除拓展,请使用 'dng clean' 指令");
  puts("clean [name]");
  puts("  彻底清除一个拓展");
  puts("execute [name]");
  puts("  执行一个拓展用于获取新闻");
  puts("  如果直接使用 'dng execute' 所有的拓展都会被执行");
  puts("  最后新闻的汇总会输出到 Complete.html 文件");
  puts("list");
  puts("  罗列你已经安装的拓展程序");
  puts("check [name]");
  puts("  查看有关拓展的帮助信息");
  return CV_SUCCESS;
}
