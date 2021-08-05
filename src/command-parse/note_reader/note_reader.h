#ifndef NOTE_READER_H
#define NOTE_READER_H
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
  char name[256];
  char author[256];
  char version[256];
  char connect_program[256];
}NoteRecord, *PNoteRecord;
void DeleteCharacterFromStringFromString(char *string, char character);
PNoteRecord LoadNoteFile(char *filename);
#endif
