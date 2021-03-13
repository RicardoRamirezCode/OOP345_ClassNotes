#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

void foo(double val)
{
	cout << val << endl;
}

int main()
{
	// always the case it is a collection of objects (words, 'cars', integers, etc) and we need to do 'something' with that collection
	// STL helps perform common operations on those collection of data; and can be aplied to almost any collection of data

	std::vector<int> coll = {12, 76, 32, 8, 43, 13, -43, -5, 0};
	
	// could print to screen using this method
	//
	cout << "Standard iteration over collection:" << endl;
	for (auto i = 0; i < coll.size(); ++i)
		cout << coll[i] << ", ";			// this vector has overloaded the square brackets operator so we can use it to select a certain element at an index

	// may not want manual method; want a partial/subset of collection for example
	// for_each will perform operation for each element of array
	// need to include:
	// #include <algorithm>
	// applies a function object (something that can be used like a function); instance or pointer to a function
	// applies this f to result of DEREFERENCING every iterator in range [first, last)
	// 	   means it will apply to the result of derefercing every iterator in range this function object
	// 	   f must look like :
	// 	   void fun(const Type& a);
	// 	   where Type is type of the collection; const & not mandatory
	// last element pointed by this iterator is NOT part of the range
	// works well as coll.end() is not an element of array  .., coll.end()) - coll.end() is first one outside of the range of the collection

	cout << "\n\nIteration using for_each:" << endl;
	for_each (coll.begin(), coll.end(), [](int item) {cout << item << ", ";});

	// no context needed (only working with element in collection; second is parameter that needs to match what is required; so int item
	
	// not all collections support the overload of [] so cannot always use above; list for example does not overload []
	// manual iteration over collection

	cout << "\n\nIteration using manual loop and iterators:" << endl;
	// need to create iterator first:
	std::vector<int>::iterator iter;

	// we don't use < or > with iterators as they are not indexes; like a pointer pointing to some element of the collection
	// collection could be stored contigously or randomly
	// iterator overloads the ++ operator with symantic 'move to the next element in the collection'
	// so read start at first element, keep going unti you hit the first element outside the collection

	for (iter = coll.begin(); iter != coll.end(); ++iter)
		cout << *iter << ", ";

	// it is a custom object, it is something that points to an element in collection so need to dereference

	// Iterators
	// not all the same, above we used iterator for vector. could use iterator for list, array, etc
	// https://en.cppreference.com/w/cpp/iterator

	// shows what we can do with iterators

	// to iterator over a portion of array
	cout << "\n\nIterating over a portion of array" << endl;
	for (iter = ++(coll.begin()); iter != --(--(coll.end())); ++iter)
		cout << *iter << ", ";


	cout << "\n\nIterating over a portion of array using different method" << endl;
	for (iter = coll.begin() +1u; iter != coll.end() -2u; ++iter)
		cout << *iter << ", ";

	cout << "\n\nReturning list of only even numbers from original list" << endl;

	// creating another collection from previous collection
	// for diversity going to make a new list of elements from vector that are even
	// #include <list>
	
	// copy_if copies elements if certain condition is met [find_if just finds first element to satisfy condition]
	
	//std::copy_if(coll.begin(), coll.end(), evenNum.begin(), [](int item) {return item % 2 == 0;});
	// issue with above code is that evenNum.begin() cannot be used as evenNum has no elements yet (is empty)
	// can use back insertion iterator or can caount first how many elements match my condition then preallocate the list then copy elements into preallocated list

	// returns true if param is even numbers
	auto isEven = [](int item) {return item % 2 == 0;};

	// counts how many elements match condition
	auto cnt = count_if(coll.begin(), coll.end(), isEven);	

	// preallocates a list of cnt elements
	std::list<int> evenNum(cnt);

	// copy into the list the even elements from the collection
	std::copy_if(coll.begin(), coll.end(), evenNum.begin(), isEven);

	// to make it easier implemented a lambda expression for print
	auto print = [](int item) {cout << item << ", "; };

	// print to screen all copied elements
	for_each(evenNum.begin(), evenNum.end(), print);


	cout << "\n\nReturning average of elements from original list" << endl;

	// std::accumulate
	// #include <numeric>
	// https://en.cppreference.com/w/cpp/algorithm/accumulate
	// needs a range, and an initial value

	auto sum = std::accumulate(coll.begin(), coll.end(), 0.0);	// used double to avoid rounding with average-will add intergers fine but will lose information on avg calculation
	// here it is a collection of integers, so no custom logic needed for '+' operation

	if (coll.size() > 0)
	{
		auto avg = sum / coll.size();
		cout << "Average of initial collection is : " << avg;
	}
	

	// sorting the array
	// https://en.cppreference.com/w/cpp/algorithm/sort
	// here need an iterator that can move at random positions (can jump)

	cout << "\n\nReturning (ascending) sorted elements from original list" << endl;
	std::sort(coll.begin(), coll.end());
	for_each(coll.begin(), coll.end(), print);

	// by default using < operator to sort
	cout << "\n\nReturning (descending) sorted elements from original list" << endl;
	std::sort(coll.begin(), coll.end(), [](int a, int b) {return a > b;});
	for_each(coll.begin(), coll.end(), print);


	cout << "\n\nReference Wrappers\n";
	// Reference wrapper
	// #include <functional>
	
	// allows us to create a reference, or things that look like a reference, 
	double val = 1.2;
	std::reference_wrapper<double> refW(val);
	// both reference refW and val act as a name for same object
	cout << val << " <-> " << refW << endl;

	val = 3.4;
	cout << val << " <-> " << refW << endl;
	// refW also changes as it references the same val

	// this is equvialent (in terms of functionality) to:
	double& refD = val;

	// reference wrapper is useful as sometimes c++ language forbids creation of references or use of references
	// for example with vector
	//std::vector<double&> vDR;
	// this would give a compliation error
	// C++ does not allow collection of references [arrays, vectors, staticaly/dynamically allocated array of references]
	val = 1.0;
	std::vector<std::reference_wrapper<double>> vRW;
	vRW.push_back(val);

	cout << val << " <-> " << vRW[0] << endl;
	val = 2.0;
	cout << val << " <-> " << vRW[0] << endl;
	// acts like I have a reference in the vector

	// you can create a reference wrapper by calling the function:
	auto rw = std::ref(val);		// std::ref creates a reference wrapper


	///////////////////
	// Bound functions
	// created function foo defined at start of file
	// if you find you constantly call that function with a certain value you can bind it

	auto boundFoo = std::bind(foo, 42);
	boundFoo();
}