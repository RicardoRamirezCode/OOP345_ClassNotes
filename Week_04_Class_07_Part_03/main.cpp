#include <iostream>
#include "Animal.h"
#include "util.h"

using namespace std;

int main()
{
	Animal* a = createAnimal();

	a->eat();		// eat() is not polymorphic; so we get function from Animal
	a->move();		// depends on user choice and how we instanciate the class
					// this information will not be known until run-time
					// main does not have to know what Animal is using (duck or tiger)
					// yet main calls the right function because move is polymorhpic


	//Part 02

	Animal* b = a->clone();		// want this b to be a copy of a
					// don't want b to store the same address as a
					// I want b to store the address of a new object that is the same as the address stored at a

					// can not call copy constructor as Animal doesn't know about Tiger, Duck, etc
					// if attempt to call copy constructor it can not handle the attribute of Tiger, Duck, etc
					// we don't know the actual type of a to do a correct duplication

			// answer is we need a method to do duplications

	cout << "\n\nBehaviour of Clone:" << endl;
	b->eat();
	b->move();
	// so main was able to make a copies without knowing the actual type
	// by exploiting polymorphism

	// note we can not enable polymorphism on constructors; can't make constructors virtual
	// because constructor gives the actual type of the object

	cout << endl << endl;

	// Part 03
	cout << "Comparing Animals: \n";
	Animal* c = createAnimal();

	// to see if the two objects have the same content, but all we know is Animal; I don't know any of the derived types
	// a == c compares the address which doesnt make sense so we have to dereference the Animal
	// hence *a == *c; which means we have to overload it and include it in Animal
	

	if (*a == *c)
	{
		cout << "Same Animal\n";
	}
	else
	{
		cout << "Different Animal\n";
	}

	delete a;
	delete b;
	delete c;
	// if the destructor is not virtual; when I do delete a I only get the destructor from Animal type being called
	// if I make the destructor virtual I get the destructor from the actual type not only from Animal
	// so if matric complains about virtual destructors this missing may be the cause
}