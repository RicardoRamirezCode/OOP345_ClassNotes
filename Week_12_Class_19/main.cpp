#include <iostream>
#include <algorithm>
using namespace std;

// make a class to represent a list, make it templated class
// to not interfear with list will add it to namespace lectures

namespace lectures
{
	// will manage a collection of elements of a certain type T
	template<typename T>
	class list
	{
		// collection of items type T need to be linked somehow; 
		// ie if I have an item now what is the next one in the collection

		// represents an element in the list
		struct node
		{
			// the data stored in the list
			T m_data{};
			// link to the next element in the list -- pointer to the next element in the list
			node* m_next = nullptr;
			// link to the previous element in the list
			node* m_prev = nullptr;
		};

		// the address of the first node in the list
		node* m_head = nullptr;
		// the address of the last node in the list
		node* m_tail = nullptr;

	public:
		// this is a forward iterator
		// from reference a forward iterator requires: ++, ==, !=, *, ->
		struct iterator
		{
			// behind the scenes some algorithms will require these:
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			// this iterator will maintain a pointer to the current element (element it points to)
			// the element from the list this iterator points to
			node* m_current = nullptr;

			// assuming simple case where not null for following

			iterator& operator++()
			{
				//clog << "DEBUG: iterator::operator++ has been called\n";
				m_current = m_current->m_next;
				return *this;
			}
			// return true if the iterator points to different elements in the list
			bool operator!=(const iterator& other)
			{
				//clog << "DEBUG: iterator::operator!= has been called\n";
				return m_current != other.m_current;
			}
			// return true if the iterator points to same elements in the list
			bool operator==(const iterator& other)
			{
				//clog << "DEBUG: iterator::operator== has been called\n";
				return m_current == other.m_current;
			}

			T& operator*()
			{
				//clog << "DEBUG: iterator::operator* has been called\n";
				return m_current->m_data;
			}
		};

		list() {};
		list(const list& other) = delete;
		list& operator=(const list& other) = delete;

		~list()
		{
			while (m_head != nullptr)
			{
				// delete the head of the list
				node* tmp = m_head;			// remember the old head of the list
				m_head = m_head->m_next;	// move the head to second elem of list
				delete tmp;				// delete the old head

				// when reach head of list m_head will be nullptr and will stop while loop
			}
		}

		// need a way to add to the list, expose to the client a method to add to the list
		// inserts a new value ('data') at the end of the list
		void push_back(T data)
		{
			// need to create an element of node, can't use:
			// node elem;
			// as will go out of scope at end of block; so create a pointer instead:
			node* elem = new node();
			elem->m_data = data;
			elem->m_next = nullptr;

			if (m_head == nullptr)
			{
				// special case: list is empty
				m_head = elem;
				m_tail = elem;
			}
			else
			{
				// general case: there are elements in the list, insert at the end
				elem->m_prev = m_tail;
				m_tail->m_next = elem;
				// so m_tail is this element we have created
				m_tail = elem;
			}
		}

		// insert a new value ('data') at the beginning of the list
		void push_front(T data)
		{
			node* elem = new node();
			elem->m_data = data;
			
			if (m_head == nullptr)
			{
				// special case: list is empty
				m_head = elem;
				m_tail = elem;
			}
			else
			{
				// general case: there are elements in the list, insert at the beginning
				elem->m_next = m_head;
				m_head->m_prev = elem;
				m_head = elem;
			}
		}
		// will use iterator position to denote where to insert (using indexes discouraged)
		// will insert data of type T
		void insert(iterator& pos, T data)
		{
			node* elem = new node();
			elem->m_data = data;

			// general case -- insert in the middle of list
			// assumes I can dereference many pointers below
			elem->m_next = pos.m_current;
			elem->m_prev = pos.m_current->m_prev;

			elem->m_next->m_prev = elem;
			elem->m_prev->m_next = elem;
		}

		// returns an iterator at the start of the collection
		iterator begin()
		{
			// head is of type node (node*) and I need an iterator
			// need to make an iterator pointing there:
			clog << "DEBUG: list::begin() has been called\n";
			return iterator{ m_head };
		}

		// returns an iterator pointing to the element after the last one in the collection
		iterator end()
		{
			// assumption: the list contains elements (so we can dereference it)
			clog << "DEBUG: list::end() has been called\n";
			return iterator{ m_tail->m_next };
		}
	};
}

int main()
{
	lectures::list<int> lst;

	lst.push_front(11);
	lst.push_front(12);
	lst.push_front(13);
	lst.push_front(14);

	// need to implement iterators (and begin, end) to use this kind of loop
	for (auto item : lst)
		cout << item << " ";
	cout << endl;

	// below is 'basically' what is going on above; however it is more efficient above as the below for loop
	// is calling end() more often
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		auto& item = *it;
		cout << item << " ";
	}
	cout << endl;

	std::for_each(lst.begin(), lst.end(), [] (const int& item) {cout << item << " ";});
	cout << endl;

	// any_of goes over collection and see if at least one element matches condition
	auto res = std::any_of(lst.begin(), lst.end(), [] (const int& item) {return item % 5 == 0;});
	cout << "Is there a match? " << res << endl;

	// below requires we add using iterator_category = std::forward_iterator_tag;
	std::transform(lst.begin(), lst.end(), lst.begin(), [](int& item) {return item + 10;});
	std::for_each(lst.begin(), lst.end(), [] (const int& item) {cout << item << " ";});
	cout << endl;

	auto it = lst.begin();
	++(++it);
	lst.insert(it, 36);
	std::for_each(lst.begin(), lst.end(), [] (const int& item) {cout << item << " ";});
	cout << endl;
}