// ~cornel.barna/submit workshop1
// submit is a program found in the path ~cornel.barna/
// sending a parameter workshop1

// overload of main function, only two are allowed which is without parameters and with two parameters

// the name is not important (could be n and param instead, but the types are important)
// argc meaning argument count, argv meaning argument values

// argv will be an array of string, and argchow big is the array (ie number of strings)

// char** argv and char* argv[] are equivalent; an array and each element of the array is a string of characters

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
	cout << "The app received [" << argc << "] parameters.\n";

	for (auto i = 0u; i < argc; ++i)
	{
		// note argv is of type char** so deference and select the element at argv[i]
		// note argv[i] is of type char*; which the insertion operator can use and allow the below (with type ostream [cout] and type argv[i] )
		
		// if it were cout << argv; this would be ostream and a char**
		// this would produce a different result (the address) so needed to deference it first with the [i] as it is an array of strings

		cout << i << ". " << argv[i] << "\n";
	}


	// all applications will receive as a first parameter the name of the file, the executable
	// so argc will always be one implicit argument (the application name) and whatever else you pass (the explicit ones)


	// passing parameters through VS instead of CLI
	// change by adding in properties menu to add more parameters

	// if you want to include spaces as part of the argument and not a separator need quotation marks

	// if an argument passed is, for example 10, a number and not a string
	// is an array of characters, but want to interpret as an integer
	// no casting operator will work
	// need to parse it instead, that goes from character to character and interprets as a number

	int val = std::atoi(argv[4]);

	cout << "The number is [" << val << "]" << endl;
}