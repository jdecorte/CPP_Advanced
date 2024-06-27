#include <iostream>  
#include <format>

using namespace std;


int main()
{
   string student{"Paul"};
   int grade{87};

   cout << format("{}'s grade is {}\n", student, grade);
}
