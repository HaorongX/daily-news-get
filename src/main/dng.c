/*------------------------------------------------------------------------------------
 *       
 *     dng.c  
 *          command parse
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
#include "library/dng.h"
#define DNG_COMMAND_FILE_NAME "dngcommand.record"
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
    if(narg > main_argc)
    {
        return ;
    }
    /* According to experience, argv[0] always is the full path of execture program itself*/
    for(int i = narg - 1;i < main_argc;i++)
    {
        strcat(dest,main_argv[i]);
        strcat(dest," ");
    }
    return ;
}
/*
    SearchDNGConversionRelations : Search the match rule
    Return value
    a point to rule => success
    NULL => failure
*/
ConversionRelations *
SearchDNGConversionRelations(ConversionRelations *table, const char *command)
{
    ConversionRelations *temp = NULL;
    bool flag_of_match = false;
    temp = table -> first;
	while(NULL != temp)
    {
        if(0 == strcmp(temp -> command, command))
        {
            flag_of_match = true;
            break;
        }
        temp = temp -> current -> next;
    }
    if(flag_of_match)
    {    
        return temp;
    }
    return NULL;
}
/*
    SaveDNGConversionRelationsMemoryToFile : Save the data to .dngcommand
    Return value
    void
*/
void
SaveDNGConversionRelationsMemoryToFile(const char *name, ConversionRelations *table)
{
    ConversionRelations *temp = NULL;
    FILE *dng_command_file = NULL;
    dng_command_file = fopen(name, "w+");
    temp = table -> first;
	while(NULL != temp)
    {
        fprintf(dng_command_file, "[record]\n%s => %s\n", temp -> current -> command, temp -> current -> program_full_path);
        temp = temp -> next;
    }
    fflush(dng_command_file);
    fclose(dng_command_file);
    dng_command_file = NULL;
    return ;
}
/*
    UpdateDNGConversionRelations : Update the DNG record in memory
    Return value
    void
*/
void
UpdateDNGConversionRelations(ConversionRelations *table, const char *command,const char *program_full_path)
{
    ConversionRelations *dest = NULL;
    if(NULL == (dest = SearchDNGConversionRelations(table, command)))
    {
        return ;
    }
    sprintf(dest -> current -> command, "%s", command);
    sprintf(dest -> current -> program_full_path, "%s", program_full_path);
    return ;
}
/*  FreeConversionRelationsMemory : Free the resource it used 
    Return value
    void
*/
void
FreeConversionRelationsMemory(ConversionRelations *table)
{
    ConversionRelations *temp = NULL, *temp1 = NULL;
    temp = table -> first;
    while(NULL != temp -> next)
    {
        temp1 = temp -> current -> next;
        free(temp -> current);
        temp = temp1;
    }
    temp = NULL;
    table = NULL;
    return ;
}
/*
    DNGCommandParse : Parse the command and execute
    Return value
    1 => match
    0 => nothing matched
*/
int
DNGCommandParse(ConversionRelations *table, const char *command, const char *arguments)
{
    ConversionRelations *rule = NULL;
    char final_command[1024] = {0};
    rule = SearchDNGConversionRelations(table, command);
    if(NULL == rule)
    {
        return 0;
    }
    sprintf(final_command,"%s %s", rule -> current -> program_full_path, arguments);
    system(final_command);
    return 0;
}
/*
	LoadDNGCommandFile : Load the .dngcommand file to program
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
    CloseDNGCommandFile : Free the .dngcommand file resource
    Return value
    void
*/
void
CloseDNGCommandFile(FILE *fp)
{
    fclose(fp);
    fp = NULL;
}
/*
    AddCommandRelation : Add a record to table
    Return value
    0 => success
    -1 => failure
*/
int
AddCommandRelation(ConversionRelations *table, char *command, char *program_full_path)
{
    ConversionRelations *temp = NULL;
    if(NULL != SearchDNGConversionRelations(table, command))
    {
        return -1;/* Already exist */
    }
    if(NULL == (temp = (ConversionRelations*)calloc(sizeof(ConversionRelations),1)))
    {
        return -1;
    }
	temp -> current = temp;
    sprintf(temp -> command, "%s", command);
	sprintf(temp -> program_full_path, "%s", program_full_path);
    if(NULL == table -> first)
	{
		if(NULL == (table -> first = (ConversionRelations*)calloc(sizeof(ConversionRelations),1)))
		{
			return -1;
		}
		temp -> first = table;
		memcpy(table, temp, sizeof(ConversionRelations));
		table -> current = table;
	}
	else
	{
		temp -> first = table -> first;
		table -> next = temp;
		table = temp;
	}
	return 0;
}
/*
 *   ConventDNGCommandFileContentToMemory : Load the content to memory
 *   Return value
 *   a point to date table => success
 *   NULL => failure
 */
ConversionRelations *
ConventDNGCommandFileContentToMemory(FILE *fp)
{
	ConversionRelations *table = NULL, *temp = NULL;
	char command[16] = {0};
	char program_full_path[512] = {0};
	int result_of_fscanf = 0;
	if(NULL == (table = (ConversionRelations*)calloc(sizeof(ConversionRelations), 1)))
	{
		return NULL;
	}
	while(true)
	{
		/* 2 means the normal condition, the program read the right data successly */
		if(2 != (result_of_fscanf = fscanf(fp, "[record]\n%s => %s\n", command, program_full_path)))
		{
			break;
		}
		AddCommandRelation(table, command, program_full_path);
	}
	return table;
}
/*
    RemoveCommandRelation : Remove a parse rule
    Return value
    0 => success
    -1 => failure
*/
int 
RemoveCommandRelation(ConversionRelations *table,const char *command)
{
    ConversionRelations *dest = NULL, *temp = NULL, *temp1 = NULL;
    if(NULL == (dest = SearchDNGConversionRelations(table, command)))
    {
        return -1;
    }
    temp = table -> first;
    while((NULL != temp -> next) && temp -> next != dest)
    {
        temp = temp -> next;
    }
    temp1 = dest -> next;
    temp -> next = temp1;
    free(dest);
    dest = NULL;
    return 0;
}
/*
    main : The main part of the program
    Built-in command
    parse-add command program
        Add a record to file
    parse-remove command program
        Remove a record
    parse-update command program
        Change a record
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
	ConversionRelations *table = NULL;
    char arguments[1024] = {0};
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
    if(NULL == (dng_command_file = LoadDNGCommandFile(DNG_COMMAND_FILE_NAME)))
    {
        puts("Error : Can't load the dng command file");
        exit(-1);
    }
    /* Analyse the file content */
    if(NULL == (table = ConventDNGCommandFileContentToMemory(dng_command_file)))
    {
        puts("Error : Can't analyse the file content");
        exit(-1);
    }
    /* Parse the command */
    /* For built-in command */
    if(0 == strcmp(argv[1], "parse-add"))
    {
        AddCommandRelation(table, argv[2], argv[3]);
        CloseDNGCommandFile(dng_command_file);
        SaveDNGConversionRelationsMemoryToFile(DNG_COMMAND_FILE_NAME, table);
    }
    else if(0 == strcmp(argv[1], "parse-remove"))
    {
        RemoveCommandRelation(table, argv[2]);
        CloseDNGCommandFile(dng_command_file);
        SaveDNGConversionRelationsMemoryToFile(DNG_COMMAND_FILE_NAME, table);
    }
    else if(0 == strcmp(argv[1], "parse-update"))
    {
        /* Equal to parse-add with parse-remove */
        RemoveCommandRelation(table, argv[2]);
        AddCommandRelation(table, argv[2], argv[3]);
        CloseDNGCommandFile(dng_command_file);
        SaveDNGConversionRelationsMemoryToFile(DNG_COMMAND_FILE_NAME, table);
    }
    /* Not the built-in command */
    else
    {
        CombineMainFunctionArguments(arguments, argc, argv, 3);
        if(0 == DNGCommandParse(table, argv[1], arguments))
        {
            printf("Sorry, can't match the command.\n");
            printf("Try 'dng --help' for more information.\n");
        }
    }
    /* Free the memory resource */
    FreeConversionRelationsMemory(table);
    return 0;
}
