#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <stdio.h>

#include <QuickTimeComponents.h>
#include <MacTypes.h>
using namespace std;

typedef map<string, OSErr> errorDict;
typedef map<string, string> commands;

namespace vectortools
{
	template<typename T>
	bool contains(const vector<T>& vec, const T& item)
	{
		return (std::find(vec.begin(), vec.end(), item) != vec.end());
	}

	template<typename T>
	bool contains(const commands& inmap, const T& item)
	{
		return (inmap.find(item) != inmap.end());
	}
}

namespace stringtools
{
	vector<string> split(const string& instring, const string& delim);
}

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

class argHandler
{
private:
	const vector<string> singlecmds{ "flagaudio", "setTC", "me6ch"};
	vector<string> all;
	commands params;

	void parsePath();
	void parseTC();
	void parsechannels();
	void parsecmds();
	void parseFPS();
public:
	vector<string> tasks;
	array<int, 2> channelRange{};
	int numOfTracks;
	string fileURL;
	TimeCodeRecord TCR;
	float fps;

	argHandler(int& argc, char* argv[]);
	commands getparams() const { return this->params; }
};