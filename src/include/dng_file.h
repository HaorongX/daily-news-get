#ifndef DNG_FILE_H
#define DNG_FILE_H

/*------------------------------------------------------
*
*
* dng_file.h
* The define of the DNG file function
* 
* src/include/dng_file.h
*
* Portions Copyright 2021 (c) Public Domain
*
*-----------------------------------------------------*/

#define FILE_EXIST (1)
#define FILE_UNEXIST (0)
#define MAX_BUFFER (1024)

void file_execute(const char *name);
int file_exist(const char *name);
void file_echo(const char *name);

#endif
