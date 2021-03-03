#include <iostream>

using namespace std;


unsigned int fib(unsigned int n)
{
	if (n == 0)
		throw "Index 0 is not a valid index.";
	if (n > 47)
		throw 10;		//value doesn't matter, just the type

	unsigned int val1 = 0, val2 = 1;
	for (auto i = 0u; i < n; ++i)
	{
		auto tmp = val1 + val2;
		val2 = val1;
		val1 = tmp;
	}
	return val1;
}


int main()
{
	// Recursive Functions
	// a function that calls itself
	// if a function has to call itself we say we have a recursive call
	// and at some point we have to be aware we have to break out; exit condition from recursion

	for (auto i = 0; i < 50; ++i)
	{
		try
		{
			cout << i << ". " << fib(i) << endl;
		}
		catch (const char* error)
		{
			cout << error << endl;
		}
		catch (int)		// or use catch(int error) to catch value
		{
			cout << "The index was too large." << endl;
		}
		catch (...)
		{
			cout << "Something bad happened - I don't know what.";
		}

		
	}

	// works but larger values of i cause an overflow; unsigned int will overflow
	// switching to a type that can hold larger number is a tempory fix as same issue can occur for sufficiently large i

	// want to say to the client that they provided a bad param when they give a bad param
	// we use exceptions to do so
	// we throw something; that something must be a c++ object either like a fundamental or a custom type object

	// when a functions throws or raises an exception the whole function is interrupted; nothing else gets executed
	// we then jump to some code that will be able to handle (catch) these exceptions
	// when we catch exception we need to indictate the type of exception we want to handle

	// we need each type of exceptions to generate a diff type of exception; else it can't distinguish between them

	// if we neglect to add the catch for each exception type an exception is generated and if in the program there is no
	// code to handle that exception ( a catch) then it will lead to a crash
	// can catch all exceptions with catch (...)
	// useful to catch something that maybe occurred you did not plan for

	// order matters for catch blocks
	// 
}