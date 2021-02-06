#include <iostream>
#include <map>
#include <regex>
#include <cstring>

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

    string mystring = "test11,test22222,test33";
    string delim = ",";
    string parts[3];

    size_t delimsize = sizeof(delim) / sizeof(string);
    size_t counter = 0;
    size_t start = 0;
    size_t offset = mystring.find(delim);
    while (offset != string::npos)
    {
        parts[counter] = mystring.substr(start, offset - start);
        start = offset + delimsize;
        offset = mystring.find(delim, start);
        ++counter;
        if (offset == string::npos)
            parts[counter] = mystring.substr(start, mystring.size());
    }

}
