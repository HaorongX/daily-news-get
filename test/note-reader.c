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

typedef struct _NoteRecord
{
  char name[256];
  char author[256];
  char version[256];
  char connect_program[256];
}NoteRecord, *PNoteRecord;
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
  fscanf(fp, "# %s", result -> name);
  fgets(temp, 31, fp);
  fscanf(fp, "    %% %s", result -> author);
  fgets(temp, 31, fp);
  fscanf(fp, "    %% %s", result -> version);
  fgets(temp, 31, fp);
  fscanf(fp, "    %% %s", result -> connect_program);
  fclose(fp);
  return result;
}
int
main(int argc, char **argv)
{
  PNoteRecord p = NULL;
  printf("%u",3333);
  p = LoadNoteFile("install.note");
  printf("%u",p);
  puts("???");
  puts(p -> author);
  return 0;
}
