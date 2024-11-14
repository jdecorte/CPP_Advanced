#ifndef Purchase_H
#define Purchase_H

#include <iostream>
#include <string>

using namespace std;

class Purchase
{
private:
	int amount;
	string description;
public:
	Purchase(int b, string oms) 
	{
		amount = b;
		description = oms;
	}
	int getAmount() {return amount;}
	string getDescription() {return description;}
};

#endif
