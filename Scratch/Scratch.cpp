#include <iostream>
#include <array>

struct mystruct
{
    int myarray[3];
};

int main()
{
    int newlist[3] = { 10, 20, 30 };
    mystruct test;
    int mysize = sizeof(newlist) / sizeof(int);
    for (int i = 0; i < mysize; i++)
    {
        test.myarray[i] = newlist[i];
    }
}
