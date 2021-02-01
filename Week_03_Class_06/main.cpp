#include <iostream>
#include <iomanip>
#include <typeinfo>

using namespace std;

class Foo
{
	// made as a friend not a member of Foo
	// as can't make it a member because if made a member all member functions will receive the current instance (as left op) which is an object of type Foo
	// so have to make it a helper or a friend; choice is the choice of the programmer
	friend ostream& operator << (ostream& ostr, const Foo& rightOp);
};

ostream& operator << (ostream& ostr, const Foo& rightOp)
{
	ostr << "Hello from Foo.";
	return ostr;
}


template<typename T>					// inside of <> are template parameters
void print(T val)
{
	cout << "\33[92m" << setw(10) << typeid(val).name() << "\33[0m" << setw(20)<< val << "\n";
}

template <typename T, int N>
void printA(T val)
{
	cout << "\33[92m" << setw(N) << typeid(val).name() << "\33[0m" << setw(20)<< val << "\n";
}




//void print(double val)
//{
//	cout << "[" << typeid(val).name() << "] [" << val << "]\n";
//}

int main()
{
	// Polymorphism
	// doing the same thing in a different way; execute the same action but do it differently

	/*
	- Ad-hoc polymorphism (fake polymorphism)
		-overloading
			-looks like polymorphism because we reuse the identifier and provide a new implementation for that identifier
			-fake because we don't do the same action but might do a different action
		-coercion
			- example: refers a function that accepts an interger as a parameter but client passes a double
				compiler will accept that parameter will do a conversion

	- True Polymorphism
		-inclusion (hierarchy of classes + virtual functions)
			-achieved with these virtual functions; in order to have virtual functions you need a hierarchy
		-Parametric [AKA Generic] Polymorphism (templates)
	*/

	// Run Type Time Information (RTTI)
	// use to provide some information about what types are used at runtime

	// need to include header typeinfo
	// Visual Studio may accept RTTI without header but standard says to include

	auto val = 32.1;		// type here is double
	cout << typeid(val).name() << endl;

	// typeid(val) returns a structure, a custom type; which has a bunch of members
	// can not use it to create variables of that; ie cant use it as a type when declaring a new variable
	// mostly used for debugging
	// should not use typeid to achieve some functionality for your program; ie use it to determine some logic for the program

	Foo aFoo;
	cout << typeid(aFoo).name() << endl;


	////////////////////////////////////////////////////////
	//Coloring

	// note that "\33" represents your escape key on your keyboard (without quotations)
	// use it to talk to console to change text
	cout << "\33[92m" << "I am a color!" << "\33[0m" << endl;


	////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////

	// Templates
	// advantages are if you need to fix a bug, or enhance the functionality you only have to do so in one spot vs every implementation of an overloaded function
	// issue with coercion arrises, it may convert and lose some data; ie a print(int val) but passing val as a double will have the compiler convert
	// a double to an int losing some information

	// 
	// with templates we can apply restrictions to T when we decide how we use the type T
	// for exmaple with print template above, type T must meet a condition which is that it works with insertion operator

	print(val);
	print(aFoo);

	// so as programers it's your responsibility to ensure operators are supported for the types you are passing

}