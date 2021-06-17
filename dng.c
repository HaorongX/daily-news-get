#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_VERSION "version.txt"
#define FILE_README "readme.txt"
#define FILE_HELP "helpmsg.txt"
#define FILE_EXIST (1)
#define FILE_UNEXIST (0)
#define MAX_BUFFER (1024)
#define DEBUG
int getcharpositionbehind(char *string,char c)
{
	int position = strlen(string);
	if(position <= 0)
	{
		return -1;
	}
	while(string[position] != c)
	{
		position--;
	}
	return position;
}
void getscriptname(char *dest,char *source)
{
	int position = getcharpositionbehind(source,'/');
	int length = strlen(source) - position;
	#ifdef DEBUG
		printf("position = %d\n",position);
		printf("length = %d\n",length);
	#endif
	if(source[0] == '\'')
	{
		length--;
	}
	strncpy(dest,(source + position) + 1,length);
	#ifdef DEBUG
		puts("source:");
		puts(source);
		puts("dest:");
		puts(dest);
	#endif
	return ;
}
int file_exist(char *name)
{
	FILE* fp = fopen(name,"r");
	if(NULL == fp)
	{
		return FILE_UNEXIST;
	}
	else
	{
		fclose(fp);
		return FILE_EXIST;
	}
	return 0;
}
void file_echo(char *name)
{
	FILE *file = NULL;
	int c = 0;
	file = fopen(name,"r");
	if(NULL == file)
	{
		printf(name);
		puts(" not found");
		return ;
	}
	while(EOF != (c = fgetc(file)))
	{
		putchar(c);
	}
	return ;
}
int main(int argc,char *argv[])
{
	if(1 == argc)/* Without arguments */
	{
		file_echo(FILE_VERSION);
		file_echo(FILE_HELP);	
	}
	else
	{
		switch(argc)
		{
			case 2:/*-v --help -list -all -name*/
				{
					if(!strcmp(argv[1],"-v"))
					{
						file_echo(FILE_VERSION);	
					}
					else if(!strcmp(argv[1],"--help"))
					{
						file_echo(FILE_HELP);
					}
					break;
				}
			case 3:/* remove open close -name */
				{
					break;
				}
			default:/* install update -name */
				{
					if(!strcmp(argv[1],"install"))
					{
						if(!file_exist(argv[2]))
						{
							FILE *fp = fopen("record.dnf.ini","w");
							if(NULL == fp)
							{
								puts("Fail:Create record file");
								exit(-1);
							}
							{
								char dirname[MAX_BUFFER] ="./installed/";
								strcat(dirname,argv[2]);
								if(mkdir(dirname,0777))
								{
									puts("Fail:Create Floder");
									exit(-1);
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
									int i = 0;
									while((++i) < argc)
									{
										#ifdef DEBUG
											puts(argv[i]);
										#endif
									}
								}
							}
							
						}
					}
					break;
				}
		}
	}
	return 0;
}
