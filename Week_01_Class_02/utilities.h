#ifndef UTILITIES_H
#define UTILITIES_H

namespace foo
{
	void sayHello();


	//int g_value;
	// this is still a definition; however you are redefining it
	// want to declare it without defining it
	// definining means the allocator will define memory for it
	extern int g_value;


	// Lesson Part Two

	struct Foo
	{
		const int m_val;
	};

}



#endif // !UTILITIES_H
