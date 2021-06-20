/*------------------------------------------------------
*
*
* dng_string.c
* Provide some string function
* Achieve src/include/dng_string.h
* 
* src/dng_string.c
*
* Portions Copyright 2021 (c) Public Domain
*
*
*--------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include "include/dng_string.h"

#undef DEBUG /* Already works well */

int getcharpositionbehind(char *string,char c)
{
	int position = strlen(string);
	if(position <= 0)
	{
		return -1;
	}
	while(string[position] != c)
	{
		position--;
	}
	return position;
}
void getscriptname(char *dest,char *source)
{
	int position = getcharpositionbehind(source,'/');
	int length = strlen(source) - position;
	#ifdef DEBUG
		printf("position = %d\n",position);
		printf("length = %d\n",length);
	#endif
	if(source[0] == '\'')
	{
		length--;
	}
	strncpy(dest,(source + position) + 1,length);
	#ifdef DEBUG
		puts("source:");
		puts(source);
		puts("dest:");
		puts(dest);
	#endif
	return ;
}
