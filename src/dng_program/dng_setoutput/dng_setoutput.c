/*------------------------------------------------------------------------------------
 *       
 *     dng_setoutput.c  
 *          set the output destingnish of the gather tools.
 *   
 *      Directory
 *          src/dng_program/dng_setoutput/dng_setoutput.c
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
