/*------------------------------------------------------------------------------------
 *       
 *     dng_installed_scripts_status.c  
 *          improve the scripts status
 *   
 *      Directory
 *          src/dng_program/dng_installed_scripts_status/dng_installed_scripts_status.c
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
