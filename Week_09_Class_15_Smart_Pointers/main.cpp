#include <iostream>
using namespace std;

struct Foo
{
	void process()
	{
		cout << "Starting process ...";
		// ....
		// assume some error
		throw "Error";
		cout << "Process complete\n";
	}

	~Foo()
	{
		cout << "~Foo() called\n";
	}
};

// this function will create an instance of type Foo dynamically (not statically)
void bar()
{
	Foo* theFoo = new Foo();

	try
	{
		theFoo->process();
	}
	catch (...)
	{
		delete theFoo;
		throw;
		// rethrow the exception; pass it forward on the call chain as I don't know how to handle
	}
	

	//to avoid memory leak need to delete instance
	delete theFoo;
}

int main()
{
	// process will have some error, will throw, bar (the caller) doesn't know how to handle it and it will be caught by main()
	// means destructor is never called; delete theFoo is never executed in bar()
	try
	{
		bar();
	}
	catch (const char* msg)
	{
		cout << "Something bad happened in bar(): " << msg << endl;
	}
	
	// change to bar to have a try/catch fixes issue with memory leak, only reason to have it there is to deallocate
	// theFoo but it complicates the function and causes repetition (as two deletes in bar())

}