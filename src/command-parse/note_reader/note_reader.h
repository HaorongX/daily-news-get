#ifndef NOTE_READER_H
#define NOTE_READER_H
#include "../public/public.h"
#include <stdio.h>
#define AccessPackageNoteFile(name) AccessPackageRecord(name)
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
CodeStatus WriteNoteFile(char *filename, PNoteRecord info);
PNoteRecord LoadNoteFile(char *filename);
CodeStatus FreeNoteFile(PNoteRecord file);
PNoteRecord AccessPackageRecord(char *package_name);
#endif
