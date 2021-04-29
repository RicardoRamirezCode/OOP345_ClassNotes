// Macros and Multi-Dimensional Arrays

#include <iostream>
#include <chrono>

#define PI 3.14

#define DEBUG

using namespace std;

#define DEBUG_MSG (\
	std::clog<< "\33[38;5;9mDEBUG \33[38;75m" \
		<< __FILE__ \
		<< "\33[38;5;9m:\33[38;5;87m" << __LINE__ \
		<< "\33[39;5;9m " << __func__ \
		<< " \33[38;5;214m" << reinterpret_cast<const void*>(this) \
		<< "\33[38;5;9m --> \33[0m")

// function-like macro
#define POW(P) P * P * P

int pow(double p)
{
	return p * p * p;
}

class Foo
{
public:
	Foo()
	{
#ifdef DEBUG
		DEBUG_MSG << "Initializing the Object" << endl;
#else
		cout << "Not debugging" << endl;
#endif
	}
	~Foo()
	{
#ifdef DEBUG
		DEBUG_MSG << "Destroying the Object" << endl;
#endif
	}
};


//////////////

struct space_out : std::numpunct<char>
{
	// groups of digits will be separated by this character
	char do_thousands_sep() const
	{
		return ' ';
	}
	// need to tell compiler how many digits will be in a group
	std::string do_grouping() const
	{
		return "\3";
	}
};


int main()
{
	// from current object (cout.getloc() replace with new space_out
	cout.imbue(locale(cout.getloc(), new space_out));
	// note new is dynamic memory; however this object locale will take ownership of this dynamic memory and handle
	// its destruction



	// pre-processing directives
	// handled at stage 1
	// compiler does not see the pre-processing directives (theses are done to prepare for the compiler)

	// anything starting with #

	// Symbolic name
	// not really variables, more a symbolic name for something
	// #define PI 3.14
	// means each time we have PI pre-processor will replace with value 3.14

	cout << PI << endl;

	// this PI is not a variable. So it doesn't have an address nor can its value be changed 
	// it is a symbolic constant

	// Pre-processing file
	// we can tell compiler to create this file including pre-processing on disc instead of memory

	// in options/settings
	// C/CC++ -> Pre-processor -> Pre-process to a file
	// will produce an error as second and third stage not completed, but file will be on disc
	// in Debug directory, each module will have a *.i file

	// the *.obj file is the result of the second stage of compilation
	// the *.exe file it the result of the third stage of compilation


	//////////////////////////////////////

	Foo aFoo;

	// if you needed to debug and wanted to add cout statements to each call of Foo() and ~Foo() would be hard to maintain

	// __FILE__ predefined macro will be replaced with name of file that uses DEBUG_MSG
	// __LINE__ line that uses this macro
	// __fucn__ name of function that uses this macro
	// reinterpret_cast<const void*>(this)
	// address of current instance
	// goijng to remove any semantic from the pointer just in case it defines an insertion opertor for the pointer


	// while you could define a function the issue is:
	// function does not have "this"
	// as well it will return information on the function instead; ie __func__ will be expanded to the function instead

	////////////////////////
	// Pre-processing Conditionals
	// to set DEBUG on or off could use an if statement but that adds overhead and takes time at runtime
	// would like this debug message removed from binary files when not doing debugging
	// can accomplish with conditionals

	// debug not enabled so pre-processor will not enable if branch; will leave the else
	// to enable can just add define DEBUG

	// so when we dont' enable debug we pay ZERO PERFORMANCE penalty coming from debug instructions;
	// debug code will not exist in the binary

	///////////////////////////////////////

	// function like macro
	// macros can be used like functions as well

	cout << POW(3) << endl;

	// advantages of macros:
	// faster - execute faster than a similar function
	// no type checking; in POW I can provide any type that supports *
	// while for function I have type checking ( or conversion will be made if needed)
	{
		// time stamp before we start evaluating macro
		auto start = chrono::high_resolution_clock::now();

		// evaulate macro:
		for (auto i = 0; i < 100000; i++)
		{
			POW(1.1234567890123456789);
		}		

		// time stamp at end of event
		auto end = chrono::high_resolution_clock::now();

		cout << "Macro: [" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "]\n";
	}

	{
		// time stamp before we start evaluating function
		auto start = chrono::high_resolution_clock::now();

		// evaulate function:
		for (auto i = 0; i < 100000; i++)
		{
			pow(1.1234567890123456789);
		}		

		// time stamp at end of event
		auto end = chrono::high_resolution_clock::now();

		cout << "Function: [" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "]\n";
	}

	// the overhead is shadowing the time to complete the caculations (chrono objects, etc)
	// so need to do the operation is a loop
	// this will make the overhead insignificant to the time calculation


	// disadvantes is easy to introduce an error
	cout << POW(2 + 1) << "---" << pow(2 + 1) << endl;
	// issue is you expect it to evaluate the parameter first; function does this above but macro does not
	// gives 2 + 1 * 2 + 1 * 2 + 1
	// could rewrite to:
	// POW(P) (P) * (P) * (P)  // ensures expression is evaulated first
	

	///////////////////////////////////////////////////
	// Customize Displaying Numbers 

	// would like to separate three digits by a character, a ' '
	// need to create some instruction for the cout object how to print numbers

	// then need to tell cout about this using cout.imbue as above



	///////////////////////////////////////
	// Multi-Dimensional Arrays
	cout << "Multi-Dimensional Arrays" << endl;
	// single dimentional array; receives memory on stack
	int arr[10];
	// single dimensional array; on the heap
	int* pArr = new int[10];

	{
		cout << "\nstatically allocated array" << endl;
		// statically allocated array
		// 3 rows, 2 coll; need to specify one row at a time
		int matrix[3][2]{ {2, 4}, {3, 5} };

		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 2; ++j)
				cout << "a[" << i << "][" << j << "] = " << matrix[i][j] << endl;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 2; ++j)
				cout << matrix[i][j] << " ";
		}
	}

	{
		cout << "\n\ndynamically allocated array" << endl;
		// dynamically allocated array

		int** p = nullptr;

		size_t rows = 5;
		size_t col = 6;

		// to figure out type of new need to look at type and 'remove one *'
		p = new int* [rows];
		// above is a dynamically allocated array of pointers...

		for (auto i = 0; i < rows; ++i)
		{
			p[i] = new int[col];
			//... and each is a pointer to another dynamically allocated array
			for (auto j = 0; j < col; ++j)
				p[i][j] = 2 + i + j;
		}

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < col; ++j)
				cout << p[i][j] << " ";
			cout << endl;
		}

		// clean-up (need six deletes)
		// p is a pointer (it's static)
		// it 'points' to a dynamic array (of type int*) (1) 
		// each of those to a dynamic array (5)
		// so that gives 6 deletes

		for (int i = 0; i < rows; ++i)
		{
			delete[] p[i];
		}
		delete[] p;

	}

}