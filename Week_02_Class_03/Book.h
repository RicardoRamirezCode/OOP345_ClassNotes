#ifndef BOOK_H
#define BOOK_H

struct Book
{	
	char* m_title;	// array of characters (null terminated)	
	double m_price;	// price without tax, in CAD

	double getPriceWithTax();
	const char* getTitle();
	void setTitle(const char* title);

	char& operator[](size_t idx);		// return character at idx from title

};


// global function; could add to utility module but small project
int multiply(int a, int b);



#endif // !BOOK_H
