#ifndef Approver_H
#define Approver_H

#include <iostream>
#include "purchase.h"

using namespace std;

class Approver /*Handler*/ 
{
private:
	Approver* Next;
public:
	Approver() {Next = 0;}

	void setNext(Approver* n) 
	{
		Next=n;
	}
	Approver* getNext() 
	{
		return Next;
	}
	virtual void approve(Purchase* purchase)=0;
};

class Director /*ConcreteHandler*/: public Approver 
{
private: 
	static const int MAX_AMOUNT = 100'000;
public:
	void approve(Purchase* purchase) 
	{
		if (purchase->getAmount() <= MAX_AMOUNT) 
		{
			cout << "Director approves " << purchase->getDescription() << endl;
		} 
		else if (getNext() != 0) 
		{
			getNext()->approve(purchase);
		}
		else
			cout << "purchase rejected" << endl;
	}
};

class Board /*ConcreteHandler*/: public Approver 
{
private: 
	static const int MAX_AMOUNT = 1'500'000;
public:
	void approve(Purchase* purchase) 
	{
		if (purchase->getAmount() <= MAX_AMOUNT) 
		{
			cout << "Board approves " << purchase->getDescription() << endl;
		} 
		else if (getNext() != 0) 
		{
			getNext()->approve(purchase);
		}
		else
			cout << "Purchase rejected" << endl;
	}
};



#endif
