#include "pch.h"
#include "CppUnitTest.h"
#include "../Week_02_Class_03/Book.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Week02Class03UnitTester
{	
	TEST_CLASS(BookTypeTester)
	{
		Book theBook;

	public:
		
		TEST_METHOD(Book_GetTitle_Null)		// will check on an empty object I get null from getTitle()
		{
			auto res = theBook.getTitle();
			Assert::IsNull(res);			
		}
		
		TEST_METHOD(Book_SetTitle)
		{
			theBook.setTitle("abc123");
			auto res = theBook.getTitle();

			Assert::AreEqual("abc123", res);
		}

		TEST_METHOD(Book_SubscriptionOperator)
		{
			theBook[0] = 'Z';
			auto res = theBook.getTitle();

			Assert::AreEqual("Zbc123", res);
		}


	};
}
