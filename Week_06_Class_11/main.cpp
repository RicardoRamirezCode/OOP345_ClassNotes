#include <iostream>
#include <typeinfo>

using namespace std;

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
	// function object

	// pointer to function

	// lambda expression
	// [] where we capture the context; variables that are local and available here (means on line where we are writing this
	//	that I want to use inside lambda expression
	//	then do you want to capture read only (by value) or by reference?
	//	if you want everything by value you just insert "="
	//	if all by reference then "&"
	//	or one thing by value then we put the name of the variable (with & if by reference)

	// in () specify what are the parameters of our annoymous function

	// next need to specify the return type (unless compiler can determine then not needed); here by trailing return type

	// need to capture lambda expression in some variable so we can use it

	// {} for the implementation of the lambda

	string str = "Hello";
	auto cmpL = [=](int a, int b) ->bool
	{
		cout << "A: " << a << " B: " << b << " -- " << str << endl;
		// str += " World";			// would give an error as we passed by value not reference
		return true;
	};

	cmpL(4, 5);

	// note [=] captures (by value) variables avaliable at moment of creation (local scope) of lambda AND global variables (obviously already have access)
	// [&] captures by reference
	// [&str]	captures str only by reference
	// [&str, cmpF]	// captures str by reference and cmpF by value
	// [=, &str]	// all by value, just one by reference

	////////////////////
	// Type of Lambda
	cout << typeid(cmpL).name() << endl;
	// this results in showing lambda expression is a class (it is actually an instance of a  functor)
	// compiler will see it and generate a class, but name is randomly generated
	// so cmpL is actually an instance of a functor (named lambda..... as above line will show what random name the class was given)

	////////////////
	// Purpose of lambda is it allows the following:
	int arr[]{ 4, 6, 98, 1, -5, 5, 78 };

	bubbleSort(arr, 7, [](int a, int b) {return a < b;});
	display(arr, 7);

	// so it allows you to quickly create one and pass it as a parameter to a function
}