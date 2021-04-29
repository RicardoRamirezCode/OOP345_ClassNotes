#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

int main()
{
	// Bit Operations
	// all information stored on computers are essentially a long string of 0s and 1s
	// and we associate semantics to those strings
	// we take one byte (8 bits- a string of 8 bits) and interpret as a character for example

	// packing of information
	// using a boolean to keep track of whether a 'switch' is on or off is inefficient (in terms of space)
	// we can use each bit instead to keep track of the state of the 'switch' (on/off)

	// https://code.visualstudio.com/blogs/2017/02/08/syntax-highlighting-optimizations
	// example where encoding information on bits decreased the necessary size of the tokens

	// all examples of packing a lot of data/information on as small memory as possible

	// working on bits, strip aways any semantic from type itself (don't need char, float, int, etc)
	// if we need 32 bits we can choose an int, if we just need less than 8 we can use char as our underlying type

	// here we will use short instead of char (as if we use char we will see characters displayed to screen
	// instead of numbers when we use cout

	// variable that will store the bits
	unsigned short bits = 108u;

	// let's display the bits, using:
	// #include <bitset>	// will help extract bits so we don't have to do a loop ourselves

	// will use to show how number above is represented on machine using 0s and 1s
	// bitset is a templated class, with a number representing how many numbers will be shown on the screen
	cout << "   " << setw(10) << bits << " - " << bitset<16>(bits) << "\n";

	// bit operations available in c++:
	// 
	// negation (bitwise not)
	// flips all the bits (1s become 0s, 0s become 1s)
	cout << "Bitwise Not - Negation\n";
	cout << " ~ " << setw(10) << ~bits << " - " << bitset<16>(~bits) << "\n";

	// note ~bits became -109 according to the representation on my machine
	// issue with negative numbers is standard does not describe how negative numbers are stored
	// always will get the same 'bit' but how it is interpreted or represented in base ten will depend on the machine
	// when working with bits it better to work with unsigned to guarantee a certain representation
	// as unsigned is specificed in the standard how it is represented but signed is not

	unsigned short mask = 209u;
	cout << "   " << setw(10) << bits << " - " << bitset<16>(bits) << "\n";
	cout << "   " << setw(10) << mask << " - " << bitset<16>(mask) << "\n";

	// bitwise and operator
	// and applied on bits (ie a 0 and 1 becomes a 0, etc)
	// so takes all positions and compares the bits
	cout << "Bitwise And Operator\n";
	cout << " & " << setw(10) << (bits & mask) << " - " << bitset<16>(bits & mask) << "\n";

	// bitwise or operator
	cout << "Bitwise Or Operator\n";
	cout << " | " << setw(10) << (bits | mask) << " - " << bitset<16>(bits | mask) << "\n";

	// bitwise xor (exclusive or)
	// if both are 1 or 0 it produces 0 as result; only produces 1 on where one operand is 0 the other 1
	cout << "Bitwise xor - exclusive or\n";
	cout << " ^ " << setw(10) << (bits ^ mask) << " - " << bitset<16>(bits ^ mask) << "\n";


	// shifting operator
	cout << "Original value:\n";
	cout << "   " << setw(10) << bits << " - " << bitset<16>(bits) << "\n";
	cout << "Shifted value\n";
	cout << ">> " << setw(10) << (bits >> 1u) << " - " << bitset<16>(bits >> 1u) << "\n";
	// moves entire string of streams some positions to the right or left
	// depending on which operator you use (right or left shifting operator)

	// here we shifted by one value and it produced a division by 2
	// so division by 4 would be 
	cout << ">> " << setw(10) << (bits >> 2u) << " - " << bitset<16>(bits >> 2u) << "\n";

	// shifting in other dirrection will give mulitplication by 2
	cout << "<< " << setw(10) << (bits << 1u) << " - " << bitset<16>(bits << 1u) << "\n";

	// checking if number is odd or even (not using mod)
	cout << (bits & 1u ? "odd" : "even") << endl;
	// here will check last bit; if last bit is 1 it is an odd number so will evaulate to true and print "odd"
	// else will be even

	// mod will use multiple cpu cycles to check while above is faster (one cpu cycle)

	/////////////////////
	// Assume you have
	// 01101100
	// and you want to switch the fifth index bit to true (leaving rest the same) to produce:
	// 01111100

	// to switch only that bit and leave the other bits the same, this is done by creating a mask
	// need to do an OR between original value and :
	// 00010000
	// as this is the position we want to SET to 1
	// need to set mask to 16u (first would be 1, then 2, then 4, then 8, then 16)
	cout << "Switching a single bit to 1\n";
	unsigned short mask2 = 16u;
	cout << "   " << setw(10) << bits << " - " << bitset<16>(bits) << "\n";
	cout << " | " << setw(10) << (bits | mask2) << " - " << bitset<16>(bits | mask2) << "\n";

	// So to look a a value of one bit you use AND
	// if you want to switch on some bits you use OR
	// if you want to flip certain bits you use XOR

}