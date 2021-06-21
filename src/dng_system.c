/*------------------------------------------------------
*
*
* dng_system.c
* To update the enviroment
* Achieve the dng_system.h
*
* src/dng_system.c
*
* Portions Copyright 2021 (c) Public Domain
*
*
*-------------------------------------------------------*/
#include <string.h>
#include <unistd.h>
#include "include/dng_string.h"
#include "include/dng_system.h"

#define MAX_BUFFER (1024)

void
initworkdir(const char *argv_arguments /* should be argv[0] */ )
/*
    This function assume that agrv[0] always include the program dng's dirname + filename
 */
{
    char executedir[MAX_BUFFER] = "";
    
    strncpy(executedir,argv_arguments,strlen(argv_arguments) - strlen("dng.out"));
    
    chdir(executedir);
    return ;
}
