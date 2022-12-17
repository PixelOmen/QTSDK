#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <array>
#include <cmath>

#include "Disney.h"

using namespace std;

template<typename T>
void print(T toprint)
{
	std::cout << toprint << std::endl;
}

template<typename T>
bool contains(const vector<T>& vec, const T& item)
{
	return (std::find(vec.begin(), vec.end(), item) != vec.end());
}

typedef map<string, string> commands;

void testfunc(int& x) {
	x = 20;
};

int main(int argc, char* argv[])
{
	int test = Disney::Disney24ChConfig.at(1);
	print(test);
}