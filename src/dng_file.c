/*------------------------------------------------------
*
*
* dng_file.c
* Provide some file function
* Achieve src/include/dng_file.h
*
* src/dng_file.c
*
* Portions Copyright 2021 (c) Public Domain
*
*
*--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "include/dng_file.h"

#undef DEBUG /* Already works well */

void
file_execute(const char *name)
/*
	Call the system command to execute a file content
*/
{
    FILE *fp = NULL;
    char command[MAX_BUFFER] = "";

    fp = fopen(name,"r");
         if(NULL == fp)
             return ;

    while(fgets(command,MAX_BUFFER,fp))
        system(command);

    fclose(fp);
    fp = NULL;
}
int
file_exist(const char *name)
/*
	Try to switch the status of file
	Return :
	FILE_EXIST
	FILE_UNEXIST
	-1
*/
{
    FILE *fp = NULL;

    fp = fopen(name,"r");

    if(NULL == fp)
        return FILE_UNEXIST;

    else
    {
        fclose(fp);
        return FILE_EXIST;
    }

    /* Failure out of expect */
    return -1;
}
void 
file_echo(const char *name)
/*
    Type a txt file content
*/
{
    FILE *file = NULL;
    int c = 0;
    
    file = fopen(name,"r");
    
    if(NULL == file)
    {
        
#ifdef DEBUG
        printf(name);
        puts(" not found");
#endif
        return ;
    }
    
    while(EOF != (c = fgetc(file)))
        putchar(c);
    
    return ;
}

