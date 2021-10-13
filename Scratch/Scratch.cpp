#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <array>
#include "general.h"
using namespace std;

template<typename T>
void print(T toprint)
{
	std::cout << toprint << std::endl;
}


typedef map<string, string> commands;

int main(int argc, char* argv[])
{
	print(1 % 2);
}