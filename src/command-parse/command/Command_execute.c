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
      return 0;
    }
  fclose(fp);
  return 1;
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
CodeValue
ExecutePackage(char *name, char *arguments)
{
  DIR *directory = NULL;
  char *parent_directory = "./installed";
  struct dirent *file = NULL;
  char temp[4096] = {0};
  CodeValue flag = CV_PACKAGE_NOT_FOUND;
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
          PNoteRecord notefile = NULL;
          char filename[512] = {0};
          sprintf(temp, "./installed/%s/remove.lock", file -> d_name);
          if(FileExist(temp))
            {
              continue;
            }
          if(!strcmp(file -> d_name, ".") || !strcmp(file -> d_name, ".."))
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
              flag = CV_SUCCESS;
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
CodeValue
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
          PNoteRecord notefile = NULL;
          char filename[512] = {0};
          sprintf(temp, "./installed/%s/remove.lock", file -> d_name);
          if(FileExist(temp))
            {
              continue;
            }
          if(!strcmp(file -> d_name, ".") || !strcmp(file -> d_name, ".."))
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
    GetFileSuffixName

    Describle:
      Get a file suffix name by full path

    Arguments:
      path
        The full path of the file

    Return value:
      The suffix name
*/
char*
GetFileSuffixName(char *path)
{
  int length = strlen(path);
  int suffix_length = 0;
  int i = 0;
  static char dest[128] = {0};
  memset(dest, 0, sizeof(dest));
  while(*(path + length - suffix_length) != '.')
    {
      suffix_length++;
    }
  strcpy(dest, (path + length - suffix_length + 1));
  return dest;
}
/*
    GetNewsTitle

    Describle:
      Get news title by full path

    Arguments:
      file
        The full path

    Return value:
      The title
*/
char*
GetNewsTitle(char *file)
{
  char *suffix = NULL;
  char *c_directory = 0;
  static char result[512] = {0};
  memset(result, 0, sizeof(result));
  strcpy(result, file);
  suffix = strstr(result, ".txt");
  memset(suffix, 0, strlen(suffix));
  c_directory = strrchr(result, '\\');
  strncpy(result, c_directory + 1, strlen(c_directory + 1));
  return result;
}
/*
    Collectpackage

    Describle:
      Collect daily news

    Arguments:
      name
        The dest package

    Return value:

*/
CodeValue
CollectPackage(char *name)
{
  DIR *directory = NULL;
  char parent_directory[1024] = {0};
  struct dirent *file = NULL;
  int flag = 0;
  sprintf(parent_directory, "./installed/%s/result", name);
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
      if(!strcmp(file -> d_name, ".") || !strcmp(file -> d_name, ".."))
      {
        continue;
      }
      if(DT_REG == file -> d_type)
        {
          if(!strcmp("txt", GetFileSuffixName(file -> d_name)))
            {
              char content[1024] = {0};
              char filename[1024] = {0};
              sprintf(content, "<b> %s </b><br>\n", GetNewsTitle(file -> d_name));
              AddContentToFile("Complete.html", content);
              sprintf(filename, "./installed/%s/result/%s", name,file -> d_name);
              CombineFile("Complete.html", filename);
              AddContentToFile("Complete.html", "<br>");
              flag = 1;
            }
        }
    }
  closedir(directory);
  if(flag)
    {
      return CV_SUCCESS;
    }
  return CV_PACKAGE_NOT_FOUND;
}
/*
    CollectAllPackage

    Describle:
      Collect daily news

    Arguments:
      No arguments

    Return value:
      No value
*/
void
CollectAllPackage(void)
{
  DIR *directory = NULL;
  char *parent_directory = "./installed/";
  struct dirent *file = NULL;
  directory = opendir(parent_directory);
  if(!directory)
  {
    return ;
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
          char content[1024];
          if(!strcmp(file -> d_name, ".") || !strcmp(file -> d_name, ".."))
          {
            continue;
          }
          sprintf(content,"<br><h1>%s</h1><br>",file -> d_name);
          AddContentToFile("Complete.html", content);
          CollectPackage(file -> d_name);
        }
    }
  closedir(directory);
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
  CodeValue result = CV_SUCCESS;
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
  if(CV_SUCCESS != result)
    {
      return result;
    }
  /* Second: Gather */
  system("echo >Complete.html");
  if(*(int*)extern_information == 2)
    {
      CollectAllPackage();
    }
  else
    {
      result = CollectPackage(main_argv[2]);
    }
  return result;
}
