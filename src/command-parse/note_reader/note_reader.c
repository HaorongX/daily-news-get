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
    WriteNoteFile

    Describle:
      Write some content to a note file

    Arguments:
      filename
        A point to the note file
      info
        The content

     Return value:
       No value
*/
void
WriteNoteFile(char *filename, PNoteRecord info)
{
  FILE *fp = NULL;
  fp = fopen(filename, "w");
  fwrite(info, sizeof(NoteRecord), 1, fp);
  fclose(fp);
}
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
  PNoteRecord result = NULL;
  FILE *fp = NULL;
  result = (PNoteRecord)calloc(1, sizeof(NoteRecord));
  if(NULL == result)
    {
      return NULL;
    }
  if(NULL == (fp = fopen(filename, "r")))
    {
      free(result);
      return NULL;
    }
  fread((void**)result, sizeof(NoteRecord), 1, fp);
  fclose(fp);
  return result;
}
/*
    FreeNoteFile

    Describle:
      Free a note file

    Arguments:
      file
        A point to the note file

     Return value:
       No value
*/
void
FreeNoteFile(PNoteRecord file)
{
  free(file);
  file = NULL;
}
