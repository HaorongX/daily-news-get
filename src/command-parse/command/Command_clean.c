/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_clean.c
*    src/command-parse/command/Command_clean.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    Command_clean

    Describle:
      Delete a program

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
Command_clean(void *arguments, void *extern_information)
{
  char **main_argv = (char**)arguments;
  char temp[TEMP_BUFFER_LENGTH] = {0};
  if(*(int*)extern_information <= 2)
    {
      return CV_LACK_ARGUMENTS;
    }
  sprintf(temp, "./%s/%s",DNG_EXTENSION_INSTALL_DIRECTORY , main_argv[2]);
  RemoveDirectory(temp);
  return CV_SUCCESS;
}
