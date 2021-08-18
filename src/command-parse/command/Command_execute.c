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
#include <time.h>
char *GetTodayDateString()
{
  static char today[TEMP_BUFFER_LENGTH] = {0};
  struct tm *today_date = {0};
  time_t timer;
  time(&timer);
  today_date = gmtime(&timer);
  sprintf(today, "%d-%d-%d",1900 + today_date -> tm_year, today_date -> tm_mon + 1, today_date -> tm_mday);
  return today;
}
CodeStatus MargeResultToFile(FileInfo info, void *argument)
{
  if(strstr(info.name, DNG_EXTENSION_OUTPUT_FILE_SUFFIX_NAME))
    {

      char temp[TEMP_BUFFER_LENGTH] = {0};
      char temp2[TEMP_BUFFER_LENGTH] = {0};
      char title[TEMP_BUFFER_LENGTH] = {0};
      char *character = 0;
      sprintf(temp, "%s/%s", info.path, info.name);
      character = strrchr(info.name, '\\');
      strncpy(title, character + 1, strlen(character) - strlen(DNG_EXTENSION_OUTPUT_FILE_SUFFIX_NAME) - strlen(".") - strlen("."));
      strncpy(temp2, info.name, strlen(info.name) - strlen(strchr(info.name, '\\')));
      if(!strcmp(temp2, GetTodayDateString()))
        {
          return S_SUCCESS;
        }
      AddContentToFile("Complete.html", "\n<br><b>");
      AddContentToFile("Complete.html", title);
      AddContentToFile("Complete.html", "</b><br>\n");
      CombineFile("Complete.html", temp);
    }
  return S_SUCCESS;
}
CodeStatus package_handle(FileInfo info, void *argument)
{
  PNoteRecord record = NULL;
  char temp[TEMP_BUFFER_LENGTH] = {0};
  if(DT_DIR != info.type)
    {
      return S_SUCCESS;
    }
  if(IsRemove(info.name))
    {
      return S_SUCCESS;
    }
  record = AccessPackageRecord(info.name);
  sprintf(temp, "./%s/%s/%s", DNG_EXTENSION_INSTALL_DIRECTORY, info.name, record -> connect_program);
  AddContentToFile("Complete.html", "<h2>");
  AddContentToFile("Complete.html", record -> name);
  AddContentToFile("Complete.html", "</h2>");
  system(temp);
  FreeNoteFile(record);
  sprintf(temp, "./%s/%s/%s", DNG_EXTENSION_INSTALL_DIRECTORY, info.name, DNG_EXTENSION_RESULT_DIRECTORY);
  AccessDirectory(temp, MargeResultToFile, 0, 0);
  return S_SUCCESS;
}
CodeStatus package_single_handle(char *package_name)
{
  PNoteRecord record = NULL;
  char temp[TEMP_BUFFER_LENGTH] = {0};
  if(IsRemove(package_name))
    {
      return S_SUCCESS;
    }
  record = AccessPackageRecord(package_name);
  sprintf(temp, "./%s/%s/%s", DNG_EXTENSION_INSTALL_DIRECTORY, package_name, record -> connect_program);
  AddContentToFile("Complete.html", "<h2>");
  AddContentToFile("Complete.html", record -> name);
  AddContentToFile("Complete.html", "</h2>");
  system(temp);
  FreeNoteFile(record);
  sprintf(temp, "./%s/%s/%s", DNG_EXTENSION_INSTALL_DIRECTORY, package_name, DNG_EXTENSION_RESULT_DIRECTORY);
  AccessDirectory(temp, MargeResultToFile, 0, 0);
  return S_SUCCESS;
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
  char **main_argv = (char**)arguments;
  RemoveFile("Complete.html");
  CreateEmptyFile("Complete.html");
  CombineFile("Complete.html", "Complete.css");
  AddContentToFile("Complete.html", "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">");
  if(*(int*)extern_information == 2)
    {
      AccessDirectory(DNG_EXTENSION_INSTALL_DIRECTORY, package_handle, NULL, 0);
    }
  else
    {
      package_single_handle(main_argv[2]);
    }
  return CV_SUCCESS;
}
