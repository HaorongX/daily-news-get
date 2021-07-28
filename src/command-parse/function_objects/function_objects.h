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
#define CV_FAILURE 1256
#define CV_SUCCESS 0
#define COMMAND_MAXLENGTH 64
typedef int CodeValue;
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
PFunctionObject CreateFunctionObject(CodeValue (*function)(void *arguments, void *extern_information), char *command);
PFunctionObjectData CreateFunctionObjectData(CodeValue (*function)(void *arguments, void *extern_information), char *command);
PFunctionRules CreateFunctionRules(void);
CodeValue AddFunctionRule(PFunctionRules rules, CodeValue (*function)(void *arguments, void *extern_information), char *command);
CodeValue CallFunction(PFunctionRules rules, char *command, void *arguments, void *extern_information);
CodeValue CleanFunctionRule(PFunctionRules rules);
