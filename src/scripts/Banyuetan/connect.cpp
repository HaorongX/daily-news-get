#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include<iostream>

using namespace std;

int
main(int argc, char* argv[])
{
    string command = "python3 ./banyuetan.py ";
    for (int i = 1;i < argc;++ i)
    {
        command += argv[i];
        command += ' ';
    }
    cout<<command<<endl;
    system(command.c_str());
    return 0;
}
