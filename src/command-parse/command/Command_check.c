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
    PrintFileContent

    Describle:
      Print a file content

    Arguments:
      filename
        The file name

    Return value:
      No value
*/
void
PrintFileContent(char *filename)
{
  FILE *fp = NULL;
  int c = 0;
  fp = fopen(filename, "r");
  if(NULL == fp)
    {
      return ;
    }
  while(EOF != (c = fgetc(fp)))
    {
      fputc(c, stdout);
    }
  fclose(fp);
}
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
  DIR *directory = NULL;
  char *parent_directory = "./installed";
  struct dirent *file = NULL;
  char **main_argv = (char**)arguments;
  int flag = 0;
  if(*(int*)extern_information <= 2)
    {
      return CV_LACK_ARGUMENTS;
    }
  directory = opendir(parent_directory);
  if(!directory)
    {
      return CV_OPEN_DIR_FAILRUE;
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
          if(!strcmp(file -> d_name, main_argv[2]))
            {
              char filename[512] = {0};
              sprintf(filename, "./installed/%s/help.txt", file -> d_name);
              PrintFileContent(filename);
              flag = 1;
              break;
            }
        }
    }
  if(0 == flag)
    {
      printf("Packed not found,please use 'dng list' for more information");
    }
  return CV_SUCCESS;
}
