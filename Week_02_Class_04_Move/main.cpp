#include <iostream>

using namespace std;

// the lValue/rValue references are useful when dealing with resources

class Foo
{

	short* m_resource;		// dynamically allocated array of shorts
							// could have short* m_resources {nullptr} or in copy constructor to handle
	size_t m_size{ 0u };			// size_t : unsigned int (not necessarily int, the underlying type depends on platform we are working on)
							// standard says size_t should be able to store the size (bytes) of the largest object that can exist in memory
								// some example of large objects would be large arrays

								// static member variable-----type variable
	static int m_cnt;		// shared by all instances

public:
	
	// static function--------type function (type member)
	static int getCounter();

	// custom constructor
	Foo(size_t size) : m_size{size}
	{
		//m_size = size; // did implementation in initialization list
						// more efficient, the value size will be assigned to the object from the moment of creation
						// while in body it has garbage first before assignment
						// () are like you are calling a constructor; but conversions might occur if you do use them
							// so the compiler just checks if they are compatible and if a conversion can be made
						// {} no conversion will occur; a bit safer as type checking is more strictly enforced

		cout << "Foo(int): " << this << endl;

		++Foo::m_cnt;

		m_resource = new short[m_size];			// we are assuming m_size is valid
		
		for (auto i = 0u; i < m_size; ++i)		// u means to interpret 0 as unsigned number
		{
			m_resource[i] = i - 5;
		}

	}

	// copy constructor
	Foo(const Foo& rightOp) : m_resource{nullptr}
	{
		cout << "Copy constructor: " << this << endl;

		++Foo::m_cnt;

		*this = rightOp;		// issue here is you would get a crash when you call the assignment operator as the delete is called on the current object
								// and current instance contains garbage
								// so need to initialize in initialization list the m_resourse to nullptr; else we could do when defining the members of Foo
								// result is same in both cases
	}

	// assignment constructor
	Foo& operator=(const Foo& rightOp)
	{
		cout << "Copy Assignment operator (=) : " << this << " from " << &rightOp << endl;
		if (this != &rightOp)
		{
			// clear-up; deallocate the resourse
			delete[] this->m_resource;

			// do check here to make sure other is not null and extend; ignoring that possiblity

			// shallow copy
			this->m_size = rightOp.m_size;

			// deep copy
			this->m_resource = new short[rightOp.m_size];
			for (auto i = 0u; i < rightOp.m_size; ++i)
			{
				m_resource[i] = rightOp.m_resource[i];
			}
		}

		return *this;
	}

	// move constructor							// Foo&& is called a move reference, or rValue reference
												// responsible to move the content from the parameter into current instance
	Foo(Foo&& other)
	{
		cout << "Move C: " << this << " from " << &other << endl;

		++Foo::m_cnt;

		*this = std::move(other);			// need std::move() else will call the standard assignment constructor
	}

	// move assignment operator
	Foo& operator=(Foo&& other)
	{
		cout << "Move =: " << this << " from " << &other << endl;

		if (this != &other)
		{
			//clean-up
			delete[] m_resource;

			// shallow copy
			m_size = other.m_size;
			m_resource = other.m_resource;

			// reset the other object
			// as current instance is going to take ownership of the resource
			other.m_resource = nullptr;		// really preparing it for the the destructor
											// also if we leave out when destructor is called on other it will break current object instance *this

			// can also reset other attributes of other, not really needed in this example
			other.m_size = 0;
			 
		}

		return *this;

	}


	// destructor (mandatory as you have a resource)
	~Foo()
	{
		cout << "~Foo(): " << this << " Deleting [" << m_resource << "]" <<  endl;
		delete[] m_resource;
	}

};

int Foo::m_cnt = 0;

int Foo::getCounter()
{
	return Foo::m_cnt;
}



int main()
{
	// calls custom constructor
	// compiler will see buiding an object f based on number 7; and will look inside class and see constructor that accepts number exists
	Foo f = 7;

	// here going to get a (custom) constructor to build a new object, and assignment operator will take care of assignment
	f = Foo(2);
	// sequence of events: when we build the second object ( a different address than first) and they we get the copy assignment operator
	// copying into the first object from teh second object;
	// then Foo(2) goes out of scope imediately [is local, temp and only exists on line 93)

	/*Foo(int): 00CFFCCC
	Foo(int): 00CFFBFC
	Copy Assignment operator (=) : 00CFFCCC from 00CFFBFC
	~Foo(): 00CFFBFC
	~Foo(): 00CFFCCC*/

	// this requires a lot of work, allocated memory, deallocated memory, copied from the other object, deallocated memory again
	// copy in third line is copying content from an object that will disappear soon

	/*
	Note, the copy operations recevies a parameter of const. As the object is still useful so we don't want to touch it. So they protect the original object
	But the move operators will receives the paramater,some objects that about to die. So we 'steal' the contents as it will die soon. Simply moves the
	contents (from the parameter) into the current object.


	Also if you wanted to you could:
	Foo f1 = std::move(f);
	This forces a move, if your design doesn't need object f anymore further; f is not used anymore. 
	
	*/

	/*
	Rule of 5:
	Need these for any class that manages a resource

	Foo(const Foo& other);
	Foo& operator= (const Foo& other);
	Foo(Foo&& other);
	Foo& operator= (Foo&& other);
	~Foo();

	
	*/

	//////////////////////////////////////////////////////////////////////////////

	// Instance variables
	// examples are the m_resource
	// every instances has its own attribute called m_resource
	// vary from type variables



	//Type Variables (the static member variable)

	// will exist in memory for entire duration of program (before main even starts this counter will receive memory)
	// shared by all instances
	// because static counter is not specific to every instance it shouldn't be initialized in the contstructor
	// belongs to type not instance

	// note that m_cnt is declared not defined
	// have to defined it separately from it's instances
	// defined above on line 137

	// note static variables are automatically initialized to 0; so the '=0' is optional in our case.


	cout << "\nThere are [" << Foo::getCounter() << "] instances created\n" << endl;





	//static function--------type function (type member)
	// These do not have instances needed like type variables, so don't have '*this' available
	// also implementation occurs outside like with m_cnt above.



}