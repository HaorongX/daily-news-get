#ifndef PUBLIC_FILE
#define PUBLIC_FILE
#include "public_type.h"
#define CreateEmptyFile(filename) AddContentToFile(filename, "")
CodeStatus CombineFile(char *file_1,char *file_2);
CodeStatus AddContentToFile(char *file, char *content);
CodeStatus PrintFileContent(char *filename);
CodeStatus RemoveDirectory(char *path);
CodeStatus RemoveFile(char *filename);
CodeStatus CopyDirectory(char *source, char *dest);
CodeStatus AccessDirectory(char *path, CodeStatus (*function)(FileInfo info, void *arguments), void *arguments, int flag);
#endif
