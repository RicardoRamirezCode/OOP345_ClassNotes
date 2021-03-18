#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	double val = 0.1234567890123456789;


	fstream file;
	file.open("file2.txt", ios_base::out | ios_base::in | ios_base::trunc | ios_base::binary);

	if (file.is_open())
	{
		clog << "File is open and ready to be used.\n";
		file.seekp(ios_base::beg);

		//file << val;
		// above will lose data, when we put into file it will be an approximation
		// binary files solve this issue

		// opening file with ios_base::trun
		// means erase all in file
		// ios_base::binary
		// open file in binary

		// << operator, get, getline are specifically meant for text files

		// to write in binary file 
		// first param: address of first byte I want to write; needs to be array of bytes/chars
		// need a pointer to char so need to use reinterpret_cast
		// second param: from that address how many bytes should I write
		// val is 8 bytes but to be safe, in case we make alterations, we use sizeof
		
		// write a number into the file
		const char* byteArr = reinterpret_cast<const char*>(&val);
		
		file.write(byteArr, sizeof(val));

		// read from the file
		// 1st move to begining of stream
		file.seekg(ios_base::beg);
		double copy = 0;
		// we use read from binary files; instead of extraction operators, get, getline which are used for files
		char* readByteArr = reinterpret_cast<char*>(&copy);
		file.read(readByteArr, sizeof(copy));
		// first param where to store data
		// second param how many bytes to read

		// in above read all data is recreated WITHOUT ANY LOSS OF INFORMATION
		// both val and copy are the exact same


		file.close();
	}
	else
	{
		clog << "File could not be opened.\n";
	}

	//1:02:54
}