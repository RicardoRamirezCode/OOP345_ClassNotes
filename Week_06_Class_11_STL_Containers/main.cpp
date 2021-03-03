#include <iostream>
#include <array>
#include <vector>
#include <forward_list>
#include <list>

using namespace std;

void display(std::array<int, 5> arr)
{
	for (auto i = 0u; i < arr.size(); ++i)
		cout << arr[i];
}

int main()
{
	// Contaniners in C++
	// in programs, most of the time, we are manipulating a collection of data;
	// of objects of a certain type and we need to do something with those (sort, search into them, modify, filter them (subset), etc)
	
	// Types of collections (used thusfar):

	// arrays
	// advantage: fast retrieval of the element at random index 'i'
	//					one big block of memory compact, no gaps, and we can access those elements fast
	// so drawbacks are you can not resize array (or if you use dynamically allocated arrays, you can do work in background that mimics but it is expensive 
	//					and is not really resizing the original array)
	//		you can not use assignment to copy contents from one array to another
	//		when you pass an array as parameter you have to pass its size
	
	
	// drawback: is it can not be resized OR very expensive to resize
	//				we can avoid this a bit by using dynamically allocate arrays, and from a client perspective we have resized but in reality
	//				we have just created a new array and copied over the elements

	int arr_1[5]{ 5,8,32,9,1 };

	int arr_2[5];

	// drawback: can not, for example using above c-style arrays:
	// arr_2 = arr_1;
	// in this case we would have to iterate to copy contents of array 1 in to array 2
	// this is another disadvantage of c-style arrays

	// drawback: no method to know the size of the array
	//				if we have a function and pass to it a pointer to an array, we have to pass its size if the function plans to iterate over the array
	/*void display(int arr[])
	{
		for (auto i = 0; i < ??? ; i ++)
	}*/
	
	//////////////////////////////////
	// STL: Standard Template Library
	
	//////////
	// std:: array - statically allocated array - it goes on the stack
	// std array will be a templated class that will accept a certain paramter, the type of the array, and size
	std::array<int, 5> arrSTL_1{};
	std::array<int, 5> arrSTL_2;

	// passing arrays(functions) and easy assignment are handled by the class std::array
	// class std::array will behind the scenes have a statically allocated array of specified type, of specified size
	// will still have same advantage (fast retrieval) /disadvantage (of can not resize)
	// but will able to easily assign and pass int function without dealing with second parameter

	// can assign them
	arrSTL_2 = arrSTL_1;

	// can pass only array and not size
	// example on line 6
	

	///////
	// Vector
	// dynamically allocated array - goes on the heap (instance of type vector will be on stack; but maintain a dymaically allocated array which is on the heap)
	// main difference versus previous is we can resize (but will be very expensive)
	// use vector if sometimes we need to resize but most of the time we just need to look at the collection, iterate, etc.
	std::vector<int> coll;
	
	// add elements using push
	coll.push_back(5);
	coll.push_back(8);
	coll.push_back(32);
	coll.push_back(9);
	coll.push_back(1);

	cout << "\n\nVector\n";

	for (auto i = 0u; i < coll.size(); ++i)
		cout << coll[i] << ", ";
	cout << endl;

	// for every item (and am going to capture by reference so we don't make copies) in the collection -> print it
	for (auto& item : coll)
		cout << item << ", ";
	cout << endl;


	////////////////
	// (linked) list

	// advantage: very fast to resize, insert or remove an element
	// disadvantage: slow in asccessing an element at some random index

	// with std:: array and vector 
	// compiler allocates some section of memory, has a pointer (ptr) pointing to start of that section
	// then when we use ptr[i]
	// compiler reads it as (ptr + i) which it then dereferences as:
	// * (ptr + i)
	// this is why access is very fast to a certain index i

	// list organize data differently; has bunch of blocks of memory called nodes
	// nodes have at least two fields:
	// one field will store the data
	// second field will store the address of the next node on the list (so a pointer to another node)
	// last element (called the tail) will point to null
	// first element will be called the head of the list

	// note nodes are not consecutive in memory
	// can not easily (by calucating ptr+i as in previous example) find what is the element at index i
	// to do so will have to iterate; start from first element (head) follow pointers (by counting how many jumps)

	// resizing is fast
	// just need to update a few pointers to add an element
	// just have previous node point to new element and new element point to next element
	// faster at end nodes as you only need to modify a single pointer

	// this is an example of a single-linked list, you can travel in one direction
	// can have a double-linked list and travel in other direction (by storing the pointer to the previous element as well)


	// single-linked list
	// move only from head to tail
	// #include <forward_list>

	// double-linked list
	// #include <list>

	cout << "\n\nLists\n";

	std::list<int> coll2;

	coll2.push_back(5);
	coll2.push_back(8);
	coll2.push_back(32);
	coll2.push_back(9);
	coll2.push_back(1);

	/*for (auto i = 0; i < coll2.size(); ++i)
		cout << coll2[i] << ", ";
	cout << endl;*/
	// above wil not work as we can not overload [] as we would have to traverse the list and it's inefficient and designers of class excluded that

	
	for (auto& item : coll2)
		cout << item << ", ";
	cout << endl;

	// [] not implemented so can not iterate using index i
	// we use different method, called iterators



	std::list<int>::iterator it = coll2.begin();
	// think of as a pointer that points to first element of list

	// as long as iterator (it) is not at end of of list; increment iterator (ie go to next element)
	// NOTE .end() gives you an iterator outside of the range
	// so coll2.end() does not belong to the collection
	
	for (; it != coll2.end(); ++it)
		cout << *it << ", ";					// if pointer points to element,we get actual element by dereferencing; type of *it is int
	cout << endl;

	// above requires us to define iterator based on type <int> and if we need to change we have to update;
	// alternative is using the following:

	for (auto it = coll2.begin(); it != coll2.end(); ++it)
		cout << *it << ", ";
	cout << endl;
	// here we make the iterator and compiler will infer its type

	// this allows us to change from std::list<int> coll2 to std::vector<int> without having to update the logic


	// adding element to middle
	cout << "\nAdding an element\n";
	auto it2 = coll2.begin();
	++(++it2);
	coll2.insert(it2, -87);		// insert after first two elements, add -87

	for (auto it = coll2.begin(); it != coll2.end(); ++it)
		cout << *it << ", ";
	cout << endl;

	// remove an element
	cout << "\Removing an element\n";
	coll2.erase(it2);		// erasing element pointed by the iterator

	for (auto it = coll2.begin(); it != coll2.end(); ++it)
		cout << *it << ", ";
	cout << endl;


	//////////////////////////
	// RECAP: Collections in STL
	// std::vector 			dynamic memory
	// std::array			static memory
	// std::list			double linked list
	// std::forward_list	single linked list
	
}