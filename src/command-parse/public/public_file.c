#include "public.h"
#include <dirent.h>
#include <string.h>
/*
    CopyDirectory

    Describle:
      Copy a directory

    Arguments:
      path
        The path

    Return value:

*/
CodeStatus
CopyDirectory(char *source, char *dest)
{
  char temp[TEMP_BUFFER_LENGTH] = {0};
  sprintf(temp, "cp -r %s %s", source, dest);
  system(temp);
  return 0;
}
/*
    AccessDirectory

    Describle:
      Access a directory,and call the function

    Arguments:
      path
        The path
      function
        When file access,this function will be called.
      flag
        If some problem happend,stop the execute right now?

      Return value:

*/
CodeStatus
AccessDirectory(char *path, CodeStatus (*function)(FileInfo info, void *arguments), void *arguments,int flag)
{
  DIR *directory = NULL;
  struct dirent *file = NULL;
  FileInfo info = {0};
  CodeStatus status = 0;
  sprintf(info.path,"%s" , path);
  if(NULL == (directory = opendir(path)))
    {
      return ERROR_OPEN_DIRECTORY;
    }
  while(NULL != (file = readdir(directory)))
    {
      if(!strcmp(file -> d_name, "..") || !strcmp(file -> d_name, "."))
        {
          continue;
        }
      sprintf(info.name, "%s", file -> d_name);
      info.type = file -> d_type;
      status = function(info, arguments);
      if(STATUS_CONTINUE != status && flag)
        {
          closedir(directory);
          return status;
        }
    }
  closedir(directory);
  return status;
}
/*
    RemoveDirectory

    Describle:
      Remove a directory

    Arguments:
      path
        The path

    Return value:

*/
CodeStatus
RemoveDirectory(char *path)
{
  char temp[TEMP_BUFFER_LENGTH] = {0};
  sprintf(temp, "rm -f -r %s", path);
  system(temp);
  return 0;
}
/*
    RemoveFile

    Describle:
      Remove a file

    Arguments:
      filename
        The file name

    Return value:

*/
CodeStatus
RemoveFile(char *filename)
{
  return remove(filename);
}
/*
    PrintFileContent

    Describle:
      Print a file content

    Arguments:
      filename
        The file name

    Return value:

*/
CodeStatus
PrintFileContent(char *filename)
{
  FILE *fp = NULL;
  int c = 0;
  fp = fopen(filename, "r");
  if(NULL == fp)
    {
      return ERROR_OPEN_FILE;
    }
  while(EOF != (c = fgetc(fp)))
    {
      fputc(c, stdout);
    }
  fclose(fp);
  return S_SUCCESS;
}
/*
    AddContentToFile

    Describle:
      Add a string to file

    Arguments:
      file
        The dest file
      content
        The content

    Return value:
      No value
*/
CodeStatus
AddContentToFile(char *file, char *content)
{
  FILE *fp = fopen(file, "a+");
  if(NULL == fp)
    {
      return ERROR_CREATE_FILE;
    }
  fputs(content, fp);
  fclose(fp);
  return 0;
}
/*
    CombineFile

    Describle:
      Combine 2 files content

    Arguments:
      file_1
        The dest file
      file_2
        The source file

    Return value:
      No value
*/
CodeStatus
CombineFile(char *file_1,char *file_2)
{
  FILE *fp1 = fopen(file_1, "a+");
  FILE *fp2 = fopen(file_2, "r");
  char temp[1024] = {0};
  while(!feof(fp2))
    {
      fgets(temp, sizeof(temp), fp2);
      fprintf(fp1, "%s", temp);
    }
  fclose(fp1);
  fclose(fp2);
  return 0;
}
