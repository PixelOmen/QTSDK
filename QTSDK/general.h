#pragma once
#include <iostream>
#include <map>
#include <string>
#include <MacTypes.h>
#include <vector>
#include <array>
using namespace std;

namespace vectortools
{
	template<typename T>
	bool contains(T& item, vector<T>& vec)
	{
		return (std::find(vec.begin(), vec.end(), item) != vec.end());
	}
}

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
};

typedef map<string, OSErr> errorDict;
typedef map<string, string> commands;

commands parseargs(int& argc, char* argv[], int* totalTracksOut, array<int, 2>* channelsOut, char** pathOut, vector<string>* tasksOut);



