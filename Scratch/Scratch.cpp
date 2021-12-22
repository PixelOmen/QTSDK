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

template<typename T>
bool contains(const vector<T>& vec, const T& item)
{
	return (std::find(vec.begin(), vec.end(), item) != vec.end());
}

typedef map<string, string> commands;

int main(int argc, char* argv[])
{
	vector<string> test{ "tklds", "akldjf" };
	vector<float> SUPPORTED_FPS{ 24, 23.98, 23.976, 25, 30, 29.97, 60, 59.94 };
	//bool result = contains(SUPPORTED_FPS, stof("blah"));
	if (stof("23.9845") == SUPPORTED_FPS[1] || SUPPORTED_FPS[2]) {
		print("Yup");
	}
	else
	{
		print("nope");
	}
	//try
	//{
	//	float worked = stof("23.98");
	//	print(worked);
	//}
	//catch (const exception& e)
	//{
	//	print(e.what());
	//}

}