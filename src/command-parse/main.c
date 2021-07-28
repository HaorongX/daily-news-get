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

/* Describle a value of the argv array */
typedef char* CommandArgument;
/* To combine the main function arguments and pass on the function */
typedef struct _CommandArguments
{
  CommandArgument *arguments;/* A point to each arguments */
  unsigned long count;/* The number of the arguments */
}CommandArguments, *PCommandArguments;
/* Describle a rule between function and command */
typedef struct _FunctionObject
{
  void (*function)(PCommandArguments arguments,void *extern_info);/* The point to the function */
  char *command;/* The command to the function  */
}FunctionObject, *PFunctionObject;
/* Describle the rules */
typedef struct _FunctionObjects
{
  FunctionObject function_object;/* The function */
  int flag;/* 1 means already set */
  struct _FunctionObjects *first;
  struct _FunctionObjects *current;
  struct _FunctionObjects *next;
}FunctionObjects, *PFunctionObjects;
/*
    CreateCommandRule

    Describle:
      This function create a Function Object

    Arguments:
      first
        Used for exist data
        If there is no data,just use the NULL.

    Return value:
      A point to the object
        Success
      NULL
        Failure
*/
PFunctionObjects
CreateCommandRule(PFunctionObjects first)
{
  PFunctionObjects result =  (PFunctionObjects)calloc(1, sizeof(FunctionObjects));
  if(NULL == first)
    {
      result -> first = result;
    }
  else
    {
      result -> first = first;
    }
  result -> current = result;
  return result;
}
/*
    AddCommandRule

    Describle:
      This function add a rule to the Function Object

    Arguments:
      function_objects
        The goal
      function
        The dest
      command
        The source

    Return value:
      0
        Success
     -1
        Failure
*/
int
AddCommandRule(PFunctionObjects function_objects, void (*function)(PCommandArguments arguments,void *extern_info), char *command)
{
  function_objects -> function_object.function = function;
  if(NULL ==  (function_objects -> current -> function_object.command = (char*)calloc(strlen(command) + 1, sizeof(char))))
    {
      return -1;
    }
  sprintf(function_objects -> function_object.command, "%s", command);
  function_objects -> flag = 1;
  function_objects -> next = CreateCommandRule(function_objects -> first);
  function_objects -> current = function_objects -> next;
  if(NULL == function_objects -> first)
    {
      function_objects -> first = function_objects;
    }
  return 0;
}
/*
    CallFunctionByCommand

    Describle:
      This function select the appropriate function to handle the command

    Arguments:
      function_objects
        The array of function with its rule
      command
        The source command
      arguments
        The data provide by main function

    Return value:
      1
        Success
      Other
        Failure
*/
int
CallFunctionByCommand
(PFunctionObjects functions, char *source_command, PCommandArguments arguments)
{
  PFunctionObjects temp = NULL;
  int flag = 0;
  temp = functions -> first;
  while(temp)
    {
      if(0 == strcmp(temp -> function_object.command, source_command))
        {
          temp -> function_object.function(arguments, 0);
          flag = 1;
          break;
        }
      temp = temp -> next;
    }
  return flag;
}
/*
    ConvertArgvToCommandArguments

    Describle:
      This function used to convert main's argv to CommandArguments structure

    Arguments:
      main_argc
        The main argc argument
      main_argv
        The main argv argument

    Return value:
      This function return a point to CommandArguments structure
      If return the NULL,something wrong happend

    Notice
      main is the C program main function
      count from the third argument of the main function
*/
PCommandArguments
ConvertArgvToCommandArguments(int main_argc,char **main_argv)
{
  PCommandArguments result = NULL;
  if(NULL == (result = (PCommandArguments)calloc(sizeof(CommandArguments),1)))
    {
      return NULL;
    }
  result -> count = main_argc - 2;
  if(main_argc <= 2)
    {
      return result;
    }
  result -> arguments = calloc(sizeof(CommandArgument),result -> count);
  for(int i = 0;i < result -> count;i++)
    {
      result -> arguments[i] = main_argv[i + 2];
    }
  return result;
}
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
    help

    Describle:
      Print the help message

    Arguments:
      arguments:
        the main function arguments
      extern_info:
        Extern Infomation

    Return value:
      No value
*/
void
help(PCommandArguments arguments, void *extern_info)
{
  puts("dng bersion 0.0.4 Beta");
  puts("Usage: dng [OPTION]");
  puts("--version                 Display compiler version information");
  puts("-v                        Equal to '--version'");
  puts("--help [command]          Display help information");
  puts("help [command]            Equal to '--help'");
  puts("install [name]            Install a program");
  puts("remove [name]             Remove a program");
  puts("uninstall [name]          Equal to 'remove'");
  puts("execute [name]            Execute a program");
  puts("gather [name]             Equal to 'execute'");
  puys("list                      List all the program installed");
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
  PCommandArguments main_command = NULL;
  PFunctionObjects rules = NULL;
  InitEnviroment();
  if(argc <= 1)
    {
      puts("dng: missing command");
      puts("Try 'dng help' for more infomation");
      return 0;
    }
  /* TODO: Build a function to pass on command */
  main_command = ConvertArgvToCommandArguments(argc, argv);
  if(NULL == main_command)
    {
      puts("Error:Can't allow the memory.");
      return -1;
    }
  rules = CreateCommandRule(NULL);
  AddCommandRule(rules, help, "--help");
  CallFunctionByCommand(rules, argv[1], main_command);
  return 0;
}
