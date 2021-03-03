#include <iostream>

using namespace std;

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
		cout << "Operator () called\n";
		if (m_order == Order::ASC)			// now we can store a state in this object
			return a > b;
		else
			return a < b;
	}
	// want this operator to match the call like the previous (asc/dec) so it should return a bool
};
// if I have overloaded this operator then this class is a functor ( a function class)

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

// this works with functor
void bubbleSortFunctor(int* arr, size_t n, Comparator cmp)
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

// user can pass either pointer to function or passing for T a comparator
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



int main()
{
	// create an object/class and instanciate that class
	// an instance of that class will be used like a function

	Comparator cmpFunctor;

	//cout << "Should I switch?" << cmpFunctor(12, 9) << endl;

	// benefit of a class (and this Functor) is I can store a state; can inherit, have member values and virtual functions, template, etc
	// only thing that makes it functor is the overloading of the operator ()


	char choice = '\0';
	cout << "Asc/Desc?";
	cin >> choice;

	if (choice == 'a')
	{
		cmpFunctor.m_order = Order::ASC;			// this sets object to be asscending
	}
	else
	{
		cmpFunctor.m_order = Order::DESC;
	}

	int arr[]{ 4, 6, 98, 1, -5, 5, 78 };

	bubbleSort(arr, 7, cmpFunctor);
	display(arr, 7);

	// this bubblesort is the same code as previous, so instead we can use template


}