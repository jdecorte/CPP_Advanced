// ChainOfResponsability.cpp : Defines the entry point for the console application.
//

#include "purchase.h"
#include "approver.h"


int main()
{
	// Create the chain of responsibility
	Director dir;
	Board board;
	dir.setNext(&board);

	cout << "Machine" << endl;
	Purchase a(100'000,"Machine");
	dir.approve(&a);

	cout << "Building" << endl;
	Purchase b(1'000'000,"Building");
	dir.approve(&b);

	cout << "Tropical Island" << endl;
	Purchase c(10'000'000,"Tropical Island");
	dir.approve(&c);

	return 0;
}

