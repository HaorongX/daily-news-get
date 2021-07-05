#ifndef DNG_H
#define DNG_H
/*------------------------------------------------------------------------------------
 *       
 *      dng.h 
 *          collect all DNG project library
 *   
 *      Directory
 *          src/dng_program/include/library.h
 *      
 *      Portions Copyright (c) Public Domain
 *------------------------------------------------------------------------------------*/
#define MAX_BUFFER 1024

int GetProgramSelfFullPath(char *path, int size);
int GetLastCharacterPosition(const char *str, char c);
int GetProgramSelfPath(char *path, int size);
int ChangeWorkDirectory(const char *path);
int InitWorkEnviroment(void);
#endif
