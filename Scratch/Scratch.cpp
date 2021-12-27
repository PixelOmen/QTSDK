#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <array>
#include <cmath>
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

int main(int argc, char* argv[])
{
	double fps = 23;
	fps++;
	print(fps);
}