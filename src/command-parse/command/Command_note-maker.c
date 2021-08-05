/************************************************
*  DNG Project
*    Daily News Gather
*
*  Command_note-maker.c
*    src/command-parse/command/Command_note-maker.c
*
*  Copyright Public Domain 2021
*
*************************************************/
#include "command.h"
#include <stdio.h>
#define DNG_NOTE_MAKER_VERSION "0.0.2"
/*
    DeleteCharacter

    Describle:
      Delete a character from a string

    Arguments:
      string
        The source string
      character
        The character

     Return value:
       No value
*/
void
DeleteCharacter(char *string, char character)
{
  int i = 0;
  while('\0' != *(string + i))
    {
      if(*(string + i) == character)
        {
          *(string + i) = '\0';
        }
      i++;
    }
}
/*
    Command_note_maker

    Describle:
      Make the program note file
      (install.note)

    Arguments:
      arguments:
        Accept the packed data
      extern_information
        Accept extural data

    Return value:
      CV_SUCCESS
        Success
      CV_USER_FILE_FAILURE
        Create file failed
*/
CodeValue
Command_note_maker(void *arguments, void *extern_information)
{
  FILE *install_note = NULL;
  char input_name[256] = {0};
  char input_author[256] = {0};
  char input_version[256] = {0};
  char input_connect_program[256] = {0};
  printf("DNG -- install.note maker\n");
  printf("Version:%s\n", DNG_NOTE_MAKER_VERSION);
  printf("Please make sure your input with no blank");
  printf("Step 1:");
  printf("Plesase input your project name\n");
  printf("For example: my-gather\n");
  printf("Your project name:");
  fgets(input_name, 255, stdin);
  printf("Step 2:");
  printf("Plesase input your project author\n");
  printf("For example: pie\n");
  printf("Your name:");
  fgets(input_author, 255, stdin);
  printf("Step 3:");
  printf("Plesase input your project version\n");
  printf("For example: 0.0.1\n");
  printf("Your version:");
  fgets(input_version, 255, stdin);
  printf("Step 4:");
  printf("Plesase input your connect program\n");
  printf("For example: connect.out\n");
  printf("Your connect program:");
  fgets(input_connect_program, 255, stdin);
  if(NULL == (install_note = fopen("install.note", "w")))
    {
      return CV_USER_FILE_FAILURE;
    }
  DeleteCharacter(input_name, '\n');
  DeleteCharacter(input_author, '\n');
  DeleteCharacter(input_version, '\n');
  DeleteCharacter(input_connect_program, '\n');
  fprintf(install_note, "# %s\n", input_name);
  fprintf(install_note, "  @ Author\n");
  fprintf(install_note, "    %% %s\n", input_author);
  fprintf(install_note, "  @ Version\n");
  fprintf(install_note, "    %% %s\n", input_version);
  fprintf(install_note, "  @ Connect Program\n");
  fprintf(install_note, "    %% %s\n", input_connect_program);
  fclose(install_note);
  return CV_SUCCESS;
}
