#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "TradeDB.h"
#include "TradeCollector.h"

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
    vector<TradeDB> tradeDB;
    int totalNumOfDB = 0, count = 0;
    string line;
    while (getline(cin, line))
    {
        if (!totalNumOfDB) //This line id for number of trader systems
        {
            totalNumOfDB = stoi(line);
            if (totalNumOfDB <= 0)
            {
                cout<<"Invalid number of trading systems"<<endl;
                exit(0);
            }
        }
        else
        {
            stringstream ss(line);
            string dbId;
            getline(ss, dbId, ' ');
            tradeDB.emplace_back(dbId);
            while (!ss.eof())
            {
                string tradeId;
                getline(ss, tradeId, ' ');
                TradeRecord tradeRecord(tradeId);
                tradeDB[count].addTrade(tradeRecord);
            }

            if (++count == totalNumOfDB)
                break;
        }
    }

    cout<<"***Result***"<<endl;

    TradeCollector tradeCollector;

    for_each(begin(tradeDB), end(tradeDB), [&tradeCollector](const TradeDB& item)
        {
            tradeCollector.collectTrade(item);
        });

    tradeCollector.printAll(cout);

    return 0;
}
