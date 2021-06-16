#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FILE_VERSION "version.txt"
#define FILE_README "readme.txt"
#define FILE_HELP FILE_README
void file_echo(char* name)
{
	FILE* file = NULL;
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
int main(int argc,char* argv[])
{
	if(1 == argc)/* Without arguments */
	{
		file_echo(FILE_VERSION);
		file_echo(FILE_README);	
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
					break;
				}
		}
	}
	return 0;
}
