/*------------------------------------------------------
*
*
* dng.c
* The main part of the DNG program
* 
* src/dng.c
*
* Portions Copyright 2021 (c) Public Domain
*
*
*-------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "include/dng_file.h"

#define FILE_VERSION "version.txt"
#define FILE_HELP "helpmsg.txt"
#define DEBUG

int main(int argc,char *argv[])
{
	if(1 == argc)/* Without arguments */
	{
		file_echo(FILE_HELP);	
	}
	else
	{
		switch(argc)
		{
			case 2:
				{
					if(!strcmp(argv[1],"-v"))
					{
						file_echo(FILE_VERSION);	
					}
					else if(!strcmp(argv[1],"--help"))
					{
						file_echo(FILE_HELP);
					}
					else if(!strcmp(argv[1],"execute"))
					{
						DIR *dir = NULL;/* installed */	
						struct dirent *installeddir = NULL;
						char filednfcalls[MAX_BUFFER] = "";
						dir = opendir("./installed/");
						if(NULL == dir)
						{
							puts("Error: Can't open the installed floder");
							exit(-1);
						}
						while(installeddir = readdir(dir))
						{
							if(DT_DIR == (installeddir -> d_type))
							{
								#ifdef DEBUG
									puts(installeddir -> d_name);
								#endif
								sprintf(filednfcalls,"./installed/%s/.dnfcalls",installeddir -> d_name);
								file_execute(filednfcalls);/* execute script */
							}
						}
						closedir(dir);
						dir = NULL;
						puts("Complete!");
					}
					break;
				}
			case 3:
				{
					if(!strcmp(argv[1],"remove"))
					{
						char syscalls[MAX_BUFFER] = "";
						sprintf(syscalls,"rm -f -r ./installed/%s",argv[2]);
						system(syscalls);
						puts("Complete!");
					}
					break;
				}
			default:
				{
					if(!strcmp(argv[1],"install"))
					{
						if(!file_exist(argv[2]))
						{
							/*
							FILE *fp = fopen("record.dnf.ini","w");
							if(NULL == fp)
							{
								puts("Fail:Create record file");
								exit(-1);
							}
							*/
							{
								char dirname[MAX_BUFFER] ="./installed/";
								strcat(dirname,argv[2]);
								if(mkdir(dirname,0777))
								{
									puts("Notice:Create floder failed");/* May installed and the dirtion exists  */
								}
							}
							{
								char filednfcallsname[MAX_BUFFER] = "";
								FILE *dnfcalls = NULL;
								sprintf(filednfcallsname,"./installed/%s/.dnfcalls",argv[2]);
								#ifdef DEBUG
									puts(filednfcallsname);
								#endif
								if(!(dnfcalls = fopen(filednfcallsname,"w")))
								{
									puts("Fail:Create dnfcall file");
									exit(-1);
								}
								{
									char program_arguments[MAX_BUFFER] = "";
									char execute_arguments[MAX_BUFFER] = "";
									char program[MAX_BUFFER] = "";
									char execute[MAX_BUFFER] = "";
									if(argc <= 4)
									{
										puts("Error: You should give execute program");
										exit(-1);
									}
									strcpy(program,argv[3]);
									if(!strcmp(argv[4],"-a"))/* dng install name program -a ... */
									{
										if(argc <= 6)
										{
											puts("Error: You should give arguments");
											exit(-1);
										}
										strcpy(program_arguments,argv[5]);
										#ifdef DEBUG
											puts("program_arguments:");
											puts(program_arguments);
										#endif
										/* dng install name program -a "Command" execute [ -a ["Command"] ] */
										{
											strcpy(execute,argv[4]);
											if(argc <= 7)/* dnf install name program execute */
											{
												;/* Just do nothing */
											}
											else
											{
												if(!strcmp(argv[7],"-a"))
												{
													strcpy(execute_arguments,argv[8]);
													#ifdef DEBUG
														puts(execute_arguments);
													#endif
												}
											}
										}
									}
									else
									{
										strcpy(execute,argv[4]);
										if(argc <= 5)/* dnf install name program execute */
										{
											;/* Just do nothing */
										}
										else
										{
											if(!strcmp(argv[5],"-a"))
											{
												if(argc <= 6)
												{
													puts("Error: You should give arguments");
													exit(-1);
												}
												strcpy(execute_arguments,argv[6]);
												#ifdef DEBUG
													puts(execute_arguments);
												#endif
											}
										}
									}
									/* copy script to installed */
									char syscalls[MAX_BUFFER] = "";
									char scriptname[MAX_BUFFER] = "";
									getscriptname(scriptname,program);
									sprintf(syscalls,"cp %s %s",program,scriptname);
									system(syscalls);
									/* execute [execute arguments] program(script) [program_arguments] */
									fprintf(dnfcalls,"%s %s %s %s",execute,execute_arguments,scriptname,program_arguments);
									fflush(dnfcalls);
									#ifdef DEBUG
										puts("string:");
										printf("%s|%s|%s|%s\n",execute,execute_arguments,program,program_arguments);
										puts("content:");
										file_echo(filednfcallsname);
									#endif
									/*
									int i = 2;
									while((++i) < argc)
									{
										#ifdef DEBUG
											puts(argv[i]);
										#endif
											
									}
									*/
								}
								fclose(dnfcalls);
								dnfcalls = NULL;
								puts("Complete!");
							}
							
						}
					}
					break;
				}
		}
	}
	return 0;
}
