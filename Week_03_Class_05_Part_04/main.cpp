#include <iostream>
#include <iomanip>

using namespace std;

void memDump(void* p, int cnt)		// starting from address p dump cnt bytes
{
	cout << "Dumping...\n\t";
	//going to see numeric value of each type
	// access every byte, what c++ type can we use for each byte?;
	// answer char; so need to make a conversion to char
	unsigned char* pC = reinterpret_cast<unsigned char*>(p);	// I want to convert to unsigned char* and I want to reinterpret the parameter p
	cout << setfill('0') << hex;

	for (auto i = 0; i < cnt; i++)
	{
		cout << " " << setw(2) << (unsigned int)pC[i];	// else operator would try to print character to screen and we want to strip that
	}

	cout << setfill(' ') << dec << endl;
}


int main()
{
	int* ptrI = nullptr;		// here int tells us how to interpret the data stored at the address stored in the pointer
					// it means the address stored in ptrI, I should take four bytes and interpret them as an interger

	void* ptr = nullptr;		// generic pointer - type is not specified
					// here, at the address stored in ptr but don't know how to interpret the data at that address
	
	// can't do this as you don't know how to interpret the address; can't dereference
	// cout << *ptr;

	// Generic pointers CANNOT be dereferenced
	// need to associate a type to the pointer before you can dereference; you can store an address
	// void is type and void is an incomplete type


	int arr[5] { 1,2,3,45 };
	memDump(arr, 20);		// array of 5 elements, each element is an integer, so total cnt is 20
	cout << endl;
	
	double val = 1.234455677;
	memDump(&val, 8);		// because the function accepts void* I can pass that is a pointer, type will be stripped away
	cout << endl;

	char str[]{ "Hello" };
	memDump(&str, 6);		// number of character of "Hello" plus one for null terminator
	cout << endl;


	/////////////////////////////////////////////
	size_t;		// size_t means an unsigned integer and _t means it's a type

	// they are always relying on some underlying type, some fundamental type behind it
	// here size_t is a redefinition of unsigned int
	// so size_t is an alias of unsigned int

	// other types that c has added
	wchar_t;		// capable to store the biggest installed character set on your machine (depends on machine)
	char16_t;		// uses UTF-16 encoding
	char32_t;		// UTF-32 encoding

}