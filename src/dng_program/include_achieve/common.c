/*------------------------------------------------------------------------------------
 *       
 *     common.c
 *          achieve the function of common.h
 *   
 *      Directory
 *          src/dng_program/common.c
 *      
 *      Portions Copyright (c) Public Domain
 *------------------------------------------------------------------------------------*/
#include "../include/common.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
/*
    Copy file
*/
int 
CopyBinaryFile(const char *dest, const char *source)
{
    char command[MAX_BUFFER] = {0};

    return 0;
}
/*
    Change program work directory
*/
int 
ChangeWorkDirectory(const char *path)
{
    return chdir(path);
}
/*
    Get the last character position from string
 */
int
GetLastCharacterPosition(const char *str, char c)
{
    int position = 0;
    position = strlen(str);
    
    while((*(str + position) != c) && (position > 0))
        position--;
    
    return position;
}
/*
    Get the path of program.
    Return value
    0 success
    -1 failure
*/
int 
GetProgramSelfFullPath(char *path,int size)
{
    if(-1 ==  readlink("/proc/self/exe",path,size))
    {
        return -1;
    }
    return 0;
}
/*
    Get the last character position from string
    Return Value
    0 success
    -1 failure
*/
int 
GetProgramSelfPath(char *dest,int size)
{
    int position = 0;
    int length = 0;
    
    if(-1 ==  readlink("/proc/self/exe",dest,size))
        return -1;
    
    length = strlen(dest);
    position = GetLastCharacterPosition(dest, '/');
    for(int i = length > size ? size : length;i > position;i--)
        *(dest + position) = '\0';
    return 0;
}
/*
    Just to test the code, it must be deleted.
*/

