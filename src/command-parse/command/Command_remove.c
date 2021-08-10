/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_remove.c
*    src/command-parse/command/Command_remove.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
#include "../note_reader/note_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
/*
    Command_remove

    Describle:
      Remove a program

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
Command_remove(void *arguments, void *extern_information)
{
  char temp[TEMP_BUFFER_LENGTH];
  char **main_argv = (char**)arguments;
  if(*(int*)extern_information <= 2)
    {
      return CV_LACK_ARGUMENTS;
    }
  sprintf(temp, "./%s/%s/%s", DNG_EXTENSION_INSTALL_DIRECTORY, main_argv[2],DNG_EXTENSION_CLOSE_FILE);
  CreateEmptyFile(temp);
  return CV_SUCCESS;
}
