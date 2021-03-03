#include <iostream>

using namespace std;

struct Foo
{
	virtual void display() const = 0;
};

struct Bar : public Foo
{
	void display() const {cout << "Hello.\n"; }
};

int main()
{
	////////////////////////////////
	// Array of Pointers Recap
	//int* arr;
	// arr[0] - > type int

	//int* arr[5];	// statically allocated array of pointers ; has five elements and each element is a pointer

	int val = 1;

	int** arr;		// dynamically alloated array of pointers
	arr = new int* [5]; // arr is now an array of pointers

	arr[0] = &val;			// both arr[9] and &val are of type int*

	// main reason for using array of pointers is if we wanted to use something abstract instead of int
	// we have created a pure virtual function, Foo; thus we can not have instances of Foo
	
	Foo* arrF[5];
	arrF[0] = new Bar;


	///////////////////////////////
	// Lambda expressions
	// method to create annoymous functions in c++

	[](){};		// this is techincally a lambda expression, that receives nothing and does nothing
				// () for parameters; {} for implementation; [] for capture list/ context; context is all local variables

	int data = 9;
	auto lambda = [data] (int a) {cout << "Value: [" << a << "][" << data << "]\n"; };

	lambda(67);
	data++;		// this would have no effect on lambda as it captured whatever was the value at the time 
	lambda(3);

	// if you want to update inside of lambda or outside of lambda you need to capture by reference

}