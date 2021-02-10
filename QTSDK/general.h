#pragma once
#include <iostream>
using namespace std;

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

int* parseargs(int& argc, char* argv[], int& totaltracks);



