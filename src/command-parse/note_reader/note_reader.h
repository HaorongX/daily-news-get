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
  char name[512];
  char author[512];
  char version[512];
  char connect_program[512];
}NoteRecord, *PNoteRecord;
void WriteNoteFile(char *filename, PNoteRecord info);
void DeleteCharacterFromStringFromString(char *string, char character);
PNoteRecord LoadNoteFile(char *filename);
void FreeNoteFile(PNoteRecord file);
#endif
