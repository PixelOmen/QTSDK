#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>
using namespace std;

namespace stringtools
{
	int test = 8;
	//void split(const string& instring, const string& delim)
	//{
	//	vector<string> returnvector{};
	//	int counter = 0;
	//	int start = 0;
	//	int offset = instring.find(delim);

	//	if (offset == string::npos)
	//		return {};

	//	while (offset != string::npos)
	//	{
	//		returnvector.emplace_back(instring.substr(start, offset - start));
	//		start = offset + 1;
	//		offset = instring.find(delim, start);
	//		++counter;
	//		if (offset == string::npos)
	//			returnvector.emplace_back(instring.substr(start, instring.size()));
	//	}

	//	return returnvector;
	//}
}

namespace another
{
	int testint = 10;
}