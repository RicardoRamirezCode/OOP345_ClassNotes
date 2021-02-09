#include <iostream>

using namespace std;

int main()
{
	// classes and their relations
	// strength of relation comes from how easy it is to de-couple them (ie how easy it from those to classes to make independent classes)
	// ie classes who don't know about each other and don't need anything from the other

	// inheritance - 'is a' (is-kind-of)
	// composition :	(complete) ownership (one instance owns another instance)
	//					life management (one instance is responsible to create/destroy the other instance)
	// aggreation	:	'has-a' relationship
	//					ownership (ownership is not exclusive - one instance is not responsible for life management)
	//					the object will be created somewhere outside of the aggregator and will be passed to the aggregator
	//					so child object can exist independent of parent and vice versa but still have ownership
	//					example would be a car and it's wheels. 
	//					car will not create the wheels, car has ownership of wheels and can use them however both can exists indepently
	// association:		
	//					an example is when we do a cout << "Hello;
	//					cout is an object of type ostream; if your class using cout to print something to the screen you have an associate 
	//					between ostream and your class but if you don't have access to cout your class still can created still has it data
	//					they exist independent from each other and each type is complete from each other
	/*
	college
	departments
	professors
	TTC
	Here college needs departments and departments can't exist without a college, so each needs the other; not complete without the other. 
	So it's composition.
	With departments with and professors; professors can exist independent of the college. College is not complete without professors, it
	needs professors but the college is not responsible to create the professors.
	So relation is aggregation. No lifemangement but there is ownership.
	Professors do not own the TTC, and the TTC does not own the professors. No ownership; but can exists without the other.

	*/


	class Foo
	{

	};

	class Bar
	{
		Foo aFoo;		// composition
						// everytime when we create an instance of type Bar will have to contain an instance of type Foo
						// the instance of type bar cannot exist without an instance of type Foo
						// so we have complete ownership
						// Bar will responsible to create the instance of Foo and delete it when it goes out of scope
						// Foo will not exist without a Bar

		Foo* pFoo;		// could be composition; depends on how do we create this object
						// if the constructor in Bar allocates memory for pFoo (does a new inside of Bar constructor for example)
						// and destructor is doing a delete at the end
						// then we do have composition
						// if bar is receiving this object created somewhere else then it's not doing life management; aggregation

		Foo& rFoo;		// composition is not possible; as when we create an instance of type Bar I need an instance of type Foo and
						// that instance needs to be created somewhere outside of the class
						// ie that reference has to already exist when I create an instance of Bar	
						// so no composition if we have a reference
						// aggregation; we have ownership but no life management

	};

	//////////////////////////////////////
	// Expressions
	// a combination of operands and operators; way we build these expressions and combine these operands and operators allow us to create
	// bigger and bigger expressions

	
	// There are two categories/characteristics to be concerned with:
	// has idenity - exists in ram (has an address)
	//				identity of any expression or variable is given by it's address
	// is it movable - means if I take away the content of that entity, of that value/object, and put it somewhere else; will that program still
	//					work or will that instance still need its content
	//				- so if it's safe to steal it's content then we say it's movable; if not safe to take it's content because an instance
	//					still needs its content then it's not movable
	//				- so question to ask is does it still need it's content:
	// So we classify an expression (or variable) into these two categories: identity, movable

	/*
	So there are four possible combinations of these two categories:
	First:	has identity but not movable
	Second: has identity is movable
	Third:	does not have identity and is movable
	Fourth:	no identity and not movable

	Fourth combination is actually not possible; so only three possible combinations
	These three combinations in order correspond to the boxes on the lowest part of the following tree:


						+----------------------------+                        
						|                            |                        
						|                            |                        
						|    Expression              |                        
						|                            |                        
						+----------------------------+                        
							/---               --\                             
						---                      ---                          
	+------------------------+          +------------------------+          
	|                        |          |                        |          
	|         glvalue        |          |    rvalue              |          
	|                        |          |                        |          
	+------------------------+          +------------------------+          
	----        ----\                /-----          --\             
	---/                 ----      ------                   --           
	+--------------+            +----------------+          +-------------------+
	|              |            |                |          |                   |
	|   lvalue     |            |    xvalue      |          |    prvalue        |
	|              |            |                |          |                   |
	+--------------+            +----------------+          +-------------------+


	So has identity is a glvalue (generalized lvalue)
	So is movable is rValue.

	lvalue:		left hand value
	xvalue:		expiring value
	prvalue:	pure rValue

	xvalues are those objects that are about to expire; they go out of scope right after the expression where they appear, they are
			at the end of their lives
			in which case if take the content of those objects and put them into some other object we don't break anything (as object
			is about to die it doesn't need it's contents anymore)
	lValue	thing that appears on left hand side of assignment operator. if we take away its content then we might be leaving an object
				in an invalid state, might be breaking the object, as we may still need it in future evaluations
	prvalues	values that do not exist in memory such as the number 10, literals
				so if I take away the content of a pure value no issues, they don't have an identity that don't exists and ram (and have an 
				address) and it's safe to move the content if possible

	*/

	int x = 5;		// a has memory address, but not safe to move its content - because I might use it; so it's an lvalue
					// 5 doesn't have a memory address, so only option is a prvalue
					// 5 is also called a literal and literals do not have identity

	/*
	class Foo
	{

	};

	Foo bar()
	{
		Foo aFoo;
		// ...
		return aFoo;		// here it has identity (as it has an address); but after next line it is finished; so it is movable
							// so it is an xvalue
	}
	*/
	
	x = 12;		// here left operand needs to be a glvalue; if it didn't have memory the operation wouldn't make sense: we would be storing 12 in what?

	x++;		// requirements of postfix ++ is met

	// however a++ returns 'something'
	//(x++)++;	// not valid because result of (a++) is in the wrong category; postfix ++ returns a prvalue (doesn't have memory or identity) - main reason is
				// it doesn't have identity

	++(++x);	// is legal as prefix ++ returns an lvalue (it has an address/identity)


	int b = 7 + 4 * -3 / 2 - 2;
		// ((7 + ((4 * (-3)) / 2)) - 2)		// first was (-3) last one applied is = (assignment)

	// 1:00

	short a[5]{5, 8, 3, 2, 7};

	short* ptr = &a[2];

	for (auto i = 0; i < 3; ++i)			// 3 is picked as we know the size of the array of a
	{
		cout << ptr[i] << ", ";
	}
	cout << endl;

	for (auto i = 0; i < 3; ++i)		// note we could use a larger value instead of 3; it will go out of bounds
	{									// will be undefined behaviour (may crash, or wrong data)
		cout << ptr[-i] << ", ";		// still on the programmer to know when to stop
	}
	cout << endl;

	short c[]{ 0, 5, 8, 3, 2, 7 };
	short* ptrC = c;

	for (int i = 0; i < 6; ++ptrC, ++i)
	{
		cout << *ptrC << ", ";				// ptr stores the address of c; but we are dereferecing so we are printing the content at that address
	}
	cout << endl;
	// so pointer became an itereator; will move from element to element



	// Size of operator
	
	//evaluated at compile time; so can't be used on dynamic memory, pointers, etc
	// if used on a pointer will just return 4 bytes
	
	cout << "Size of ptrC: " << sizeof(ptrC) << endl;		// returns memory size in bytes of the pointer (4)
	cout << "Size of c: " << sizeof(c) << endl;			// type of c is short[6]; so a uses 6 shorts
														// short[6] is 6 x 2;
	// size of array
	cout << "Size of Array: " << sizeof(c) / sizeof(c[0]) << endl;

	// can use this sizeof(c) / sizeof(c[0]) as condition in iterator

	/////////////////////////////////
	// Conversions

	int val = 9;
	short sVal;
	//sVal = (short)val;		//c style conversion, could be dangersous due to data loss as in this example short stores less than our int

	// static cast - a templated operator
	sVal = static_cast<short>(val);					// used between compatible types but not on the same hiearchy			
	dynamic_cast<Base*>(obj);						// used in a hierarchy; will generate an error if not possible ie if not on same hierarchy or if the result
													// would be some sibling to the destination type (Base*)
	reinterpret_cast<dest_type>(obj);				// doesn't check compt between types; simply reinterprets the bytes;
													// only check it does is that the same number of bytes used in obj should be used in dest_type
	const_cast<dest_type>(obj);						// dest_type should be exactly the same as the object but without const
	
	/*
	static_cast			compatible type
	dynamic_cast		types on the same hierarchy
	reinterpret_cast	reinterprets the bytes as another type
	const_cast			removes const
	*/

}