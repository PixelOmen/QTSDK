#include <iostream>
#include <array>
#include <map>

typedef std::map<std::string, int> errorDict;
typedef int error;

template<typename T>
void print(T toprint)
{
    std::cout << toprint << std::endl;
}

errorDict initQT()
{
    errorDict returnDict{ {"first", 20}, {"second", 15} };
    return returnDict;
}

int pullFromDict(errorDict& dict, std::string& value)
{
    if (dict.find(value) == dict.end())
    {
        return -1;
    }
    else
    {
        return (dict)[value];
    }
}


int main()
{
    int* myints = new int[5];

    for (int i = 0; i < 5; i++)
        myints[i] = i+10;

    for (int i = 0; i < 5; i++)
    {
        print(myints[i]);
    }

}
