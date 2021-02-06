#include <iostream>
#include "Duck.h"

using namespace std;

void Duck::move()
{
	cout << "Duck -> move()\n";
}

void Duck::eat()
{
	cout << "Duck -> eat()\n";
}

Animal* Duck::clone()
{
	cout << "Cloning ducks.\n";
	return new Duck(*this);		// calling copy constructor of Duck
}

bool Duck::operator==(const Animal& obj) const	
{
	bool result;
	// now need to make sure that Animal that was recieved is a Tiger
	// need to attempt cast then
	// if you have a hierarchy of classes and you want to convert on the heirarchy
	// then use dynamic_cast

	// dynamic_cast works with pointer not values
	const Duck* theOther = dynamic_cast<const Duck*>(&obj);
	// above was conversion, now need to check if it was successful or not
	if (theOther == nullptr)		// means conversion failed
	{
		result = false;
	}
	else
	{
		result = true;
	}

	return result;
}