#include <iostream>

using namespace std;

// will make a function to print to screen, will be called multiple times
// will pass array as a pointer
void display(int* arr, size_t size)
{
	// will assume client passed a valid array
	cout << arr[0];
	for (auto i = 1u; i < size; i++)
	{
		cout << ", " << arr[i];
	}
	cout << endl;
}


bool asc(int a, int b)
{
	return a > b;
}

bool desc(int a, int b)
{
	return a < b;
}


void bubbleSort(int* arr, size_t n)
{
	for (auto i = 0u; i < n - 1; ++i)
	{
		for (auto j = i + 1; j < n; ++j)
		{
			if (asc(arr[i], arr[j]))			// logic of 'should i swith them?'
			{
				auto tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}


void bubbleSortUpdated(int* arr, size_t n, bool (*cmp)(int, int))
{
	for (auto i = 0u; i < n - 1; ++i)
	{
		for (auto j = i + 1; j < n; ++j)
		{
			if (cmp(arr[i], arr[j]))
			{
				auto tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}
int main()
{
	// pointer to a function (notice both asc and desc from before are similar)
	bool (*cmpF)(int, int);		// pointer to a function that returns bool and recieves two params

	// returns bool, (*) indicates its pointer to function called cmp; and should receive an int and another int as param
	// if we write:
	// bool *cmp(int, int); compiler will read this as a function prototype (declaration of function)
	// cmp is a variable that is a pointer to a function that has return type bool and accepts two param of type int
	cmpF = nullptr;	// cmp if a variable that stores the address of a function but can use like a function later

	char choice = '\0';
	cout << "Asc/Desc?: ";
	cin >> choice;

	if (choice == 'a')
		cmpF = asc;
	else
		cmpF = desc;

	// so we are getting the addresses of these two functions and assigning them to cmpF

	int arr[]{ 4, 6, 98, 1, -5, 5, 78 };

	// have an array, a collection of values and want to sort them

	cout << "Original Array:\n";
	display(arr, sizeof(arr) / sizeof(arr[0]));

	cout << "Updated Array\n";
	bubbleSort(arr, sizeof(arr) / sizeof(arr[0]));
	display(arr, sizeof(arr) / sizeof(arr[0]));
	
	// issue is if I want to change from ascending to descending we need to keep changing the body of the function and recompiling
	// wrote function asc/desc to answer if we should switch or not



	//////////////////////////////
	// updated bubble sort
	cout << "Array Sorted by User Choice:\n";
	bubbleSortUpdated(arr, sizeof(arr) / sizeof(arr[0]), cmpF);
	display(arr, sizeof(arr) / sizeof(arr[0]));

	// this type of function we pass as param to other functions are call back functions
	// main is calling bubblesort but the bubblesort through a callback (able to callback the client) to excute some other function

	// all above is c (other than bool)
}