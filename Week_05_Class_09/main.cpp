#include <iostream>

using namespace std;

template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b)			// functions with trailing return type
{
	return a + b;
}
// we need to specify the types at the end; we can't have :
// decltype(a + b) add(T1 a, T2 b)
// as the compiler reads from left to right and it doesn't know about 'a' at that point
// also can't use:
// decltype(T1 + T2) add(T1 a, T2 b)
// as we can't have an expression adding types




int main()
{
	//auto val = 12;		// here compiler can figure out as we initialized val to an int

	decltype(12 + 1.2) val;	// declytype will take the expression and evaluate it's type (not the value) and use that type as the type of val

	cout << "Result: " << add(1, 2.3) << endl;
	cout << "Result: " << add(2.3, 1) << endl;

	// decltype(expr) -- evaluated at compile time
	//					 it doesn't evaluate the expression itself just the type of the expression
	//
	// if "expr" is an xvalue	->	T&&		(will return an rvalue reference)
	// if "expr" is an lvalue	->	T&		(will return an lvalue reference)
	// if "expr" is an prvalue	->	T		(will return just T)
}