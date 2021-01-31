#include <iostream>
#include <string>

using namespace std;

/*
* 
* Method here does not allow user to mistype a parameter
void paint(string color)
{
	if (color == "red")
	{
		cout << "House is painted [" << color << "].\n";
	}
	else if (color == "green")
	{
		cout << "House is painted [" << color << "].\n";
	}
	else
	{
		cout << "Not available!\n";
	}

}

*/

// enumerations are actually intergers in this type
// each attribute will have an value
// can change the default value by assigning it here

// so enumerations are integers in disguse
enum class Color
{
	Red,		// 0
	Blue,		// 1
};

enum class WebColor
{
	Pink,
	Green,
	Magenta,
	Red,
	Blue,
};

// adding above enum created ambiguity;
// changed it to enum class


void paint(Color color)
{
	switch (color)
	{
	case Color::Red:
		cout << "I like red!\n";
		break;

	case Color::Blue:
		cout << "House is painted with [blue].\n";
		break;

	default:
		cout << "Not available.\n";
		break;

	}

}


int main()
{
	paint(Color::Red);
	paint(Color::Blue);
}