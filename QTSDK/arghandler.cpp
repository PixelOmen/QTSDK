#include "general.h"
using namespace std;

void argHandler::parseTC()
{

}

void argHandler::parsechannels()
{
	string channelstring = this->params["channels"];
	string delim = ",";

	size_t counter = 0;
	size_t start = 0;
	int found = 1;
	size_t offset = channelstring.find(delim);
	if (offset == string::npos)
	{
		print("Incorrect argument formatting for channels");
		exit(1);
	}
	while (offset != string::npos)
	{
		if (found > 2)
		{
			print("Incorrect argument formatting for channels");
			exit(1);
		}
		this->channelRange.at(counter) = stoi(channelstring.substr(start, offset - start));
		start = offset + 1;
		offset = channelstring.find(delim, start);
		++counter;
		if (offset == string::npos)
		{
            this->channelRange.at(counter) = stoi(channelstring.substr(start, channelstring.size()));
		}
		++found;
	}

	if (this->channelRange.at(0) < 1 || this->channelRange.at(1) < 1 || this->channelRange.at(1) < this->channelRange.at(0))
	{
		print("Incorrect input channels. Input channels cannot be less than 1 and the second channel must be larger than the first");
		exit(1);
	}

	this->numOfTracks = (this->channelRange.at(1) - this->channelRange.at(0)) + 1;

	if (this->numOfTracks != 2 && this->numOfTracks != 6 && this->numOfTracks != 8)
	{
		print("Total number of tracks is not 2, 6, or 8");
		exit(1);
	}
}

void argHandler::parsecmds()
{
    string cmd;
    int counter = 0;
    for (auto i : this->all)
    {
        if (i[0] == '-')
        {
            cmd = i.substr(1, (i.size() - 1));

            if (vectortools::contains(this->singlecmds, cmd))
                this->tasks.emplace_back(cmd);
            else if (counter + 1 < this->all.size())
            {
                if (this->all[counter + 1][0] != '-')
                    this->params[cmd] = this->all[counter + 1];
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

argHandler::argHandler(int& argc, char* argv[])
{
    if (argc < 3)
    {
        print("Not enough arguments");
        exit(1);
    }

    for (int i = 0; i < argc; ++i)
    {
        this->all.emplace_back(argv[i]);
    }

    this->parsecmds();

    if (vectortools::contains(this->params, (string)"path"))
        this->fileURL = this->params["path"];
    else
    {
        print("No input path specified");
        exit(1);
    }

    if (vectortools::contains(this->tasks, (string)"flagaudio"))
    {
        if (vectortools::contains(this->params, (string)"channels"))
            this->parsechannels();
        else
        {
			print("No channel range specified");
			exit(1);
		}
    }

    if (vectortools::contains(this->tasks, (string)"setTC"))
    {
        if (vectortools::contains(this->params, (string)"tc"))
            this->parseTC();
        else
        {
            print("No TC specified");
            exit(1);
        }
    }
}