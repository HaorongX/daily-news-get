/*------------------------------------------------------------------------------------
 *       
 *     dng_help.c  
 *          provide help infomation to user
 *   
 *      Directory
 *          src/dng_program/dng_help/dng_help.c
 *      
 *      Portions Copyright (c) Public Domain
 *------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dng.h"

/*
    Type a txt file content
    Return value:
    0 success
    -1 failure
*/
int 
FileEcho(const char *filename)
{
    FILE *fp = NULL;
    int c = 0;
    if( !( fp = fopen(filename , "r") ) )
    {
        return -1;
    }
    while(EOF != (c = fgetc(fp)))
    {
        putchar(c);
    }
    fclose(fp);
    return 0;
}
int main(int argc,char **argv)
{
    if(0 != InitWorkEnviroment())
    {
        puts("Error: Initiative failed!");
        exit(-1);
    }
    if(argc == 1) /* Equal to '-h' */
    {
        if(-1 == FileEcho("dng_help.txt"))
        {
            puts("Error : Fail to print the help infomation");
            exit(-1);
        }
    }
    if(argc > 1)
    {
        if(!strcmp(argv[1], "-v") || !strcmp(argv[1], "-V"))
        {
            FileEcho("dng_version.txt");
        }
        else if(!strcmp(argv[1], "-h"))
        {
            if(-1 == FileEcho("dng_help.txt"))
            {
                puts("Error : Fail to print the help infomation");
                exit(-1);
            }
        }
        else
        {
            printf("DNG Helper\n");
            printf("usage:\n");
            printf("dng_help -v get the dng version\n");
            printf("dng_help -h get the help dng infomation");
        }
    }
    return 0;
}
