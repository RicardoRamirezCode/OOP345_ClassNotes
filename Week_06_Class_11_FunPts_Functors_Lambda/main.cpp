#include <iostream>
using namespace std;

////////////////
// Pointer to Function
bool asc(int a, int b)
{
	return a > b;
}

bool desc(int a, int b)
{
	return a < b;
}

///////////
// Functors

enum class Order
{
	ASC,DESC
};

class Comparator
{

public:
	Order m_order = Order::ASC;				// just setting default to asc
	bool operator()(int a, int b)
	{		
		if (m_order == Order::ASC)			// now we can store a state in this object
			return a > b;
		else
			return a < b;
	}	
};

// user can pass either pointer to function, passing for T a comparator or use a lambda
template <typename T>
void bubbleSort(int* arr, size_t n, T cmp)
{
	for (auto i = 0u; i < n - 1; ++i)
	{
		for (auto j = i + 1; j < n; ++j)
		{
			if (cmp(arr[i], arr[j]))				// T must be able to support () and pass two params and return something that can be converted to bool
			{
				auto tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

// Display function
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

int main()
{
	bool (*cmpF)(int, int);			// pointer to function method
	cmpF = nullptr;					// could do in above line

	Comparator cmpFunctor;			// Functor method

	// take user input
	char choice = '\0';
	cout << "Asc/Desc?";
	cin >> choice;


	if (choice == 'a')
	{
		cmpF = asc;								// set function pointer to asc
		cmpFunctor.m_order = Order::ASC;		// set functor state
	}
	else
	{
		cmpF = desc;							// set function pointer to desc
		cmpFunctor.m_order = Order::DESC;		// set functor state
	}


	int arr[]{ 4, 6, 98, 1, -5, 5, 78 };

	
	bubbleSort(arr, 7, cmpF);
	display(arr, 7);
	bubbleSort(arr, 7, cmpFunctor);
	display(arr, 7);
	bubbleSort(arr, 7, [](int a, int b) {return a > b;});		// passing lambda here which I can change as writer of code as I need
	display(arr, 7);											// no user input in this particular case




}