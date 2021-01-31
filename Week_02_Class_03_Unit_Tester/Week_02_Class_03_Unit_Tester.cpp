#include "pch.h"
#include "CppUnitTest.h"
#include "../Week_02_Class_03/Book.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Week02Class03UnitTester
{
	// renamed class to something else, in this case a global function tester
	TEST_CLASS(GlobalFunctionTester)
	{
	public:
		//renamed to some tester
		TEST_METHOD(Multiply_2by2)
		{
			// now need to call multiply function, however there is no connection yet between two projects
			// need to tell unit tester project it references other project
			// select references under the tester project
			// right click on it and select 'add reference' and select other project this is testing
			// means before this can be compoliled the dependencies also have to be compiled

			// to use function that resides in another project still need to include a header with a declaration
			// could make a copy but those copies could become desynced
			// find current folder of unit tester
			// go up a level to solution folder
			// include the header (line 3)
			
			auto res = multiply(2, 2);		// going to capture the result in a variable

			Assert::AreEqual(4, res);	// this function will check if two values are equal
										// should test on the specifications

			// now the project does have access to the header so the compiler knows symbols/identifiers from other project; multiply for example
			// the linker does not have access to the function multiply (as it's in a different project)

			// don't forget to set as startup project

			// need to tell the linker in unit tester project to link to the result of the compilation project of other project
			// looking at main project file, in the debug folder, can see the .obj files (compile translation units)
			// these (object) files are the ones we have to tell the linker to link to in the unit tester

			// grab path
			// right click on unit tester project, select properties, linker/input section
			// select additional dependencies, add by editing (right click on arrow at end):
			// D:\repos\Seneca\OOP345_ClassNotes\Week_02_Class_03\Debug\*.obj

			// to run test go to test menu/ test explorer then run all

		}

		// SECOND TEST

		TEST_METHOD(Multiply_3by2)
		{
			auto res = multiply(3, 2);
			Assert::AreEqual(6, res);
		}

		// use 'debug all tests' under the test /test explorer

		// if you need to use the same thing over multiple tests
		// made new cpp file called Book type tester

	};
}
