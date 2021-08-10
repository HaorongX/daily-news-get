#ifndef DNG_FUNCTION_OBJECTS_H
#define DNG_FUNCTION_OBJECTS_H
/*********************************************************
 *  DNG Project
 *    Daily News Gather
 *
 *  function_objects.h
 *    The header file of function objects library
 *
 *  src/command-parse/function_objects/function_objects.h
 *
 *  Copyright Public Domain 2021
 *
 *********************************************************/
#include "../public/public.h"
PFunctionObject CreateFunctionObject(CodeValue (*function)(void *arguments, void *extern_information), char *command);
PFunctionObjectData CreateFunctionObjectData(CodeValue (*function)(void *arguments, void *extern_information), char *command);
PFunctionRules CreateFunctionRules(void);
CodeValue AddFunctionRule(PFunctionRules rules, CodeValue (*function)(void *arguments, void *extern_information), char *command);
CodeValue CallFunction(PFunctionRules rules, char *command, void *arguments, void *extern_information);
CodeValue CleanFunctionRule(PFunctionRules rules);
#endif
