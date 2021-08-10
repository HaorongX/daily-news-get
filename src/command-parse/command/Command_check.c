/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_check.c
*    src/command-parse/command/Command_instal.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
/*
    Command_check

    Describle:
      Check a program information

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
Command_check(void *arguments, void *extern_information)
{
  char **main_argv = (char**)arguments;
  char filename[PATH_MAXLENGTH] = {0};
  if(*(int*)extern_information <= 2)
    {
      return CV_LACK_ARGUMENTS;
    }
  sprintf(filename, "./%s/%s/%s",DNG_EXTENSION_INSTALL_DIRECTORY, main_argv[2], DNG_EXTENSION_HELP_FILE);
  if(S_SUCCESS != PrintFileContent(filename))
    {
      return CV_PACKAGE_HELP_FAILURE;
    }
  return CV_SUCCESS;
}
