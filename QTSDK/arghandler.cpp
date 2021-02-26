#include <iostream>
#include <string>
#include "general.h"
#include "arghandler.h"
using namespace std;

namespace arghandler
{
    const vector<string> singles{ "flagaudio", "setTC" };
}

void parsecmds(vector<string>& args, commands* argcmdsOut, vector<string>* tasksOut)
{
    string cmd;
    int counter = 0;
    for (auto i : args)
    {
        if (i[0] == '-')
        {
            cmd = i.substr(1, (i.size() - 1));

            if (vectortools::contains(cmd, *(const_cast<vector<string>*>(&arghandler::singles))))
            {
                (*tasksOut).emplace_back(cmd);
            }
            else if (counter + 1 < args.size())
            {
                if (args[counter + 1][0] != '-')
                {
                    (*argcmdsOut)[cmd] = args[counter + 1];
                }
                else
                {
                    cout << "Empty command parameter for " << i << endl;
                    exit(1);
                }
            }
            else
            {
                cout << "Empty command parameter for " << i << endl;
                exit(1);
            }
        }
        ++counter;
    }
}

static void parsechannels(commands& argcmds, int& totalTracksOut, array<int, 2>& channelsOut)
{
	string channelstring = argcmds["channels"];
	string delim = ",";

	size_t offset = channelstring.find(delim);
	if (offset == string::npos)
	{
		print("Incorrect argument formatting for channels");
		exit(1);
	}

	size_t counter = 0;
	size_t start = 0;
	int found = 1;
	while (offset != string::npos)
	{
		if (found > 2)
		{
			print("Incorrect argument formatting for channels");
			exit(1);
		}
		channelsOut.at(counter) = stoi(channelstring.substr(start, offset - start));
		start = offset + 1;
		offset = channelstring.find(delim, start);
		++counter;
		if (offset == string::npos)
		{
            channelsOut.at(counter) = stoi(channelstring.substr(start, channelstring.size()));
		}
		++found;
	}

	if (channelsOut.at(0) < 1 || channelsOut.at(1) < 1 || channelsOut.at(1) < channelsOut[0])
	{
		print("Incorrect input channels. Input channels cannot be less than 1 and the second channel must be larger than the first");
		exit(1);
	}

	totalTracksOut = (channelsOut.at(1) - channelsOut.at(0)) + 1;

	if (totalTracksOut != 2 && totalTracksOut != 6 && totalTracksOut != 8)
	{
		print("Total number of tracks is not 2, 6, or 8");
		exit(1);
	}
}

commands parseargs(int& argc, char* argv[], int* totalTracksOut, array<int,2>* channelsOut, char** pathOut, vector<string>* tasksOut)
{
    if (argc < 3)
    {
        print("Not enough arguments");
        exit(1);
    }

    vector<string> args;
    for (int i = 0; i < argc; ++i)
    {
        args.emplace_back(argv[i]);
    }

    commands argcmds;
    parsecmds(args, &argcmds, tasksOut);

    if (argcmds.find("path") != argcmds.end())
    {
        *pathOut = const_cast<char*> ((argcmds["path"]).c_str());
    }
    else
    {
        print("No input path specified");
        exit(1);
    }

    if (argcmds.find("channels") != argcmds.end())
    {
        parsechannels(argcmds, *totalTracksOut, *channelsOut);
    }

    return argcmds;
}