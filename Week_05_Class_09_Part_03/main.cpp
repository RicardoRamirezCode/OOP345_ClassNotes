#include <iostream>
#include <iomanip>
#include <bitset>

using namespace std;

int main()
{
	cout << "Is unsigned 0 greater than -1? " << (0u > -1 ? "yes" : "no") << endl;
	// above gives correct (for compiler) but not intuitively correct answer of no
	// we can't evaluate expressions (such as 0u > -1) where we have different types; so we need to convert
	// by default compiler reinterprets -1 to unsigned int (ie it reinterprets whatever zeros and ones are there as unsigned int)

	auto a = 0u;

	cout << "Unsigned -1: " << static_cast<unsigned int>(-1) << endl;			// types are convertable so use static cast
	// so this is the result above is the very large number the compiler is using for the previous example

	// bitset is a templated class that accepts one parameter of non template type
	cout << setw(16) << "Unsigned a: " << setw(10) << a << " " << bitset<32>(a) << endl;

	a--;	// arithmetic overflow as it goes outside the range
	cout << setw(16) << "Unsigned a - 1: " << setw(10) << a << " " << bitset<32>(a) << endl;

	// now we can interpret this as an signed int
	// so in b we store the value of a interpreted as signed int
	int b = static_cast<int>(a);

	cout << setw(16) << "Signed a: " << setw(10) << b << " " << bitset<32>(b) << endl;
	// so same bits but interpreted differently
}