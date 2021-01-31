#include <iostream>
#include <string>

using namespace std;

union ID
{
	char m_strID[20];	// 20 bytes
	long long m_id;		// 8 bytes

	// if you have string for example, will create issues
	// as you can not put custom types in here
	// if you use fundamental types will be no issue

};
// I can choose how the ID will be represented, but don't want to create a structure that will have both attributes
// as we are only going to use one of them


// union allocates memory, everytime I'm going to instanciate; it will allocated memory of the largest member
// so it will use 20 bytes of memory

// in structs it allocates memory for each attribute
// in unions all attributes start at the same address; you get memory for the largest attribute

// so unions will allocate all attibutes to start at the same address
// allowing me to use one of them and not waste memory
// advantages is memory saving
// disadvantage is it's very easy to set an attribute and misuse it somewhere else accessing the data [as once you set it to one attribute it will
// remain that for life of program



int main()
{

	ID theId;		// 20 bytes

	// note if I use the m_id and set it here	
	theId.m_id = 123456789;
	// this will return garbage
	// cout << theId.m_strID << "\n";
	// if I decide theID will use m_id then I should always use that on this instance
	// other instances can use whatever


}