/*********************************************************
 *  DNG Project
 *    Daily News Gather
 *
 *  main.c
 *    The achieve of function objects library
 *
 *  src/command-parse/function_objects/main.c
 *
 *  Copyright Public Domain 2021
 *
 *********************************************************/
#include <stdio.h>
#include "function_objects.h"
#include <stdlib.h>
#include <string.h>
/*
    CreateFunctionObject

    Describle:
      Create a function object

    Arguments:
      function
        A function point to the function
      command
        The corresponding function

    Return value:
      The object of function

    Notice:
      The command should shorter than COMMAND_MAXLENGTH

 */
PFunctionObject
CreateFunctionObject(CodeValue (*function)(void *arguments, void *extern_information), char *command)
{
  PFunctionObject result = NULL;
  if(NULL == (result = (PFunctionObject)calloc(1, sizeof(FunctionObject))))
    {
      return NULL;
    }
  result -> function_object_data.function = function;
  strncpy(result -> function_object_data.command, command, COMMAND_MAXLENGTH);
  return result;
}
/*
    CreateFunctionObjectData

    Describle:
      Create a function object data

    Arguments:
      function
        A function point to the function
      command
        The corresponding function

    Return value:
      The object of function data

    Notice:
      The command should shorter than COMMAND_MAXLENGTH

 */
PFunctionObjectData
CreateFunctionObjectData(CodeValue (*function)(void *arguments, void *extern_information), char *command)
{
  PFunctionObjectData result = NULL;
  if(NULL == (result = (PFunctionObjectData)calloc(1, sizeof(FunctionObjectData))))
    {
      return NULL;
    }
  result -> function = function;
  strncpy(result -> command, command, COMMAND_MAXLENGTH);
  return result;
}
/*
    CreateFunctionRules

    Describle:
      Creeate the function rules

    Arguments:
      no argument require

    Return value:
      The point to function rule

 */
PFunctionRules
CreateFunctionRules(void)
{
  return (PFunctionRules)calloc(1, sizeof(FunctionRules));
}
/*
    AddFunctionRule

    Describle:
      Add a rule to the function rules object

    Arguments:
      rules
        The existed rules object
      function
        The existed function
      command
        The corrosponding command

    Return value:
      The point to function rules

    Notice:

 */
CodeStatus
AddFunctionRule(PFunctionRules rules, CodeValue (*function)(void *arguments, void *extern_information), char *command)
{

  PFunctionObject object = NULL;
  object = CreateFunctionObject(function, command);
  if(object == NULL)
    {
      return ERROR_ALLOC_MEMORY;
    }
  if(NULL == rules -> first)
    {
      rules -> first = object;
      rules -> last = object;
    }
  else
    {
      rules -> last -> next = object;
      rules -> last = object;
    }
  return S_SUCCESS;
}
/*
    CallFunction

    Describle:
      Call Function by string

    Arguments:
      rules
        The existed rules
      command
        The corresponding command

    Return value:
      The function code value

 */
CodeValue
CallFunction(PFunctionRules rules, char *command, void *arguments, void *extern_information)
{
  PFunctionObject temp = NULL;
  temp = rules -> first;
  while(temp != NULL)
    {
      if(0 == strcmp(temp -> function_object_data.command, command))
        {
          return temp -> function_object_data.function(arguments, extern_information);
          break;
        }
      temp = temp -> next;
    }
  return CV_COMMAND_NOT_FOUND;
}
/*
    CleanFunctionRule

    Describle:
      Clean up a function object memory

    Arguments:
      rules
        The existed rules
    Return value:
      The built-in code value

 */
CodeValue
CleanFunctionRule(PFunctionRules rules)
{
  PFunctionObject temp = NULL,temp1 = NULL;
  temp = rules -> first;
  while(temp != NULL)
    {
      temp1 = temp -> next;
      free(temp);
      temp = temp1;
    }
  free(rules);
  return CV_SUCCESS;
}
