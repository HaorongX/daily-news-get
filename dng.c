#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
		file_echo("version.txt");
		file_echo("readme.txt");	
	}
	else
	{
		if(0 == strcmp(argv[1],"-v"))
		{
			
		}
	}
	return 0;
}
