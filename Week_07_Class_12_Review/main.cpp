#include <iostream>
#include <string>
#include <string_view>
#include <assert.h>

using namespace std;

int main()
{
	/////////////////////////////////////
	//Static Assert
	// allows you to check if a condition is true at compile time
	// condition has to be evaluated, or can be evaulated, at compile time

	const size_t size = 10;
	static_assert(size == 10, "The value should be 10.");
	// a compile time, compiler will evaluate condition

	// if we remove const from size, we can not evaulate at compile time
	// if we need to evaulate some condition but at run time (not compile time)
	// include assert

	size_t size2 = 10;
	assert(size == 10, "Value should be 10.");
	// will evaluate at runtime, if that evaluation fails. Assert will crash program.




	///////////////////////////////////////
	//const and constexpr

	// const: the value can not be changed after creation
	// constexpr:	-the value can not be changed after creation
	//				-the value must be known at compile time					


	size_t size3;
	cout << "Write a number: ";
	cin >> size3;

	const size_t cSize = size3;
	// have to assign a value, can use size.
	
	cout << "The constant is : " << cSize << endl;

	// the value of cSize is not known at compile time
	constexpr size_t realSize = 12;
	// here value of realSize has to be assigned to value known right 
	int arrReal[realSize];


	/////////////////////////////////////////
	// Stringview
	// lighter version of string

	
	// RECAP: Collections in STL
	// std::vector 			dynamic memory
	// std::array			static memory
	// std::list			double linked list
	// std::forward_list	single linked list

	///// 
	// std::queue			FIFO	(first added first out; conversly last in last out)
	// std::stack			FILO	(first added, last removed)

	// concern how we handle additions and removals; not underlying method of organizing elements



	char arr[]{ "Hello World!" };
	std::string str = arr;				// composition
	std::string_view strV = arr;		// aggregation
	// to use string_view need to include header string_view
	// as well to tell the compiler to use c++17
	// go to settings, properties, c/c++, language, 'C++ Lanuage Selected'
	// change from default to c++17

	// both str and strV are initialized with array of character arr


	cout << arr << " ---- " << str << " ---- " << strV <<  endl;
	
	// update arr
	arr[0] = 'Z';

	cout << arr << " ---- " << str << " ---- " << strV <<  endl;
	// original array was changed, str was changed but strV was changed
	// strV provides a wrapper around existing memory
	// between str/arr we have composition
	// between strV/arr we have aggregation
	// in both we have ownership; 
	// but with str/arr will not take ownership but will make a copy of what client passes and have ownership of some internal data structure
	// strV/arr will maintain a refernece or pointer (in this case a pointer) but not do life management; 
	// string_view will give you a view into array but not allow you to change that arr

	// this is why when we change original array string_view will be effected as it has a view of original array not a copy of it
	// while str has a copy of the original array

	// str will have to allocate memory, do copy operation, etc
	// strV is not duplicating, allocating memory, (shalow copy is good enough)
	
	// string_view can lead to issues
	// if we don't have a statically allocted array for example

	char* arr2 = new char[13]{"Hello World!"};
	std::string str2 = arr2;
	std::string_view strV2 = arr2;

	cout << arr2 << " ---- " << str2 << " ---- " << strV2 <<  endl;

	// however if we delete[] arr2
	// we broke strV; strV2 will now have undefined behaviour (crash, or garbage data to screen)
	// strV2 just maintains a reference to outside array, so in this case that caused an issue when we deleted outside array

	// if we just need to view string, pass a parameter, don't need to change string (concat) then string_view is perfect
	// if we need to modify strings, then std::string


	// aside:
	//strV[2] = "Z";	// not allowed

	strV = "Goodbye";
	// is allowed, we are chaning the string_view instance not the underlying string



}