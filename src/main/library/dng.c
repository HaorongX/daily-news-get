/*------------------------------------------------------------------------------------
 *       
 *     dng.c
 *          achieve the function of common.h
 *   
 *      Directory
 *          src/dng_program/common.c
 *      
 *      Portions Copyright (c) Public Domain
 *------------------------------------------------------------------------------------*/
#include "../library/dng.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
/*
    InitWorkEnviroment : Set the right work directory
    Return Value
    0 => csuccess
    -1 => failure
*/
int
InitWorkEnviroment(void)
{
    char path[MAX_BUFFER] = {0};
    if(-1 == GetProgramSelfPath(path, sizeof(path)))
    {
        return -1;
    }
    if(0 != chdir(path))/* 0 means success in chdir function */
    {
        return -1;
    }
    return 0;
}
/*
    ChangeWorkDirectory : Change program work directory
*/
int 
ChangeWorkDirectory(const char *path)
{
    return chdir(path);
}
/*
    GetLastCharacterPosition : Get the last character position from string
    Return value
    the position of the character
*/
int
GetLastCharacterPosition(const char *str, char c)
{
    int position = 0;
    position = strlen(str);
    while((*(str + position) != c) && (position > 0))
    {    
        position--;    
    }
    return position;
}
/*
    GetProgramSelfFullPath : Get the path of program with program name
    Return value
    0 => success
    -1 => failure
*/
int 
GetProgramSelfFullPath(char *path, int size)
{
    if(-1 ==  readlink("/proc/self/exe",path,size))
    {
        return -1;
    }
    return 0;
}
/*
    GetProgramSelfPath : the last character position from string
    Return Value
    0 success
    -1 failure
*/
int 
GetProgramSelfPath(char *dest, int size)
{
    int position = 0;
    int length = 0;
    if(-1 ==  readlink("/proc/self/exe", dest, size))
    {    
        return -1;
    }
    length = strlen(dest);
    position = GetLastCharacterPosition(dest, '/');
    for(int i = length > size ? size : length;i > position;i--)
    {
        *(dest + position) = '\0';
    }
    return 0;
}
