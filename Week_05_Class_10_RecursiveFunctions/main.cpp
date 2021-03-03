#include <iostream>

using namespace std;

// iterative method
unsigned int fib(unsigned int n)
{
	size_t val1 = 0, val2 = 1;
	for (auto i = 0u; i < n; i++)
	{
		auto tmp = val1 + val2;
		val2 = val1;
		val1 = tmp;
	}
	return val1;
}

// recursive method
unsigned int fibR(unsigned int n)
{
	// exit condition from recursion
	if (n <= 2)
		return 1;
	return fibR(n - 1) +fibR(n - 2);
	// so if n >2 then we return above
	// it calculates fibR at n-1 and fibR at n-2 and returns it as result of fibR at n (adding previous two values)
	// dynamic programming could be used here
}


int main()
{
	for (auto i = 1; i < 47; ++i)
	{
		cout << i << ". " << fibR(i) << endl;
	}

	// while recursive method is simplier than iterative method, there is a price to pay
	// more inefficient. same index is calculated over and over multiple times
	
	// so two things to consider for recursive functions:
	// need an exit condition (will be stuck in an infinite recursive call and will get a stack overflow error)
	// might be more inefficient

	// we get a stack overflow because of parameters; evertime we call a function we put one more parameter to the stack
	// function is NOT on the stack but PUTS stuff on the stack
	// even if function doesn't put param on the stack there are still things added on the stack on background (like return address)
}