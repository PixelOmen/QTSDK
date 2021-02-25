#include <iostream>
#include <string>
#include "general.h"
#include "arghandler.h"
using namespace std;

static void parsecmds(vector<string>& args, commands* argcmdsOut)
{
    string cmd;
    int counter = 0;
    for (auto i : args)
    {
        if (i[0] == '-')
        {
            cmd = i.substr(1, (i.size() - 1));

            if (counter + 1 < args.size())
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

static void parseChannels(commands& argcmds, int* channelsOut, int* totalTracksOut)
{
	string channelstring = argcmds["channels"];
	string delim = ",";

	size_t offset = channelstring.find(delim);
	if (offset == string::npos)
	{
		print("Incorrect argument formatting for channels.");
		exit(1);
	}

	size_t counter = 0;
	size_t start = 0;
	int found = 1;
	while (offset != string::npos)
	{
		if (found > 2)
		{
			print("Incorrect argument formatting for channels.");
			exit(1);
		}
		channelsOut[counter] = stoi(channelstring.substr(start, offset - start));
		start = offset + 1;
		offset = channelstring.find(delim, start);
		++counter;
		if (offset == string::npos)
		{
			channelsOut[counter] = stoi(channelstring.substr(start, channelstring.size()));
		}
		++found;
	}

	if (channelsOut[0] < 1 || channelsOut[1] < 1 || channelsOut[1] < channelsOut[0])
	{
		print("Incorrect input channels. Input channels cannot be less than 1 and the second channel must be larger than the first.");
		exit(1);
	}

	*totalTracksOut = (channelsOut[1] - channelsOut[0]) + 1;

	if (*totalTracksOut != 2 && *totalTracksOut != 6 && *totalTracksOut != 8)
	{
		print("Total number of tracks is not 2, 6, or 8.");
		exit(1);
	}
}

void parseargs(int& argc, char* argv[], int* totalTracksOut, int* channelsOut)
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
    parsecmds(args, &argcmds);

    if (argcmds.find("channels") != argcmds.end())
    {
        parseChannels(argcmds, totalTracksOut, channelsOut);
    }

}