#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
void AddContentToFile(char *file,char *content)
{
  FILE *fp = fopen(file, "a+");
  fputs(content, fp);
  fclose(fp);
}
void CombineFile(char *file_1,char *file_2)
{
  FILE *fp1 = fopen(file_1, "a+");
  FILE *fp2 = fopen(file_2, "r");
  char temp[1024] = {0};
  while(!feof(fp2))
    {
      fread(temp, sizeof(temp),1,fp2);
      fwrite(temp, sizeof(temp), 1, fp1);
    }
  fclose(fp1);
  fclose(fp2);
}
char* GetFileSuffixName(char *path)
{
  int length = strlen(path);
  int suffix_length = 0;
  int i = 0;
  static char dest[128] = {0};
  memset(dest, 0, sizeof(dest));
  while(*(path + length - suffix_length) != '.')
    {
      suffix_length++;
    }
  strcpy(dest, (path + length - suffix_length + 1));
  return dest;
}
char* GetNewsTitle(char *file)
{
  char *suffix = NULL;
  char *c_directory = 0;
  static char result[512] = {0};
  memset(result, 0, sizeof(result));
  strcpy(result, file);
  suffix = strstr(result, ".txt");
  memset(suffix, 0, strlen(suffix));
  c_directory = strrchr(result, '\\');
  strncpy(result, c_directory + 1, strlen(c_directory + 1));
  return result;
}
void CollectPackage(char *name)
{
  DIR *directory = NULL;
  char parent_directory[1024] = {0};
  struct dirent *file = NULL;
  sprintf(parent_directory, "./installed/%s/result", name);
  directory = opendir(parent_directory);
  if(!directory)
  {
    return ;
  }
  while(1)
    {
      file = readdir(directory);
      if(NULL == file)
        {
          break;
        }
      if(DT_REG == file -> d_type)
        {
          if(!strcmp("txt", GetFileSuffixName(file -> d_name)))
            {
              char content[1024] = {0};
              char filename[1024] = {0};
              sprintf(content, "<b> %s </b><br>\n", GetNewsTitle(file -> d_name));
              AddContentToFile("Complete.html", content);
              sprintf(filename, "./installed/%s/result/%s", name,file -> d_name);
              CombineFile("Complete.html", filename);
              AddContentToFile("Complete.html", "<br>");
            }
        }
    }
  closedir(directory);
}
void CollectAllPackage()
{
  DIR *directory = NULL;
  char *parent_directory = "./installed/";
  struct dirent *file = NULL;
  directory = opendir(parent_directory);
  if(!directory)
  {
    return ;
  }
  while(1)
    {
      file = readdir(directory);
      if(NULL == file)
        {
          break;
        }
      if(DT_DIR == file -> d_type)
        {
          char content[1024];
          sprintf(content,"<br><h1>%s</h1><br>",file -> d_name);
          AddContentToFile("Complete.html", content);
          CollectPackage(file -> d_name);
        }
    }
  closedir(directory);
}
int main()
{
  CollectAllPackage();
  return 0;

}
