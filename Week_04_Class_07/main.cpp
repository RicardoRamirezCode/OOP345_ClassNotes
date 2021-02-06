#include <iostream>

using namespace std;

template <typename T>
void print(T val)
{
	val++;				// must support ++ postfix
	cout << val;		// must be insertable (<< must be overloaded for type T)
	val.setData(54);	// must have a member function called setData with an integer as param
}

class Pair_int_string
{
	int val;
	string key;
};

class Pair_string_string
{
	string val;
	string key;
};

// specialization for Pair
// an exception for implementation on a specific template type
template <>
void print<Pair_int_string>(Pair_int_string val)
{

}

int main()
{
	



}