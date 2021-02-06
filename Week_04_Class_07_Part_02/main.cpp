#include <iostream>
#include "Animal.h"
#include "Tiger.h"
#include "Duck.h"

using namespace std;

int main()
{
	// abstract type
	// not a complete class; it is a type that is missing some implementation for a function
	// either by having a pure virtual function or by inheriting one and not having an implementation for it
	// can not be instantiated; only complete types can be

	// complete class
	// has everything it needs; can be instantiated while abstract can not as it's missing some implementation(s)


	Animal* a = new Tiger;
	// Animal - declared type
	// Tiger - actual type

	a->eat();
	// eat() is not subject to polymorphism; so we get eat from the declared type (Animal)
	a->move();
	// Animal has no implementation of move()
	// it will still work as move is subject to polymorphism; so on the hierarchy of classes we are going to get move()
	// from the actual type
	// the declared type of a is Animal, but the actual type of a is Tiger (what constructor has been used to instantiate it)

	// so we select the function from actual type or declared type depending on whether we have polymorphism enabled on that function

	// if you don't want to do dynamic memory:
	Tiger t;	// create an instance
	Animal* b = &t;

	b->eat();
	b->move();

	// rely on polymorphim to get the right function
	// just hold a pointer to the base class
	// whatever is the actual type you know from polymorphim you get from that actual type


	////////////////////////////////////////
	// implemenation of duck

	// not aware of derived type; just have a pointer to the base type

	Animal* d = new Duck;

	d->eat();
	d->move();
}