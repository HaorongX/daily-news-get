/*------------------------------------------------------------------------------------
 *       
 *     dng.c  
 *          install & remove & execute the scripts
 *   
 *      Directory
 *          src/dng_program/dng.c
 *      
 *      Portions Copyright (c) Public Domain
 *------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/dng.h"
/*
    To combine main function 'argv' to single string
    Only use for main
    No return value
    for example:
    Program -call script argument_1 argument_2
    The total argc = 5
    and call this function to:
    char command[1024] = {0};// Assume the max string length will be 1024
    CombineMainFunctionArguments(command,5,argv,3);
    If will create "script argument_1 argument_2" when success.
*/
/*
    Note : 
    make sure that the (narg - 1) will be the right position to the array
    The 'narg' at least be 2
*/
void 
CombineMainFunctionArguments(char *dest, int argc, char **argv, int narg)
{
    int i = narg - 1;
    /* According to experience, argv[0] always is the full path of execture program itself*/
    printf("i = %d argc = %d\n",i,argc);
    if(i <= 0)
    {
        return ;
    }
    while(i < argc)
    {
        printf("%s %d\n",dest,i);
        strcat(dest,argv[i]);
        strcat(dest," ");
        i++;
        puts(dest);
    }
}
int 
main(int argc, char **argv)
{
    char program_call_full_command[MAX_BUFFER] = {0};
    if(0 != InitWorkEnviroment())
    {
        puts("Error: Initiative failed!");
        exit(-1);
    }
    CombineMainFunctionArguments(program_call_full_command,argc,argv,2);
    puts(program_call_full_command);
    return 0;
}
