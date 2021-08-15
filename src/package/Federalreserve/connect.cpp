#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;
/*
    InitEnviroment

    Describle:
      To make sure the program run in the right track

    Arguments:
      This function needn't any arguments

    Return value:
      0
        Success
     -1
        Failure
*/
int
InitEnviroment(void)
{
  char path[1025] = {0};
  int length = 0;
  /* Get the current work directory */
  if(-1 == readlink("/proc/self/exe",path,1024))
  {
    return -1;
  }
  length = strlen(path);
  while('/' !=  *(path + length))
    {
      *(path + length) = '\0';
      length--;
    }
  if(0 != chdir(path))
    {
      return -1;
    }
  return 0;
}
int
main(int argc, char* argv[])
{
    string command = "python3 ./federalreserve.py ";
    InitEnviroment();
    for (int i = 1;i < argc;++ i)
    {
        command += argv[i];
        command += ' ';
    }
    system(command.c_str());
    return 0;
}
