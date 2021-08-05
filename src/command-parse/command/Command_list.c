/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_list.c
*    src/command-parse/command/Command_list.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
#include <stdio.h>
#include <dirent.h>
/*
    Command_list

    Describle:
      List the program installed

    Arguments:
      arguments:
        Accept the packed data
      extern_information
        Accept extural data

    Return value:
      CV_SUCCESS
        Success
      CV_FAILURE
        Failure

    Notice:
      We assumed the InitEnviroment has called
*/
CodeValue
Command_list(void *arguments, void *extern_information)
{
  DIR *directory = NULL;
  char *parent_directory = "./installed";
  struct dirent *file = NULL;
  /* '.' means the current directory  */
  directory = opendir(parent_directory);
  if(!directory)
    {
      return CV_FAILURE;
    }
  while(1)
    {
      file = readdir(directory);
      if(NULL == file)
        {
          break;
        }
      if(DT_DIR == file -> d_type)
        {

        }
    }
  return CV_SUCCESS;
}
