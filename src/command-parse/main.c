/************************************************************
*
*  DNG Project
*     Daily News Gather
*
*  main.c
*     This is the main part of the dng command-parse
*
*  Copyright Public Domain 2021
*
************************************************************/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "function_objects/function_objects.h"
#include "command/command.h"
/*
    InitEnviroment

    Describle:
      To make sure the program run in the right track

    Arguments:
      This function needn't any arguments

    Return value:
      0
        Success
     -1
        Failure
*/
int
InitEnviroment(void)
{
  char path[1025] = {0};
  int length = 0;
  /* Get the current work directory */
  if(-1 == readlink("/proc/self/exe",path,1024))
  {
    return -1;
  }
  length = strlen(path);
  while('/' !=  *(path + length))
    {
      *(path + length) = '\0';
      length--;
    }
  if(0 != chdir(path))
    {
      return -1;
    }
  return 0;
}
/*
    PrintErrorMessage

    Describle:
      Print the error message

    Arguments:
      code
        The error code
      message:
        The message print
      line:
        The line of code
        Should be __LINE__

    Return value:
      No value

    Notice:
      If DNG_RELEASE defined,the third argument will be ignored.
*/
void
PrintErrorMessage(int error_code, char *message, int line)
{
  printf("DNG Error:%s\nError code:%3d\n", message, error_code);
  #ifdef DNG_RELEASE
  printf("Code line:%d\n", line);
  #endif
}
/*
    PrepareRules

    Describle:
      Simplify the process of prepare the crospponding rules between
      function and command

    Arguments:
      rules
        The existed rules object

    Return value:
      No value
*/
void
PrepareRules(PFunctionRules rules)
{
  AddFunctionRule(rules, Command_help, "help");
  AddFunctionRule(rules, Command_help, "--help");
  AddFunctionRule(rules, Command_help, "-h");
  AddFunctionRule(rules, Command_version, "version");
  AddFunctionRule(rules, Command_version, "--version");
  AddFunctionRule(rules, Command_version, "-v");
  AddFunctionRule(rules, Command_install, "install");
  AddFunctionRule(rules, Command_remove, "remove");
  AddFunctionRule(rules, Command_remove, "uninstall");
  AddFunctionRule(rules, Command_list, "list");
  AddFunctionRule(rules, Command_list, "--list");
  AddFunctionRule(rules, Command_execute, "execute");
  AddFunctionRule(rules, Command_execute, "gather");
  AddFunctionRule(rules, Command_clean, "clean");
  AddFunctionRule(rules, Command_check, "check");
}

/*
    main

    Describle:
      This Function Is The Main Part Of the program

    Arguments:
      argc
        The count of the arguments to the program
      argv
        The arguments spilited by ' '

    Return value:
      0
        Success
     -1
        Something wrong happend
*/
int
main(int argc, char **argv)
{
  PFunctionRules rules = NULL;
  CodeValue status_value = 0;
  InitEnviroment();
  if(argc <= 1)
    {
      puts("dng: missing command");
      puts("Try 'dng help' for more infomation");
      return 0;
    }
  rules = CreateFunctionRules();
  if(NULL == rules)
    {
      return -1;
    }
  PrepareRules(rules);
  status_value = CallFunction(rules, argv[1], (void*)argv, (void*)&argc);
  if(CV_FAILURE == status_value)
    {
      PrintErrorMessage(CV_FAILURE, "Command not found", __LINE__);
    }
  //CleanFunctionRule(rules);
  return 0;
}
