#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Disney.h"

template<typename T>
void print(T toprint)
{
	std::cout << toprint << std::endl;
}

template<typename T>
bool contains(const std::vector<T>& vec, const T& item)
{
	return (std::find(vec.begin(), vec.end(), item) != vec.end());
}

typedef std::map<std::string, std::string> commands;

void testfunc(int& x) {
	x = 20;
};

int main(int argc, char* argv[])
{
	int test = Disney::Disney24ChConfig.at(8);
	// int test = headerfunc(10);
	print(test);
}