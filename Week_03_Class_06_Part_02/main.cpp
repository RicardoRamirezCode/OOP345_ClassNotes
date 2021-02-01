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



template <typename T, int N = 10>		// sets default value of N to 10;
void print(T val)
{
	cout << "\33[92m" << setw(N) << typeid(val).name() << "\33[0m" << setw(20)<< val << "\n";
}



class FooNew
{
	int m_value;
public:
	void display()const;
};


void FooNew::display()const
{
	cout << typeid(*this).name() << endl;
}


int main()
{
	auto val = 32;
	print<int, 10>(val);		// here we have to be explicit with value of N but with updated template above added a default value of N
								// so not needed to specifiy type and N value

	auto valID = 1.2;
	print<double, 10>(valID);

	Foo aFoo;
	print<Foo, 10>(aFoo);

	
	// can also explicitly state type as above examples
	
	// but compiler can figure out template type usually
	// but if compiler can't figure it out you can force it as above

	// can also pass values as parameters in template

	// however all templates must be known at compile time
	// so can't use cin>>size to pass size as parameter to above as N
	// as value of size is not known at compile time
	// however can use constexpr

	constexpr int size = 10;

	// because compiler needs access to the source code during the compilation process
	// templates must be implemented in headers
	// because if you implement them in cpp you can not use them in another module as compilation happens per module
	// so when it compiles a module it needs access to the template code to generate the actual code that gets compiled

	// Templates are implemented only in headers not cpp files

	//////////////////////
}