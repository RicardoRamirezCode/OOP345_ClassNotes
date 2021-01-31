#include <iostream>

using namespace std;




int main()
{
	int a[5]{1, 56, -3};				// type of a is int[5]
				// c style array of type integers
				// an array of a group of items,
				// all items same types
				// all allocated contigously in memory
	// so four bytes representing the first integer, followed by another four bytes for the second int,... up to five elements

	for (auto elem : a)
	{
		cout << elem << ", ";
		elem += 1;		// elem will be a copy of every element from array
	}
		
	cout << endl;

	// need to capture every element by reference, so change is made to a; to do so add (auto elem& : a)

	for (auto elem : a)
	{
		cout << elem << ", ";
		elem += 1;
	}

	cout << endl;

	// acts like 'for each';
	// so for each int element in array a...do this... (changed from int to auto, see below for reason)
	// can be used only on statically allocated arrays
	// could use int instead of auto; however if you change your type you don't have to update

	int* arr = new int[6];			// type is int*
	// can't use the previous
	// arr is a pointer to the first element of the array, it's not an array as previous example
	// so for loop wouldn't know where to stop
	// arr is a pointer it doesn't contain information on where to stop / size of array

	// type of a is int[5]
	// compiler knows size as it's part of type
	// type of arr is int*

}