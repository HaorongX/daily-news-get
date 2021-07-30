/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_install.c
*    src/command-parse/command/Command_instal.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
/*
    Command_install

    Describle:
      Install a program

    Arguments:
      arguments:
        Accept the packed data
      extern_information
        Accept extural data

    Return value:
      CV_SUCCESS
        Success
*/
CodeValue
Command_install(void *arguments, void *extern_information)
{
  if(*(int*)extern_information <= 2)
    {
      return CV_USER_LACK_ARGUMENTS;
    }
  return CV_SUCCESS;
}
