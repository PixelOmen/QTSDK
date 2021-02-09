#include <iostream>
#include <string>
#include "general.h"
using namespace std;

int* parseargs(int& argc, char* argv[])
{
    if (argc != 3)
    {
        print("Not enough arguments");
        exit(1);
    }

    string channelstring = argv[1];
    string path = argv[2];

    string delim = ",";
    size_t delimsize = sizeof(delim) / sizeof(string);
    int* channelints = new int[2];

    size_t offset = channelstring.find(delim);
    if (offset == string::npos)
    {
        print("Incorrect argument formatting for channels.");
        exit(1);
    }

    size_t counter = 0;
    size_t start = 0;
    while (offset != string::npos)
    {
        channelints[counter] = stoi(channelstring.substr(start, offset - start));
        start = offset + delimsize;
        offset = channelstring.find(delim, start);
        ++counter;
        if (offset == string::npos)
        {
            channelints[counter] = stoi(channelstring.substr(start, channelstring.size()));
        }
    }
    
    return channelints;
}