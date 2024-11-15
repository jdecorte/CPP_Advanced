#include <iostream>
#include "garage.h"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        Garage g; // default state is Closed
        g.OpenClose();
        g.SetState(Opening::get());
        g.Lock();
        g.OpenClose();
        g.Lock();
        g.Lock();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Unknown exception" << endl;
    }
    
    return 0;
}
