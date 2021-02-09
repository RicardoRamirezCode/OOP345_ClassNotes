#include <iostream>

using namespace std;

namespace detail
{
	template<typename T>
	struct value_category
	{
		//static char* value = "prvalue;
		// above won't work as type
		//const char* value = "prvalue";
		// this above would work; however if we make it static it will not it means I can not initialize inside the class
		static constexpr char const* value = "prvalue";

		// equivalent to:
		// static constexpr const char* value = "prvalue";  // as const will tie itself to the nearest type (to char not the pointer *)
	};

	// now we specialize it; here if we receive an lvalue reference
	template<typename T> struct value_category<T&> { static constexpr char const* value = "lvalue";};
	template<typename T> struct value_category<T&&> { static constexpr char const* value = "xvalue";};

	// so whenever we instanciate using an rvalue reference we are going to get the above last specializtion

}

// creating a macro:
#define PRINT_VALUE_CAT(expr) std::cout << #expr << " is a " \
<< ::detail::value_category<decltype((expr))>::value << endl;


// # means whatever comes after interpret as a string; so above will print the actual expr not evaulating the expression and printing that; only used in macros
// the backslash above tells the compiler the next line is part of the same macro; used if macro is too long


struct S
{
	int i;
};


int main()
{
	// decltype(expr)
	// if "expr" is an xvalue	->	T&&		(will return an rvalue reference)
	// if "expr" is an lvalue	->	T&		(will return an lvalue reference)
	// if "expr" is an prvalue	->	T		(will return just T)


	int val;
	cout << ::detail::value_category<decltype(val)>::value << endl;
	// from global namespace go into namespace detail take the value_category structure and instanciate with a template param decltype with my expr of val
	// and from that type select value
	// however with above we get value category of the variable, but we want the value_category of the expression, so double () are used
	cout << ::detail::value_category<decltype((val))>::value << endl;

	// so second set of round brackets tell it to evaluate as an expression, without it just evaluates as a variable

	PRINT_VALUE_CAT(val);
	PRINT_VALUE_CAT(10);

	PRINT_VALUE_CAT(val++);
	PRINT_VALUE_CAT(++val);

	int&& r = 123;

	PRINT_VALUE_CAT(r);
	// r is an lvalue because we evaulate r as an expression; ie we can have r = 12;
	// however if we get rid of second set of brackets, we get value category of variable itself:
	cout << ::detail::value_category<decltype(r)>::value << endl;

	PRINT_VALUE_CAT(val + val);
	// val + val = 23; can not be done, so not an lvalue

	PRINT_VALUE_CAT(std::move(val));
	PRINT_VALUE_CAT(std::move(r));		// expression r is an lvalue, but std::move(r) is an xvalue



	PRINT_VALUE_CAT(S{ 0 });		// instance of type S; is a prvalue
	PRINT_VALUE_CAT(S{ 0 }.i);		// is an xvalue
}