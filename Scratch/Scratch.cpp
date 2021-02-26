#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <array>
using namespace std;

template<typename T>
bool contains(T item, vector<T> vec)
{
    return (std::find(vec.begin(), vec.end(), item) != vec.end());
}

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

int main(int argc, char* argv[])
{
    vector<string> test{ "teststring" };
    print(contains((string)"teststring2", test));
}