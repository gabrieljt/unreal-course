// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

int main()
{
	std::cout << "Hello there. Tell me your name." << std::endl;

	std::string str;

	std::cin >> str;

	std::cout << str << ", is it? Why don't you tell me your age now?" << std::endl;

	int age;

	std::cin >> age;

	str = age < 18 ? "... you shouldn't be here." : "So, ready to get high?";

	std::cout << str << std::endl;

	return 0;
}