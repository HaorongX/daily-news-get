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
#include "../public/public.h"
#include <stdio.h>
#define DNG_NOTE_MAKER_VERSION "0.0.2"
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
  NoteRecord record = {0};
  printf("DNG -- install.note maker\n");
  printf("Version:%s\n", DNG_NOTE_MAKER_VERSION);
  printf("第一步:\n");
  printf("你的项目名称:");
  fgets(record.name, sizeof(record.name), stdin);
  printf("第二步:\n");
  printf("你的名字:");
  fgets(record.author, sizeof(record.author), stdin);
  printf("第三步:\n");
  printf("项目版本号:");
  fgets(record.version, sizeof(record.version), stdin);
  printf("第四步:\n");
  printf("请输入通讯程序名称:");
  fgets(record.connect_program, sizeof(record.connect_program), stdin);
  DeleteCharacter(record.name, '\n');
  DeleteCharacter(record.author, '\n');
  DeleteCharacter(record.version, '\n');
  DeleteCharacter(record.connect_program, '\n');
  WriteNoteFile(DNG_EXTENSION_RECORD_FILE, &record);
  return CV_SUCCESS;
}
