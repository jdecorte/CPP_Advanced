#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

using namespace std;

class Logger /*Handler*/ 
{
private:
	Logger* next;
protected:
	virtual void log_(string msg, int priority) = 0;
public:
	Logger() {next = 0;}
    virtual void log(string msg, int priority) final
	{
		log_(msg, priority);
		if (getNext() != 0)
		{
			getNext()->log(msg, priority);
		}
	}
	void setNext(Logger* n) 
	{
		next = n;
	}	
	Logger* getNext() {return next;}

};

class ConsoleLogger /* ConcreteHandler */ :public Logger 
{
public:
	void log_(string msg, int priority) override
	{
		cout << msg << " to console" << endl;
	}
};

class FileLogger /* ConcreteHandler */ :public Logger 
{
private:
	static const int min_priority = 5;
public:
	void log_(string msg, int priority) override
	{
		if (priority >= min_priority)
		{
			cout << msg << " to file" << endl;
		}
	}
};

class EmailLogger /* ConcreteHandler */ :public Logger 
{
private:
	static const int min_priority = 10;
public:
	void log_(string msg, int priority) override
	{
		if (priority >= min_priority)
		{
			cout << msg << " to email" << endl;
		}
	}
};


#endif
