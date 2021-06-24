/*------------------------------------------------------------------------------------
 *       
 *     dng_list.c  
 *          list the scripts installed
 *   
 *      Directory
 *          src/dng_program/dng_list/dng_list.c
 *      
 *      Portions Copyright (c) Public Domain
 *------------------------------------------------------------------------------------*/
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include "../include/dng.h"
int
main()
{
    if(0 != InitWorkEnviroment())
    {
        puts("Error: Initiative failed!");
        exit(-1);
    }
    return 0;
}
