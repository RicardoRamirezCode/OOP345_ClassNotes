#ifndef ANIMAL_H
#define ANIMAL_H

class Animal
{
public:

	virtual void move() = 0;		// since each derived class of animal will have a different way of moving

	void eat();

	// when you have a hierarchy of classes
	// you need to add in base class virtual destructor
	// because in main we have pointers to dynamically allocated Animals (a, b and c in main)
	// want to avoid memory leaks
	virtual ~Animal();

	// Part 02
	virtual Animal* clone() = 0;		// return by either reference or address
										// this clone function will be subject to polymorphism; will get the function from the actual type
										// when we call it

	// Part 03
	virtual bool operator==(const Animal& obj) const = 0;
	// can't look at specific members of derived classes as Animal doesn't know about them
	// so can only leave a prototype and let the derived classes handle the implementation
	// to not allow shadowing need to make it pure virtual




};

#endif // !ANIMAL_H


