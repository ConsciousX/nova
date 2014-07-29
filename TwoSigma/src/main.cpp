#include <iostream>
#include <string>

#include "Animation.h"
#include "MissingLetters.h"

using namespace std;

//Get option
char getOpt(char **&argv)
{
    char *v, c;
    v = *argv;

    if (v == nullptr || *v++ != '-' || (c = *v++) == '\0')
    {
        return -1;
    }

    ++argv;

    return c;
}

//Get option argument
char* getOptArg(char **&argv)
{
    char *v;
    v = *argv;

    if (v != nullptr && *v != '-' && *v != '\0')
    {
        ++argv;
        return v;
    }
    else
    {
        return nullptr;
    }
}

//Get next argument
char* getArg(char **&argv)
{
    return *argv++;
}

//Usage function
void usage()
{
    cout<<"usage: %s [options] [string ...]\n";
    cout<<"options: "<<endl;
    cout<<"-a               This is a"<<endl
        <<"-b               This is b"<<endl
        <<"-c               This ic c"<<endl
        <<"-o <file>        This is o"<<endl;
}

void exitUsage()
{
    usage();
    exit(1);
}

int main(int argc, char **argv)
{
    //Parse arguments
    char **av = (argv + 1);
    char c;

    while ((c = getOpt(av)) > 0)
    {
        switch (c)
        {
            case 'a':
                break;
            case 'b':
                break;
            case 'c':
                break;
            case 'o':
                if (getOptArg(av) == nullptr)
                    exitUsage();
                break;
            default:
                exitUsage();
        }
    }

    //Last argument should be string
    char* str = getArg(av);
    if (!str)
        exitUsage();

    vector<string> result1 = animation.animate(3, str);
    for(auto item : result1)
    {
        cout<<item<<endl;
    }

    string result2 = missingLetters.getMissingLetters("fdf df fdfs kljlkjlj adada rionc");
    cout<<result2<<endl;

    string result3;
    result3.push_back(0x44);
    result3.push_back(0x45);
    result3.push_back(0x43);
    result3.push_back(0x4f);
    result3.push_back(0x44);
    result3.push_back(0x49);
    result3.push_back(0x47);
    result3.push_back(0x20);
    result3.push_back(0x4d);
    result3.push_back(0x45);
    result3.push_back(0x53);
    result3.push_back(0x45);
    result3.push_back(0x20);
    result3.push_back(0x46);
    result3.push_back(0x41);
    result3.push_back(0x49);
    result3.push_back(0x4c);
    result3.push_back(0x45);
    result3.push_back(0x44);

    cout<<result3<<endl;

    return 0;
}
