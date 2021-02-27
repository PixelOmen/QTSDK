#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <array>
using namespace std;

template<typename T>
void print(T toprint)
{
	std::cout << toprint << std::endl;
}

class testclass
{
public:
	int m_x;
	int m_y;

	testclass(int x, int y)
		: m_x(x), m_y(y)
	{
	}

	void printx();
	void printy();
};

void testclass::printx()
{
	print(this->m_x);
	this->printy();
}

void testclass::printy()
{
	print(this->m_y);
}


int main(int argc, char* argv[])
{
	testclass test{ 3 , 10 };
	testclass test2{ 5 , 20 };

	test.printx();
	test2.printx();
}