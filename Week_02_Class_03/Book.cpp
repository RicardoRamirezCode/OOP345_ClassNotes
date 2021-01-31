#include "Book.h"

double Book::getPriceWithTax()
{
	return -1;
}

const char* Book::getTitle()
{
	return m_title;
}

void Book::setTitle(const char* title)
{
	// THIS IS WRONG AND SHOULD NOT BE DONE!!!!!!!! SHOULD NOT CONST_CAST as you are 'lying'
	this->m_title = const_cast<char *>(title);		// compiler will complain as title is const so need the const_cast
}

char& Book::operator[](size_t idx)
{
	// assume index is correct
	return m_title[idx];
}

int multiply(int a, int b)
{
	return a * b;
}