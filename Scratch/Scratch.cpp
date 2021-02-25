#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int global = 10;


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

void somefunc()
{
    print(global);
}

int main(int argc, char* argv[])
{
    string teststring = "12345";
    vector<string> testargs;
    for (int i = 0; i < argc; ++i)
    {
        testargs.emplace_back(argv[i]);
    }
    
    typedef map<string, string> command;
    
    command testcmd;
    string key = "cmd1";
    testcmd[key] = "param1";

    command newcmd;
    print(testcmd.empty());

}