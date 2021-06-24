/*------------------------------------------------------------------------------------
 *       
 *     dng_remove.c  
 *          remove the scripts
 *   
 *      Directory
 *          src/dng_program/dng_remove/dng_remove.c
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
