#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

int main(int argc, char* argv[])
{

    string mystring = "my string,seperated by commas";
    string delim = ",";
    size_t delimsize = sizeof(delim) / sizeof(string);
    vector<string> results;
    size_t offset = mystring.find(delim);
    size_t counter = 0;
    size_t start = 0;
    while (offset != string::npos)
    {
        results.push_back(mystring.substr(start, offset - start));
        start = offset + delimsize;
        offset = mystring.find(delim, start);
        ++counter;
        if (offset == string::npos)
        {
            results.push_back(mystring.substr(start, mystring.size()));
        }
    }
    print(results[0]);
    print(results[1]);
}