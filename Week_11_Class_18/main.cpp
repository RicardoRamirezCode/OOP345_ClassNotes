#include <iostream>
#include <string>

using namespace std;

/*
class Student
{
	std::string m_name;
public:
	Student(const char* name) : m_name{ name }
	{
		cout << "Student::Student(const char*)\n";
	}

	~Student()
	{
		cout << "Student::~Student()\n";
	}
	void display() const
	{
		cout << "Student: " << m_name << "\n";
	}
};

class Faculty
{
	std::string m_name;
public:
	Faculty(const char* name) : m_name{ name }
	{
		cout << "Faculty::Faculty(const char*)\n";
	}

	~Faculty()
	{
		cout << "Faculty::~Faculty()\n";
	}
	void display() const
	{
		cout << "Faculty: " << m_name << "\n";
	}
};

class Tutor : public Student, public Faculty
{
public:
	Tutor(const char* name) : Student(name), Faculty(name)
	{
		cout << "Tutor::Tutor(const char*)\n";
	}

	~Tutor()
	{
		cout << "Tutor::~Tutor()\n";
	}
};

int main()
{
	// multiple inheritance
	Tutor t("John");
	
	calls constructors in order of initializtion list and destructors are called in reverse order
	Student::Student(const char*)
	Faculty::Faculty(const char*)
	Tutor::Tutor(const char*)
	Tutor::~Tutor()
	Faculty::~Faculty()
	Student::~Student()
	

	// display is available to class Tutor through inheritance; issue is each class it inherits from has a display function
	// can use scope resolution
	t.Student::display();

	// Tutor inherits from faculty and student; if we accidently have in initialization list of Tutor two different names
	// now issue is desynchronized data; we passed two different names
	// Tutor(const char* name) : Student("John"), Faculty("Sara")
}
*/

// can take common from both classes to make a new class
class Person
{
	std::string m_name;

public:
	Person(const char* name) : m_name{ name }
	{
		cout << "Person::Person(const char*)\n";
	}

	~Person()
	{
		cout << "Person::~Person()\n";
	}

	void display() const
	{
		cout << "Person: " << m_name << "\n";
	}
};

class Student : virtual public Person
{	
public:
	Student(const char* name) : Person(name)
	{
		cout << "Student::Student(const char*)\n";
	}

	~Student()
	{
		cout << "Student::~Student()\n";
	}
};

class Faculty : virtual public Person
{	
public:
	Faculty(const char* name) : Person(name)
	{
		cout << "Faculty::Faculty(const char*)\n";
	}

	~Faculty()
	{
		cout << "Faculty::~Faculty()\n";
	}
};

class Tutor : public Student, public Faculty
{
public:
	Tutor(const char* name) : Person(name), Student(name), Faculty(name)
	{
		cout << "Tutor::Tutor(const char*)\n";
	}

	~Tutor()
	{
		cout << "Tutor::~Tutor()\n";
	}
};

int main()
{
	Tutor t("John");
	// display only exists in class Person; yet can't have:
	//t.display();
	// reason is we have two subobjects of Person
	/*
		Person::Person(const char*)
		Student::Student(const char*)
		Person::Person(const char*)
		Faculty::Faculty(const char*)
		Tutor::Tutor(const char*)
		Tutor::~Tutor()
		Faculty::~Faculty()
		Person::~Person()
		Student::~Student()
		Person::~Person()
	
		when creating Tutor need to build first subobject which is Student; and that requires we build subobject Person

					P
				  /  \
				 F    S
				  \  /
				    T
					Diamond Problem

		C++11 added a solution, by adding virtual inheritance
		class is not virtual, inheritance is virtual
		Student will not build it's own subobject of type Person
		Faculty will not build it's own subobject of type Person
		class tutor will only have one subobject Person and NEED TO SPECIFY in initializtion list of Tutor now for Person

		TUTOR WILL CREATE ITS OWN SUBOBJECT PERSON THAT WILL BE USED BY BOTH STUDENT AND FACULTY!!!
		Tutor(const char* name) : Person(name), Student("John"), Faculty("Sara")
		so here above even if we passed two different names to the constructors of Student and Faculty it wouldn't matter

	*/
	t.display();
}

