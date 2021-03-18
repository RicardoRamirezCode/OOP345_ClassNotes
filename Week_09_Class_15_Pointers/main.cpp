#include <iostream>

using namespace std;

void foo(char* dest, char* src)
{
	while (*dest++ = *src++);	// this evaluates to zero when \0 is copied into dest
	// first dereferences, applies it to the dereference of dest; then increments
}


int main()
{
	// pointers - variables that store an address (of anything that can exist in memory; functions, variables, etc)
	// attaching types to pointers allow us to know how to interpret the bytes at that address
	// ie for integer starting at an address the next four bytes will be interpreted as a single piece of information, the integer itself
	// for a char only one byte, etc

	// statically allocated array of characters
	char s[]{ "Hello" };
	// note s now refers to an address of characters, the first byte of that array
	// as such all elements of that array are stored consecutively

	int i = -1;
	cout << "Iterating over array printing address of it's elements [incorrect method]\n";
	// itterate over the array and print its address
	while (s[++i] != '\0')
		cout << "0x" << &s[i] << " -> " << s[i] << endl;
	/*
	0xHello -> H
	0xello -> e
	0xllo -> l
	0xlo -> l
	0xo -> o
	*/

	// issue is &s[i] has type char* and insertion operator with char* will print the array itself not the address
	// need to strip away information about type

	i = -1;	// resetting i
	cout << "\nIterating over array printing address of it's elements [correct method]\n";
	while (s[++i])
		cout << "0x" << reinterpret_cast<void*>(&s[i]) << " -> " << s[i] << endl;

	// void* is generic pointer that doesn't store information about type
	// this reinterpret_cast is needed for this type as it has insertion overload
	// changed condition; will interpret s[++i] as boolean


	// above accesses using indexes but can also access using pointers

	//char* it = &s[0];	// iterator and initializing it for first element of array
	char* it = s;
	// easier way of writing; as s is interpreted as 'address of first element of array'

	cout << "\nIterating over array using iterators printing address of it's elements\n";
	while (*it)
	{
		cout << "0x" << reinterpret_cast<void*>(it) << " -> " << *it << endl;
		++it;
		// need character located at address stored at it; so need to dereference it; *it
	}
	
	it = s;		// reset iterator to first element
	char* end = s + 5;		// element beyond the last one of the array; address of first element + 5
							// +5 gives character after 'o' which is \0

	cout << "\nIterating over array using iterators printing address of it's elements [end iterator method]\n";
	while (it != end)
	{
		cout << "0x" << reinterpret_cast<void*>(it) << " -> " << *it << endl;
		++it;
		// need character located at address stored at it; so need to dereference it; *it
	}


	cout << "\nString copy:\n";
	char s1[]{ "Hello" };
	char s2[]{ "world" };

	cout << "S has value : " << s1 << " -- s2 has value : " << s2 << endl;
	foo(s1, s2);
	cout << "S has value : " << s1 << " -- s2 has value : " << s2 << endl;


	////////////////////////////////////
	// string literals

	char sliteral[]{ "Hello" };
	// literals are values themselves; above is a string literal
	// c++ sees this as constant [unmodifiable]
	
	// char* p = "Hello";
	// cannot do as p is not marked as constant, and you could attempt to change it : p[0] = 'A';
	// should always use const when using string literals to be as strict as possible
	
	const char* p = "Hello";
	// here compiler doesn't complain as you set it to const

	// reason for this const is strings and intergers are most used types in programs
	// desingers of the languages, to optimize, if we use literal "hello" it will exist in memory somewhere and only exist in one place
	// so any other parts that use this string literal will get this exact string (not a copy)

	const char* q = "Hello";

	// now both p and q are string literals hello
	// on line where q is declared compiler will notice q will store the address of an already existing string literal
	// and doesn't allocate new memory but just reuses that address

	// s does not have the same address as
	// s is not storing the address of a string literal; s allocates its own memory and initializes that memory
	// with that array of characters
	// so p stores the address of that string literal; s has its own memory that will copy that string into
	// this is why s does not have to be constant (as it has its own memory)

	cout << "\nVerifying addresses of string literals\n";

	cout << "s = [" << reinterpret_cast<void*>(s) << "]\n";
	cout << "p = [" << reinterpret_cast<const void*>(p) << "]\n";
	cout << "q = [" << reinterpret_cast<const void*>(q) << "]\n";


	////////////////////////////
	// references
	cout << "\nWorking with references\n";
	// char* tells us the type; the & after tells us it's a reference to that type
	// so its a reference to a pointer
	const char*& rp = p;

	// note you can not create a pointer to a reference!
	// const char&* rp = p; -------- not allowed

	cout << "rp : [" << rp << "] p : [" << p << "]\n";

	// cannot change string literal but can change p
	p = "World";
	cout << "rp : [" << rp << "] p : [" << p << "]\n";
	// p now points to different 'variable' but both rp (reference to p) and p are the same just different names
	// again rp is const but address stored in rp is not constant












}