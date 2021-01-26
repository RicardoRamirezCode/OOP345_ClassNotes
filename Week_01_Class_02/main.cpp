#include <iostream>

// have to declare this identifier, sayHello, before using it
// can not include ccp files, and that is where this function is defined
// all I need is the prototype
// It will still work AS LONG AS THE LINKER CAN FIND THE DEFINITION!! Linker is responsible to find the definition/implementation of the function
// so only the declaration in this cpp file is needed

//void sayHello();

// better practice is to include this declaration in a header and include the header
// as if you need to use this sayHello() function in multiple ccp files it opens the chance you mistype it, have the wrong paramaters, etc
// as well as needing to write the declarations in each cpp file

#include "utilities.h"
// here it also has a definition for g_value of 10 from this include

using namespace std;
using namespace foo;



// Lesson Part Three
constexpr int getValue(int seed) // for SOME parameters, the result is known at compile time
{
	return seed * 10;
}



int main(int argc, char* argv[])
{
	
	sayHello(); // here it displays with g_value 10; g_value was defined from the include "utilities.h"
	g_value = 20;
	// here g_value exists in another module, not known here in cpp file
	sayHello(); // here it displays with g_value 20

	

	// Lesson Part Two
	const int size = 9; 
	short arr[size];
	// constant has value from moment of birth and can not be changed
	
	// constant that doesn't have its value known at compile time
	// constant member of structure Foo for example is constant but not known at compile time
	
	int val;
	cin >> val;
	Foo theFoo{ val };
	cout << theFoo.m_val << endl;

	// so constants don't require to be known at compile time
	// only that once created it gets a value and can not be changed
	// also must initialize when it receive memory

	// C++ comes with a method, to have a constant but you guarantee the value is known at compile time
	constexpr int size_example = 9;
	short arr_b[size];


	// to recap
	const int exampleVal_a = 9;		// the value can not be changed
	constexpr int exampleVal_b = 9;	// the value can not be changed AND must be known at compile time



	/*
	int val;
	cin >> val;

	const int constVal = val;
	short arr[constVal];

	Does not work as you do not know value at compile time
	
	*/


	// Lesson Part Three
	// can make functions constexpr
	// however it does not say the value, return will always be known at compile time
	short arrExample[getValue(3)];

	 // order of steps
	// first OS will validate it is a (real) executable
	// then it will look inside and try to allocate memory
	// will allocate into memory zones

	// Mem Zones
	// data					-one will be for global variables
	// code (read only)		where the code, ie functions will go; will not allow change to functions; if there is an attempt to change anything in this zone
	//										OS will stop the application; crash the application
	// heap (dynamic memory)- anytime you create something with new, or deallocate it is done here
	//						- can be very big; can be resized during runtime
	// stack (static memory) - all variables allocated by the compiler
	//						 - very small
	//						 - like val, arr from above

	// so really want things such as very large arrays in the heap not in the stack [so dynamically allocated not created at compile time]
	// so should use stack for local, small variables
	// heap for big objects

	// trying to use stack for something very large
	// results in an error
	// stack overflow

	// for example
	// not good:
	// Picture pic;
	// is good:
	// Picture* pic = new Picture;
	// where your picture is very large



	/*
	Types:
	-fundamental: int, float, char
	are known by the hardware
	makes them very efficient to use; opeations on them are very fast

	-built-in types: [], * , &  (arrays, pointers and references)
	provided by the language
	still efficient

	-custom types: classes/ structures/ unions


	*/


	static_assert(getValue(3) == 30, "GetValue return wrong result for param 3.");
	// static_assert allows me to check some conditions that can not be checked by the language automatically
	// if i change above to 20 it won't even compile and give a message
	// message is the one I specified
	// so better to write a message so you know which static_assert failed

}