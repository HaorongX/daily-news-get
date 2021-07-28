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
help(void *arguments, void *extern_info)
{
  puts("dng version 0.0.4 Beta");
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
  puts("list                      List all the program installed");
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
  InitEnviroment();
  if(argc <= 1)
    {
      puts("dng: missing command");
      puts("Try 'dng help' for more infomation");
      return 0;
    }
  /* TODO: Build a function to pass on command */
  return 0;
}
