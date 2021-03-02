#include "general.h"
using namespace std;

void argHandler::parsePath()
{
	FILE* file;
	errno_t openerr;
	openerr = fopen_s(&file, this->params["path"].c_str(), "r");
	if (file != NULL)
	{
		fclose(file);
		this->fileURL = this->params["path"];
		print("file exists");
	}
	else
	{
		cout << "Provided path does not appear to be a valid file: " << this->params["path"] << "\n";
		exit(1);
	}
}

void argHandler::parseTC()
{
	vector<string> tcstr = stringtools::split(this->params["tc"], ":");

	if (tcstr.size() != 4)
	{
		print("Improperly formatted '-tc' parameter");
		exit(1);
	}

	this->TCR.t.hours = (UInt8)stoi(tcstr[0]);
	this->TCR.t.minutes = (UInt8)stoi(tcstr[1]);
	this->TCR.t.seconds = (UInt8)stoi(tcstr[2]);
	this->TCR.t.frames = (UInt8)stoi(tcstr[3]);
}

void argHandler::parsechannels()
{
	vector<string> channelstr = stringtools::split(this->params["channels"], ",");

	if (channelstr.size() != 2)
	{
		print("Incorrect number of channels supplied in '-channel' parameter");
		exit(1);
	}

	this->channelRange.at(0) = stoi(channelstr[0]);
	this->channelRange.at(1) = stoi(channelstr[1]);

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
	unsigned int counter = 0;
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
		this->parsePath();
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