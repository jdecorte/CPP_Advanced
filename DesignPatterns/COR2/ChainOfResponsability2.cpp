// ChainOfResponsability2.cpp : Defines the entry point for the console application.
//

#include "logger.h"

int main()
{
	ConsoleLogger console;
	FileLogger file;
	EmailLogger email;
	console.setNext(&file);
	file.setNext(&email);
	console.log("disk 80 % full",4);
	console.log("disk 90 % full",7);
	console.log("Out of disk space",11);

	return 0;
}

