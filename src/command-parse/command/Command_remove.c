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
  DIR *directory = NULL;
  char *parent_directory = "./installed";
  struct dirent *file = NULL;
  char **main_argv = (char**)arguments;
  char temp[512] = {0};
  if(*(int*)extern_information <= 2)
    {
      return CV_USER_LACK_ARGUMENTS;
    }
  directory = opendir(parent_directory);
  if(!directory)
    {
      return CV_USER_FAILURE;
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
          PNoteRecord notefile = NULL;
          char filename[512] = {0};
          if(!strcmp(file -> d_name, "..") || !strcmp(file -> d_name, "."))
            {
              continue;
            }
          sprintf(filename, "./installed/%s/install.note", file -> d_name);
          notefile = LoadNoteFile(filename);
          if(!strcmp(main_argv[2], notefile -> name))
            {
              sprintf(temp, "echo > ./installed/%s/remove.lock", file -> d_name);
              system(temp);
              FreeNoteFile(notefile);
              break;
            }
          if(NULL == notefile)
            {
              continue;
            }
          FreeNoteFile(notefile);
        }
    }
  closedir(directory);
  return CV_SUCCESS;
}
