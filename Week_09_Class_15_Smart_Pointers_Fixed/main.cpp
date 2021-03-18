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

// smart pointer; this pointer is only for instances of type Foo
// this will manage a pointer to Foo, exclusive ownership
class FooPtr
{
	// this instance will take ownership of the pointer and control the life of another instance (composition relation)
	// dynamically allocated
	Foo* theFoo = nullptr;
public:
	// first need to take ownership of an instance of this type Foo
	explicit FooPtr(Foo* aFoo) : theFoo{aFoo} { }
	// don't want instances of FooPtr that will share the resource;
	// when acquired resourse it acquired it exclusively; will not be shared with other instances
	// dont allow copies
	FooPtr(const Foo&) = delete;
	FooPtr& operator=(const Foo&) = delete;

	// allow move the the resource between instances of type FooPtr
	FooPtr(FooPtr&& other) noexcept
	{
		this->theFoo = other.theFoo;
		other.theFoo = nullptr;
	}

	FooPtr& operator = (FooPtr&& other) noexcept
	{
		if (this != &other)
		{
			delete theFoo;
			this->theFoo = other.theFoo;
			other.theFoo = nullptr;
		}
		return *this;
	}

	// overload the member selection operator (->)
	Foo* operator->()
	{
		return theFoo;
	};

	// overload the dereference operator
	Foo& operator* ()
	{
		return *theFoo;
	}

	// manage life - this means instance MUST BE dynamically allocated
	~FooPtr()
	{
		delete theFoo;
	}

};

// this function will create an instance of type Foo dynamically (not statically)
void bar()
{
	
	FooPtr theFoo(new Foo());
	// created an instance of this wrapper, then using it like I have a pointer to Foo

	// the following won't work as we need to overload -> and dereferencing opearator to access actual object
	theFoo->process();
	// uses -> to select process from inner instance

}

int main()
{
	// solution is to create another class that will take ownership of pointer (theFoo) and make instances of that class
	// and when instances of that class goes out of scope that instance will be responsible to delete
	try
	{
		bar();
	}
	catch (const char* msg)
	{
		cout << "Something bad happened in bar(): " << msg << endl;
	}
	
	// we don't have memory leak as we have an instance of type FooPtr in bar()
	// then we use that instance to call the function process on next line
	// something bad happens in process()
	// then all local variables in the this function bar go out of scope
	// then it will call the destructor for FooPtr
	// destructor for FooPtr manages resources (it dealllocates dynamically allocted memory)

	// this class is implemented in STL under the name std::unique_ptr<T>
	// templated class
	// the ptr we implemented and unique_ptr from STL; latter does not allow:
	// FooPtr theFoo = new Foo();
	// to disable automatic conversions need to change constructor
	// making it explicit means constructor must be explicitly called by programmer

	// if we have a function as such:
	/*void doSomething(FooPtr inst)
	{
		cout << "Doing something.\n";
	}*/;

	// and try to call this inside of bar():
	// doSomething(new Foo());
	// here we need a param of instance Foo; if compiler does not have it will look for any conversion that can be done
	// to make 'new Foo()' to whatever the type needed is
	// compiler will see constructor and select that constructor to do conversion; using explicit forbids that

	// could still do this way:
	/*Foo* secondPtr = new Foo();
	doSomething(secondPtr);*/
}