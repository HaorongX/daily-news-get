#ifndef DNG_COMMAND_H
#define DNG_COMMAND_H
/********************************************
*  DNG Project
*    Daily News Gather
*
*  command.h
*    src/command-parse/command/command.h
*
*  Copyright Public Domain 2021
*
*********************************************/
/* Notice: The CodeValue tyoe defined in function_objects library  */
#include "../function_objects/function_objects.h"
#define CV_USER_FILE_FAILURE 1822
#define CV_USER_LACK_ARGUMENTS 1232
CodeValue Command_help(void *arguments, void *extern_info);
CodeValue Command_version(void *arguments, void *extern_info);
CodeValue Command_install(void *arguments, void *extern_info);
CodeValue Command_remove(void *arguments, void *extern_info);
CodeValue Command_list(void *arguments, void *extern_info);
CodeValue Command_execute(void *arguments, void *extern_info);
CodeValue Command_clean(void *arguments, void *extern_info);
CodeValue Command_check(void *arguments, void *extern_info);
CodeValue Command_note_maker(void *arguments,void *extern_info);
#endif
