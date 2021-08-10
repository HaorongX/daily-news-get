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
CodeStatus file_handle(FileInfo info, void *arguments)
{
  int *count = (int*)arguments;
  if(DT_DIR == info.type)
  {
    PNoteRecord notefile = NULL;
    notefile = AccessPackageNoteFile(info.name);
    if(NULL == notefile)
    {
      FreeNoteFile(notefile);
      return ERROR_OPEN_FILE;
    }
    if(0 == (*count))
    {
      puts("Installing:");
    }
    printf("%16s     %16s       %16s\n", notefile -> name, notefile -> author, notefile -> version);
    FreeNoteFile(notefile);
    (*count)++;
  }
}
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
  char *parent_directory = "./installed";
  int count = 0;
  puts("================================================================");
  puts("");
  puts("     Package                  Author                 Version");
  puts("");
  puts("================================================================");
  if(ERROR_OPEN_DIRECTORY == AccessDirectory(parent_directory, file_handle, &count, 0))
    {
      return CV_INSTALL_DIRECTORY_ACCESS_FAILURE;
    }
  puts("================================================================");
  printf("Install %3d Package\n", count);
  return CV_SUCCESS;
}
