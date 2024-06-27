#include <iostream>
#include <string>
using namespace std;

void f(string s)
{
    cout << s << endl;
}

void foo(int x)
{
    int buf[10];
    if (x == 1000)
        buf[x] = 0; // <- ERROR
}

int main() 
{
    f("Hello, World!");
    foo(1000); // <- ERROR
    return 0;
}