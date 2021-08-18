#include "public.h"
int IsRemove(char *package_name)
{
  FILE *fp = NULL;
  char filename[2048] = {0};
  sprintf(filename, "./%s/%s/%s", DNG_EXTENSION_INSTALL_DIRECTORY, package_name, DNG_EXTENSION_CLOSE_FILE);
  fp = fopen(filename, "r");
  if(fp)
    {
      fclose(fp);
      return 1;
    }
  return 0;
}
