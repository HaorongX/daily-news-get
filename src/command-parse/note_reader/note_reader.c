/*****************************************************************
 *
 *  DNG Project
 *    Daily News Gather
 *
 *  note_reader.c
 *    Achieve the function of note_reader.h
 *
 *  Copyright Public Domain 2021
 *
 *
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "note_reader.h"
/*
    DeleteCharacterFromString

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
DeleteCharacterFromStringFromString(char *string, char character)
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
    LoadNoteFile

    Describle:
      Load a note file

    Arguments:
      filename
        The note file name

     Return value:
       The point to install.note
*/
PNoteRecord
LoadNoteFile(char *filename)
{
  FILE *fp = NULL;
  PNoteRecord result = NULL;
  char temp[32] = {0};
  fp = fopen(filename, "r");
  if(NULL == fp)
    return NULL;
  result = (PNoteRecord)calloc(1, sizeof(NoteRecord));
  if(NULL == result)
    {
      fclose(fp);
      return NULL;
    }
  fgets(temp, 3, fp);
  fgets(result -> name, 255, fp);
  fgets(temp, 31, fp);
  fgets(temp, 7, fp);
  fgets(result -> author, 255, fp);
  fgets(temp, 31, fp);
  fgets(temp, 7, fp);
  fgets(result -> version, 255, fp);
  fgets(temp, 31, fp);
  fgets(temp, 7, fp);
  fgets(result -> connect_program, 255, fp);
  fclose(fp);
  DeleteCharacterFromStringFromString(result -> name, '\n');
  DeleteCharacterFromStringFromString(result -> author, '\n');
  DeleteCharacterFromStringFromString(result -> version, '\n');
  DeleteCharacterFromStringFromString(result -> connect_program, '\n');
  return result;
}
