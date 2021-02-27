#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>

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
	bool contains(const commands& vec, const T& item)
	{
		return (std::find(vec.begin(), vec.end(), item) != vec.end());
	}
}

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

class argHandler
{
private:
	const vector<string> singlecmds{ "flagaudio", "setTC" };
	vector<string> all;
	commands params;

	void parseTC();
	void parsechannels();
	void parsecmds();
public:
	vector<string> tasks;
	array<int, 2> channelRange{};
	int numOfTracks;
	string fileURL;
	TimeCodeRecord TCR;

	argHandler(int& argc, char* argv[]);
	commands getparams() const { return this->params; }
};