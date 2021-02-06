#include <iostream>
#include <map>
#include <regex>

using namespace std;

typedef std::map<std::string, int> errorDict;
typedef int error;

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

int main(int argc, char* argv[])
{
    
    //print(argc);

    //if (argc < 3)
    //{
    //    print("Not enough arguments");
    //    exit(1);
    //}

    //std::string channels = argv[1];
    //std::string path = argv[2];

    string mystring = "test,string";

    size_t test = mystring.find_first_not_of('*', 0);

    print((test == string::npos));

}
