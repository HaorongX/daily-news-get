#ifndef DNG_PUBLIC_TYPE
#define DNG_PUBLIC_TYPE
#include "public_define.h"
typedef char* CodeValue;
typedef int CodeStatus;
typedef int FileType;
typedef struct _NoteRecord
{
  char name[BUFFER_LENGTH];
  char author[BUFFER_LENGTH];
  char version[BUFFER_LENGTH];
  char connect_program[BUFFER_LENGTH];
}NoteRecord, *PNoteRecord;
typedef struct _FunctionObjectData
{
  CodeValue (*function)(void *arguments, void *extern_information);
  char command[COMMAND_MAXLENGTH];
}FunctionObjectData, *PFunctionObjectData;
typedef struct _FunctionObject
{
  FunctionObjectData function_object_data;
  struct _FunctionObject *next;
}FunctionObject, *PFunctionObject;
typedef struct _FunctionObjects
{
  PFunctionObject first;
  PFunctionObject last;
  FunctionObjectData data;
}FunctionObjects, *PFunctionObjects, FunctionRules, *PFunctionRules;
typedef struct _FileInfo
{
  char path[PATH_MAXLENGTH];
  char name[PATH_MAXLENGTH];
  FileType type;
}FileInfo;
#endif
