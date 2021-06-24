#ifndef DNG_COMMON_H
#define DNG_COMMON_H
/*------------------------------------------------------------------------------------
 *       
 *    common.h 
 *          provide common function to DNG project
 *   
 *      Directory
 *          src/dng_program/include/common.h
 *      
 *      Portions Copyright (c) Public Domain
 *------------------------------------------------------------------------------------*/
#define MAX_BUFFER 1024

int GetProgramSelfFullPath(char *path, int size);
int GetLastCharacterPosition(const char *str, char c);
int GetProgramSelfPath(char *path, int size);
int ChangeWorkDirectory(const char *path);
#endif
