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
#include "../note_reader/note_reader.h"
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
  NoteRecord record;
  printf("DNG -- install.note maker\n");
  printf("Version:%s\n", DNG_NOTE_MAKER_VERSION);
  printf("Please make sure your input with no blank");
  printf("Step 1:");
  printf("Plesase input your project name\n");
  printf("For example: my-gather\n");
  printf("Your project name:");
  fgets(record.name, sizeof(record.name), stdin);
  printf("Step 2:");
  printf("Plesase input your project author\n");
  printf("For example: pie\n");
  printf("Your name:");
  fgets(record.author, sizeof(record.author), stdin);
  printf("Step 3:");
  printf("Plesase input your project version\n");
  printf("For example: 0.0.1\n");
  printf("Your version:");
  fgets(record.version, sizeof(record.version), stdin);
  printf("Step 4:");
  printf("Plesase input your connect program\n");
  printf("For example: connect.out\n");
  printf("Your connect program:");
  fgets(record.connect_program, sizeof(record.connect_program), stdin);
  DeleteCharacter(record.name, '\n');
  DeleteCharacter(record.author, '\n');
  DeleteCharacter(record.version, '\n');
  DeleteCharacter(record.connect_program, '\n');
  WriteNoteFile("install.note", &record);
  return CV_SUCCESS;
}
