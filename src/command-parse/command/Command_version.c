/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_version.c
*    src/command-parse/command/Command_version.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include <stdio.h>
#include "command.h"
/*
    Command_version

    Describle:
      Print the version information
    Arguments:
      arguments:
        The packed data
      extern_information:
        The packed information
    Return value:
      CV_SUCCESS
        Success
*/
CodeValue
Command_version(void *arguments, void *extern_information)
{
  puts("DNG");
  puts("Daily News Gather");
  puts("0.0.4 Beta");
  return CV_SUCCESS;
}
