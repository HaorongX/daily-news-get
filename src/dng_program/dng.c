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
#include <stdbool.h>
#include <string.h>
#include "include/dng.h"
typedef struct _ConversionRelations
{
	char command[16];
	char program_full_path[512];
	struct _ConversionRelations *first;
	struct _ConversionRelations *current;
	struct _ConversionRelations *next;
}ConversionRelations;
/*
    CombineMainFunctionArguments : To combine main function 'argv' to single string
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
/*
    Notice :
    Please focus on the "string"
    "Hello World" => argv[n] = Hello, argv[n+1] = World
*/
void 
CombineMainFunctionArguments(char *dest, int main_argc, char **main_argv, int narg)
{
    /* According to experience, argv[0] always is the full path of execture program itself*/
    for(int i = narg - 1;i < main_argc;i++)
    {
        strcat(dest,main_argv[i]);
        strcat(dest," ");
    }
    return ;
}
/*
	LoadDNGCommandFile : Load the .dngcommand file to program
	Load in readonly mode
	Return value
	A point to the file => success
	NULL => fail
*/
FILE*
LoadDNGCommandFile(const char *name)
{
	return fopen(name, "r");
}
/*
    main : The main part of the program
*/
/*
	How does the DNG command parse works:
        Load the .dngcommand file :
	The format of the file:
	[record]
	command => program	
*/
int 
main(int argc, char **argv)
{
    FILE *dng_command_file = NULL;
	ConversionRelations *table = NULL, *temp = NULL, *temp1 = NULL;
	char command[16] = {0};
	char program_full_path[512] = {0};
    bool flag_of_match = false;
    if(0 != InitWorkEnviroment())
    {
        puts("Error: Initiative failed!");
        exit(-1);
    }
    if(argc <= 1)
    {
        printf("dng : download daily article and output it to file\n");
        printf("Try 'dng --help' for more information.\n");
        return 0;
    }
    /* Load the .dngcommand file */
    if(NULL == (dng_command_file = LoadDNGCommandFile(".dngcommand")))
    {
        puts("Error : Can't load the dng command file");
        exit(-1);
    }
    /* From file content to table */
    if(NULL == (table = (ConversionRelations *)calloc(sizeof(struct _ConversionRelations), 1)))
	{
		puts("Error: Can't allow memory");
		fclose(dng_command_file);
		dng_command_file = NULL;
		exit(-1);
		return -1;
	}
	table -> first = (struct _ConversionRelations *)table; /* That is itself */
	while(2 == fscanf(dng_command_file, "[record]\n%s => %s\n", command, program_full_path))/* Avoid empty file */
	{
        table -> current = (struct _ConversionRelations *)table; /* itself */
        sprintf(table -> current -> command, "%s", command);
        sprintf(table -> current -> program_full_path, "%s", program_full_path);
        table -> next = (struct _ConversionRelations *)calloc(sizeof(struct _ConversionRelations), 1);
        table -> next -> first = table -> first;
        table = (ConversionRelations *)table -> next;
	}
	/* Free the file resource */
    fclose(dng_command_file);
    dng_command_file = NULL;
    /* Search the command and execute it */
	temp = table -> first;
	while(NULL != temp -> next)
    {
        temp = temp -> next;
        if(0 == strcmp(temp -> current -> command, argv[1]))
        {
            flag_of_match = true;
            break;
        }
    }
    /* Parse the command */
    if(flag_of_match)
    {
        char arguments[1024] = {0};
        char command[1024] = {0};
        CombineMainFunctionArguments(arguments, argc, argv, 3);
        sprintf(command,"%s %s", temp -> current -> program_full_path, arguments);
        system(command);
    }
    else
    {
        printf("Sorry, can't match the command.\n");
        printf("Try 'dng --help' for more information.\n");
    }
    /* Free the memory resource */
    temp = table -> first;
	while(NULL != temp)
    {
        temp1 = temp -> current -> next;
        free(temp -> current);
        temp = temp1;
    }
    temp = NULL;
    table = NULL;
    return 0;
}
