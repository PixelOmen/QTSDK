#include <iostream>
#include <array>
#include <map>

typedef std::map<std::string, int> errorDict;
typedef int error;

errorDict initQT()
{
    errorDict returnDict{ {"first", 0}, {"second", 1} };
    return returnDict;
}

error pullFromDict(errorDict *dict, std::string *value, std::string *answer)
{
    if (dict->find(*value) == dict->end())
    {
        answer = nullptr;
        return 1;
    }
    else
    {
        *answer = (*dict)[*value];
        return 0;
    }
}


int main()
{
    errorDict returnvalues = initQT();

    std::string answer;
    error dicterr = pullFromDict(&returnvalues, (std::string*)"test", &answer);



}
