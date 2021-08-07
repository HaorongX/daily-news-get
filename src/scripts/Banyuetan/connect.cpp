#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

int
main(int argc, char* argv[])
{
    string command = "python3 ";
    command += argv[1];
    command += "/banyuetan.py ";
    for (int i = 2;i < argc;++ i)
    {
        command += argv[i];
        command += ' ';
    }
    system(command.c_str());
    return 0;
}
