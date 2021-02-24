#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

struct teststruct
{
    int test1 = 10;
    string test2 = "my test string";
};

int main(int argc, char* argv[])
{
    teststruct myteststruct;
    myteststruct.test1 = 20;
    print(myteststruct.test1);
}