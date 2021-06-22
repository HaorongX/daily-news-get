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

int
getcharpositionbehind(char *string,char c)
/*
	To get the char first place from last
	I designed this function
	For example:
	'home/test.c'
	If you call it like getcharpositionbehid("home/test.c",'/')
	The function will return the position of the char '/'

	NOTE:
		-1 means Failure
*/
{
    int position = 0;
    
    position = strlen(string);
    if(position <= 0)
        return -1;

    while(string[position] != c)
        position--;
    
    return position;
}
void
getscriptname(char *dest,char *source)
/*
	Design to het the scriptname
	It better named " getfullfilenamebydirname "
	Because it dosen't rule the file type.
	I will rename the function.
*/
{
    int position = 0;
    int length = 0;
    
    position = getcharpositionbehind(source,'/');
    if(-1 == position)/* Failure */
        return ;
        
    length = strlen(source) - position;
    
#ifdef DEBUG
    printf("position = %d\n",position);
    printf("length = %d\n",length);
#endif

    if(source[0] == '\'')
        length--;
    
    strncpy(dest,(source + position) + 1,length);

#ifdef DEBUG
    puts("source:");
    puts(source);
    puts("dest:");
    puts(dest);
#endif

    return ;
}
