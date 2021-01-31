#include <iostream>
#include <utility>

using namespace std;


void print(int& val)
{
	cout << "This is an lValue reference\n";
}

void print(int&& val)
{
	cout << "This is an rValue reference\n";
}


/////////////Part 02
int printB(int& val)
{
	cout << "lValue reference\n";
	return val;
}

int printB(int&& val)
{
	cout << "rValue reference\n";
	return val;
}

/////////////Part 03
int& printC(int& val)				// this now receives by reference and returns by reference
{
	cout << "lValue reference\n";
	return val;						// returns by reference, so it makes no copies and returns by lValue
}

int printC(int&& val)
{
	cout << "rValue reference\n";
	return val;						// returns by value, so it will make a copy of parameter and pass it back to the client
									// since it is a copy it is temporary and returns an rValue reference
}



int main()
{
	// references, are alias; a new name for an existing 'thing'

	int a = 10;
	// below is an l-value reference
	int& ra = a;		// ra is a reference of a now.
						// references must be initialized; can't make a reference without initializing it
						// ie. they must exist in memory; you can set ra to a but not to '10' as it doesnt exist in memory

	// now above both a and ra refer to the same memory location, the same variable


	// r-value references
	a = 20;		// can be thought of as something is l-value if it can appear on the left side of the assignment operator
				// and r-values can only appear on the right side of the assignment operator

	// C++11 then asked can we create references to things that can not appear on the left side

	// below is an r-value reference
	int&& r = 10;	// r-value references; or things that only appear on the right side of an assignment operator
					// so behind the scenes the compiler will allocate some memory for 10, store the value 10 in there
					// and r will become a reference to this location in memory

	// this allows us to overload functions based on what type of references we pass


	print(10);		// calls rValue print
					// if we don't have the second print that has rValue passed to it we cannot call this print function
					// previously, we references we could define functions taking references but we could not pass
					// a value, we could only pass a reference; unless we made a reference to that value and passed that

	print(a);		// calls lValue print

	// can force a call rValue print even if we pass an lValue
	// need to transform a into an rValue reference

	print(std::move(a));	// std::move() [uses include utility]
							// std::move() isn't moving anything, it just creating an rValue reference and returns it

	/////////////Part 02
	cout << "Part 2" << endl;
	printB(printB(a));		// result of printB(a) will be passed as parameter to second call to printB
							// printB(a) calls first print (as a is an lValue)
							// result of above is sent to as parameter to second print; which is an rValue
	// above produces:
	//lValue reference
	//rValue reference



	//printB(a) = 20;		// this is not possible as print(a) returns a temporary object; something that expires immediately
							// so can not assign to it; it is an rValue reference

							// this is why second print before called the second printA

	// if you change to return by reference instead of value [ie change from int print() to int& print() then line 82 is valid
	// means printA(printA(a)) // will print lValue reference

	cout << "Part 3" << endl;
	

	printC(a) = 20;			// so basically creates NO temporary objects, no local objects;
							// so we can assign to it here value of 20
							// it has a memory location; not an object expires soon

	printC(printC(a));		// here second print gets called to the lValue reference here
							// because printC(a) can be put on the left side of assignment
							// note that printC(a) = 20; wasn't needed it was to demonstrate
	


}