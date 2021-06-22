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

void
initworkdir(const char *argv_arguments /* should be argv[0] */ )
/*
    This function assume that agrv[0] always include the program dng's dirname + filename
 */
{
    char executedir[MAX_BUFFER] = "";

#ifdef DEBUG
puts(argv_arguments);
#endif
   
    strncpy(executedir,argv_arguments,strlen(argv_arguments) - strlen("dng.out"));

#ifdef DEBUG
puts(executedir);
#endif
    
    chdir(executedir);
    return ;
}
