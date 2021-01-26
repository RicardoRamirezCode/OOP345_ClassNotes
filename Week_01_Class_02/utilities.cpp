#include <iostream>
#include "utilities.h"

using namespace std;

namespace foo
{

	int g_value = 10;



	void sayHello()
	{
		// static keyword will make this variable exist in memory for the duration of the program
		// it is still local to this function, only this function knows about the variable
		// so in essence it is like a global value as it exists the duration of the program but is local as well
		static int cnt = 0;
		cnt++;
		cout << cnt << " : Hello: [" << g_value << "]\n";
	}


	// with static keyword this function will have internal linking
	// linker will not link it across modules
	// so even if you declared the prototype in main you can not use it there
	static void sayBye()
	{
		cout << "Goodbye\n";
	}

	

}

