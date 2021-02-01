#include <iostream>
#include <iomanip>
#include <typeinfo>

using namespace std;

template<typename T>
class Foo
{
	T m_value{};			// will initialize to 0 if integer, if a pointer to nullptr; if a custom type then will initialize with default constructor
	static size_t m_cnt;
public:
	Foo();
	void display()const;
	static void showCounter();		// is a querry but don't use const
									// const at the end is applied to "*this"; but static functions do not have "*this"
};

template <typename T>
Foo<T>::Foo()
{
	m_cnt++;
}

template<typename T>
void Foo<T>::display()const
{
	cout << typeid(*this).name() << " has [" << Foo<T>::m_cnt << "] instances.\n";
}

template <typename T>
size_t Foo<T>::m_cnt = 0;

//template <typename T>
//void Foo<T>::showCounter()
//{
//	cout << "???" << " has [" << Foo<T>::m_cnt << "] instances.\n";	// wouldn't work with *this
//}

///////////////////////////////////////////////
// Specialization
template<>
size_t Foo<double>::m_cnt = 100u;		// here I'm not using T, some unknown type, I provide a specific type double
										// Visual Studio may complain because it is trying to help but is confused; but compiler won't be confused
										// however putting this line 43 after constructer below may cause an issue

// now to specialize for the constructor
template<>
Foo<double>::Foo()
{
	Foo<double>::m_cnt--;
}

int main()
{
	Foo<short> f_s[5];		// compiler can't figure out what the type is for when we instanciate instance aFoo so we have to specify
	f_s[0].display();

	Foo<long> f_l;
	f_l.display();

	// note these two instances are not compatible; so can't do assignment between the two
	// even if the same class as the base class becasue the template parameters are different the types are different
	// type Foo<short> and type Foo<long>


	/////////////////////////////
	// Specializations
	// means offer an exception, on a different behaviour, for a certain type

	// for example, for doubles should be specialized, counter should start at 100 and decrement instead of other m_cnt behaviour

	Foo<double> f_d[7];
	f_d[0].display();

}