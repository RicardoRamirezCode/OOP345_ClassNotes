#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Foo
{
	double arr[4]{};
	int val = 0;
};


int main()
{
	fstream file;
	file.open("file.txt", ios_base::out | ios_base::in | ios_base::trunc | ios_base::binary);


	// instance of Foo
	Foo theFoo;
	theFoo.val = -123;
	theFoo.arr[0] = 1.0 / 3;
	theFoo.arr[1] = 4;
	theFoo.arr[2] = 76;
	theFoo.arr[3] = 543;


	// dynamically allocted array of doubles
	double* arrDyn = new double[4];
	
	arrDyn[0] = 1.0 / 3;
	arrDyn[1] = 4;
	arrDyn[2] = 76;
	arrDyn[3] = 543;


	if (file.is_open())
	{
		clog << "File is open and ready to be used.\n";

#pragma region CUSTOM_TYPE

		// writing instance of Foo in stream
		// first pointer for writing [byte array for writing]
		const char* byteArrW = reinterpret_cast<const char*>(&theFoo);
		// strips aways all the symantics about what the instance of Foo is
		// lost organization, members, which one is first, etc; just became an address to bytes

		// writing into the file
		file.write(byteArrW, sizeof(theFoo));

		// copy of type Foo
		Foo copy;	// this instance is empty

		file.seekg(ios_base::beg);
		char* byteArrR = reinterpret_cast<char*>(&copy);
		file.read(byteArrR, sizeof(copy));
#pragma endregion

		// write into file dynamic array; pass address of arrDyn which is just 'arrDyn'
		const char* byetArrWDynamic = reinterpret_cast<const char*>(arrDyn);
		file.write(byetArrWDynamic, 4 * sizeof(arrDyn[0]));		// four elements and their sizes

		double copyDynamic[2]{};
		file.seekg(ios_base::beg);
		//file.seekg(8, ios_base::beg);
		// means from beginning move 8 bytes (one double) from beginning
		char* byteArrRDynamic = reinterpret_cast<char*>(&copyDynamic);
		file.read(byteArrRDynamic, 2 * sizeof(copyDynamic));		// only going for first two elements

		file.close();
	}
	else
		clog << "File could not be opened.\n";

	delete[] arrDyn;

	// can't do this with dynamic as addresses will be done at runtime based on whereever there is available memory
	// if you write an address into file when you load that address from the file it's garbage
	// so if you have a custom type that has attributes that are addresses, you can't dump them into a file as above



	///////////////////
	// String Stream

	// string stream object
	stringstream ss("12 54# 7"); // using in constructor an array of numbers
	// so created a stream of memory and in that stream put these characters

	// now want to extrac from that stream something, now can use ss with extraction/insertion operators, get, getline
	int v1 = 0;
	ss >> v1;
	std::cout << v1 << endl;		// gives first as 12; gives it as a NUMBER

	char arrSS[10];
	ss.getline(arrSS, 10, '#');
	std::cout << arrSS << endl;

	// first extraction is 12
	// second extraction is everything up to delimiter # so ' 54'
	
}