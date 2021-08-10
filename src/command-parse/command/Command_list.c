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
#include "../note_reader/note_reader.h"
#include <stdio.h>
#include <string.h>
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
  int count = 0;
  /* '.' means the current directory  */
  directory = opendir(parent_directory);
  if(!directory)
    {
      return CV_OPEN_DIR_FAILRUE;
    }
  puts("================================================================");
  puts("");
  puts("     Package                  Author                 Version");
  puts("");
  puts("================================================================");
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
          char filename[PATH_MAXLENGTH] = {0};
          if(!strcmp(file -> d_name, "..") || !strcmp(file -> d_name, "."))
            {
              continue;
            }
          sprintf(filename, "./installed/%s/install.note", file -> d_name);
          notefile = LoadNoteFile(filename);
          if(NULL == notefile)
            {
              FreeNoteFile(notefile);
              break;
            }
          if(0 == count)
            {
              puts("Installing:");
            }
          printf("%16s     %16s       %16s\n", notefile -> name, notefile -> author, notefile -> version);
          FreeNoteFile(notefile);
          count++;
        }
    }
  puts("================================================================");
  printf("Install %3d Package\n", count);
  closedir(directory);
  return CV_SUCCESS;
}
