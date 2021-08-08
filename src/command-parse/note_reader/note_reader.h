#ifndef NOTE_READER_H
#define NOTE_READER_H
#include "../public/public.h"
#include <stdio.h>
/*****************************************************************
 *
 *  DNG Project
 *    Daily News Gather
 *
 *  note_reader.h
 *    Define the function to read the install.note
 *
 *  Copyright Public Domain 2021
 *
 *
 *****************************************************************/
typedef struct _NoteRecord
{
  char name[NOTE_MAX_LENGTH];
  char author[NOTE_MAX_LENGTH];
  char version[NOTE_MAX_LENGTH];
  char connect_program[NOTE_MAX_LENGTH];
}NoteRecord, *PNoteRecord;
void WriteNoteFile(char *filename, PNoteRecord info);
void DeleteCharacterFromStringFromString(char *string, char character);
PNoteRecord LoadNoteFile(char *filename);
void FreeNoteFile(PNoteRecord file);
#endif
