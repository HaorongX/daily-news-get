/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_install.c
*    src/command-parse/command/Command_instal.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
#include "../note_reader/note_reader.h"
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
/*
    GetDngPath

    Describle:
      Get the dng installed path

    Arguments:
      dest
        The dest string

    Return value:
      No value
*/
void
GetDngPath(char *dest)
{
  char path[1025] = {0};
  int length = 0;
  readlink("/proc/self/exe",path,1024);
  length = strlen(path);
  while('/' !=  *(path + length))
    {
      *(path + length) = '\0';
      length--;
    }
  strncpy(dest, path, length);
}
/*
    GetPackagePath

    Describle:
      Get package path by the path of the install.note

    Arguments:
      dest:
        The dest string
      path:
        The path of the install.note

    Return value:
      No value
*/
void
GetPackagePath(char *dest, char *path)
{
  int length = 0;
  length = strlen(path);
  while('/' != *(path + length))
    {
      *(path + length) = '\0';
      length--;
    }
  strncpy(dest, path, length);
}
/*
    Command_install

    Describle:
      Install a program

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
Command_install(void *arguments, void *extern_information)
{
  char package_directory[1025] = {0};
  char dng_directory[1025] = {0};
  char **main_argv = (char**)arguments;
  char temp[1024] = {0};
  PNoteRecord notefile = NULL;
  if(*(int*)extern_information <= 2)
    {
      return CV_USER_LACK_ARGUMENTS;
    }
  notefile = LoadNoteFile(main_argv[2]);
  GetPackagePath(package_directory, main_argv[2]);
  GetDngPath(dng_directory);
  sprintf(temp, "cp -r %s %s/installed/%s", package_directory, dng_directory, notefile -> name);
  system(temp);
  FreeNoteFile(notefile);
  return CV_SUCCESS;
}
