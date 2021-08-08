/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_help.c
*    src/command-parse/command/Command_help.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
#include <stdio.h>
/*
    Command_help

    Describle:
      Print the help information

    Arguments:
      arguments:
        Accept the packed data
      extern_information
        Accept extural data

    Return value:
      CV_SUCCESS
        Success
      CV_USER_NOT_FOUNT
        Command not found
      CV_USER_FILE_NOT_FOUND
        Program not found
*/
CodeValue
Command_help(void *arguments, void *extern_information)
{
  puts("DNG -- Daily News Gather");
  puts("");
  puts("usage: dng command");
  puts("");
  puts("List of Main Commands:");
  puts("");
  puts("help");
  puts("  Provide built-in help information");
  puts("");
  puts("--help");
  puts("  Equal to 'help'");
  puts("-h");
  puts("  Equal to '-h'");
  puts("version");
  puts("  Provide built-in version information");
  puts("-v");
  puts("  Equal to 'version'");
  puts("install [name]");
  puts("  Install a program");
  puts("  Require:");
  puts("    1.The program need to provide: install.note help.txt and a connect program");
  puts("      > You can use the 'dng note-maker' to create a install.note for your program");
  puts("      > The format:");
  puts("        # Program-Name");
  puts("        @ Author");
  puts("          % your name");
  puts("            @ Version");
  puts("              % your version");
  puts("            @ Connect Program");
  puts("              % path");
  puts("      > The connect program Only needs to pass on the arguments that the DNG received");
  puts("    2.The program need to include in a floder");
  puts("    3.The program need to output the article it gathers into a file named 'collect.note'");
  puts("remove [name]");
  puts("  Remove a program but not delete it");
  puts("  If you want to delete the program your installed,try to use the 'clean'");
  puts("clean [name]");
  puts("  Delete a program your installed");
  puts("execute [name]");
  puts("  Execute corrosponding program and output the final article into 'result'(Directory)");
  printf("  > Name rule: Date%cWebsite%cTitle.txt\n", '\\', '\\');
  printf("    > Example: 2021-1-1%cHello world%cHappy New Year!.txt", '\\', '\\');
  puts("  > If there is no '[name]', all the program installed will be executed");
  puts("list");
  puts("  List the program you installed");
  puts("check [name]");
  puts("  Check a installed program");
  return CV_SUCCESS;
}
