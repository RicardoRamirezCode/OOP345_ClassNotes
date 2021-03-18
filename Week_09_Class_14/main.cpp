#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	// binary files vs text files
	// files are good for a user to put readable information
	// not as good for accuracy; binary files offer a 'perfect' cloning of data
	// but not readable by humans but machines

	// Streams
	// a sequence of 'things'; in our case a sequence of bytes
	// sequence is not necessarily bounded (where it starts or ends)
	// files are a special case of streams where we know we have an end
	// has a first byte and last byte

	// with streams we have operations: put into stream and extract from stream
	// when we insert we remove their 'meaning'
	// for example when we insert an integer or double into the stream we insert
	// those bytes and remove their 'meaning'
	// when we extact from the stream we only have bytes; which means we have to have
	// sufficient knowledge to associate symantics to those bytes as stream itself
	// does not contain such information

	// we have a hierachy of classes to manage access to streams and to files
	// ios hierachy (input/output hierarchy)

	// ios_base - some members that do not depend on the underlying char type
	// basic_ios - templated class; depends on underlying char type
	// ios - specialization where the template type is set as char
	// istream - reading
	// ostream - writing

	/////////////////////////
	// want to read/write in file using char as underlying type
	// create an instance of fstream (as we want both reading/writing)
	// so need to include header <fstream> and fstream is in namespace std

	fstream file;		// file object created

	// files do not belong to application, files belong to the operating system
	// meaning anything you do with files you need to ask permission from the OS
	// may not have permission, file may be in use, file may not exist if trying to read etc

	// file object is an object to manage communication with system

	// need to attach file object to file on disc
	// this open is doing an association between file object and file on disc
	file.open("file.txt", ios_base::out | ios_base::in);
	// this is saying I want access to this file, but it is here the OS may
	// deny this request; request could fail
	// need to specify how I want to open this file, so I need to specify a few flags
	// ios_base::out		-- means it is an output file (going to write to file)
	// ios_base::in			-- opened as input file (going to read file)
	
	// can specify multiple flags and combine with | which means 'bitwise or'
	// operates on bits not boolean values

	// check if successful
	if (file.is_open())
	{
		clog << "File is open and ready to be used\n\n";
		// do something
		// use insertion operator to insert into file
		file << "A string.";
		
		// Can move around file
		// first param the offset, second param 'from where'/starting point
		file.seekp(-4, ios_base::cur);
		// means from current position, move 4 bytes(positions) backwards

		// seek functions allow us to move in the file
		// seekp - seek put - change the position for writing (write to file)
		// seekg - seek get - change the position for reading (extracting data)
		// standard says to implement both positions in file; visual studio dose
		// not follow standard and uses same cursor for both

		// so we moved cursor for writing in previous function
		file << 'Z';
		// will change from "A string." to "A strZng"
		// reason is WE CAN NEVER INSERT INTO A FILE;
		// if you are in middle of file and start writing you are overriding previous information
		// and replace with new bytes; you can not just shift the bits

		// only alternative is to get file into memory, modify as needed
		// rewrite entire file onto disk

		//////////////////////////
		// for reading will need a buffer to temp store data
		char buffer[16];
		// since visual studio makes both seekp and seekg the same cursor
		// if we attempt to read we will read from where we left cursor above
		// so need to set currsor to begining of stream
		file.seekg(ios_base::beg);
		// above sets cursor to begining of stream

		while (file)	
			// while stream still in a good state
		{
			file >> buffer;
			// extraction operator uses any space as separator
			// space is extracted and discarded and not stored in buffer
			cout << buffer;
		}
		// when you exit from the while loop, you exit when the stream is 'not good'
		// have to make stream 'good' again if you plan to reuse
		file.clear();
		file.seekp(ios_base::end);

		// extraction operator does not check how much memory we allocated to buffer
		// if file content is larger than buffer; extraction operator will keep
		// writing outside of the allocted memory!

		// functions such as get, getline which allow you to say how much memory you have
		// either find the delimiter or number of bytes you instructed to stop at

		double val = 0.1234567890;

		file << val;
		// above will lose precision
		// when you write into text file you will get an approximation

		// break connection between object and file on disc at end
		file.close();
		// at end file destructor will be called and connection closed
		// but safter to close in case of others trying to access file
	}
	else
		clog << "File could not be opened.\n";




}