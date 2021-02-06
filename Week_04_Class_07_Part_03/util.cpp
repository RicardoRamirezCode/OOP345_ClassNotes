#include <iostream>
#include "util.h"
#include "Duck.h"
#include "Tiger.h"
#include "MechanicalTiger.h"

using namespace std;

Animal* createAnimal()
{
	Animal* result = nullptr;
	char choice = '\0';
	cout << "What animal (t/d)? ";
	cin >> choice;
	if (choice == 'd')
	{
		result = new Duck;
	}
	else
	{
		result = new Tiger;
	}

	return result;
}