/*------------------------------------------------------------------------------------
 *       
 *     dng_change.c  
 *          update the scripts calls file or script itself
 *   
 *      Directory
 *          src/dng_program/dng_change/dng_change.c
 *      
 *      Portions Copyright (c) Public Domain
 *------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dng.h"

int 
main(int argc, char **argv)
{
    if(0 != InitWorkEnviroment())
    {
        puts("Error: Initiative failed!");
        exit(-1);
    }
    return 0;
}
