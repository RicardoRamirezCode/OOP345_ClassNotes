#include <iostream>
#include "Tiger.h"

using namespace std;

void Tiger::move()
{
	cout << "Tiger -> move()\n";
}

void Tiger::eat()
{
	cout << "Tiger -> eat()\n";
}

Animal* Tiger::clone()
{
	cout << "Cloning tigers.\n";
	return new Tiger(*this);		// calling copy constructor of Tiger
}

bool Tiger::operator==(const Animal& obj) const	
{
	bool result;
	// now need to make sure that Animal that was recieved is a Tiger
	// need to attempt cast then
	// if you have a hierarchy of classes and you want to convert on the heirarchy
	// then use dynamic_cast

	// dynamic_cast works with pointer not values
	const Tiger* theOther = dynamic_cast<const Tiger*>(&obj);
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
