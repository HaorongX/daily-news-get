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
#include "../include/dng.h"
#include <unistd.h> /* For chdir */
/*
    To set the right work directory
    Return Value
    0 success
    -1 failure
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
