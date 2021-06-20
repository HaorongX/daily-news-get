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

void file_execute(const char *name)
{
	FILE *fp = fopen(name,"r");
	char command[MAX_BUFFER] = "";
	if(NULL == fp)
	{
		return ;
	}
	while(fgets(command,MAX_BUFFER,fp))
	{
		system(command);
	}
	fclose(fp);
	fp = NULL;
}
int file_exist(char *name)
{
	FILE *fp = fopen(name,"r");
	if(NULL == fp)
	{
		return FILE_UNEXIST;
	}
	else
	{
		fclose(fp);
		return FILE_EXIST;
	}
	return 0;
}
void file_echo(char *name)
{
	FILE *file = NULL;
	int c = 0;
	file = fopen(name,"r");
	if(NULL == file)
	{
		printf(name);
		puts(" not found");
		return ;
	}
	while(EOF != (c = fgetc(file)))
	{
		putchar(c);
	}
	return ;
}

