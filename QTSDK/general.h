#pragma once
#include <iostream>
#include <map>
#include <string>
#include <MacTypes.h>
#include <vector>
using namespace std;


template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
};

typedef map<string, OSErr> errorDict;
typedef map<string, string> commands;

int* parseargs(int& argc, char* argv[], int* totalTracksOut);



