/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_execute.c
*    src/command-parse/command/Command_execute.c
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
    FileExist

    Describle:
      Is file exist?
    Arguments:
      path
        The path to the file
    Return value:
      0
        Exist
     -1
        No file
*/
int
FileExist(char *name)
{
  FILE *fp;
  fp = fopen(name, "r");
  if(NULL == fp)
    {
      return -1;
    }
  fclose(fp);
  return 0;
}
/*
    ExecutePackage

    Describle:
      Execute a program
    Arguments:
      name
        The name of the program
      arguments
        The arguments to the program
    Return value:
      0
        Success
     -1
        Something wrong happend
*/
int
ExecutePackage(char *name, char *arguments)
{
  DIR *directory = NULL;
  char *parent_directory = "./installed";
  struct dirent *file = NULL;
  char temp[4096] = {0};
  int flag = -1;
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
          sprintf(temp, "./installed/%s/remove.lock", file -> d_name);
          if(FileExist(temp))
            {
              continue;
            }
          sprintf(filename, "./installed/%s/install.note", file -> d_name);
          notefile = LoadNoteFile(filename);
          if(NULL == notefile)
            {
              continue;
            }
          if(!strcmp(notefile -> name, name))
            {
              sprintf(temp, "./installed/%s/%s %s", file -> d_name, notefile -> connect_program, arguments);
              system(temp);
              FreeNoteFile(notefile);
              flag = 0;
              break;
            }
          FreeNoteFile(notefile);
        }
    }
  closedir(directory);
  return flag;
}
/*
    ExecuteAllPackage

    Describle:
      Execute all the program

    Arguments:
      No argument

    Return value:
      0
        Success
     -1
        Something wrong happend
*/
int
ExecuteAllPackage(void)
{
  /* Execute all the package */
  DIR *directory = NULL;
  char *parent_directory = "./installed";
  struct dirent *file = NULL;
  char temp[4096] = {0};
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
          sprintf(temp, "./installed/%s/remove.lock", file -> d_name);
          if(FileExist(temp))
            {
              continue;
            }
          sprintf(filename, "./installed/%s/install.note", file -> d_name);
          notefile = LoadNoteFile(filename);
          if(NULL == notefile)
            {
              continue;
            }
          sprintf(temp, "./installed/%s/%s", file -> d_name, notefile -> connect_program);
          system(temp);
          FreeNoteFile(notefile);
        }
    }
  closedir(directory);
  return CV_SUCCESS;
}
/*
    Command_execute

    Describle:
      Execute program installed

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
Command_execute(void *arguments, void *extern_information)
{
  char combine_argument[4096] = {0};
  char **main_argv = (char**)arguments;
  int result = CV_SUCCESS;
  /* First: Execute */
  if(*(int*)extern_information == 2)
    {
      result = ExecuteAllPackage();
    }
  else
    {
      int i = 3;
      while(i < ((*(int*)extern_information)))
        {
          strcat(combine_argument, main_argv[i - 1]);
          i++;
        }
      result = ExecutePackage(main_argv[2], combine_argument);
    }
  /* Second: Gather */

  return result;
}
