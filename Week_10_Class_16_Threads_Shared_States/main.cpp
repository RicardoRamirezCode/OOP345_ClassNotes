#include <iostream>
#include <thread>
#include <future>		// access to promise/future
using namespace std;



// main function of this thread
// this function should recieve the future object; and to prevent copies between main thread and doWork we will pass by reference
void doWork(std::future<double>& f)
{
	cout << "[" << this_thread::get_id() << "] Work Began:\n";

	// simulate work
	for (size_t i = 0; i < 50u; ++i)
	{
		this_thread::sleep_for(20ms);
		cout << ".";
	}

	cout << "\n[" << this_thread::get_id() << "] Waiting for data from the main thread...\n";
	// local variable to recieve data from main thread
	// going to use future object to retrieve that data
	double val = f.get();		// .get()returns an object of the templated type (value passed between threads)
	// here, if data is available (meaning promise already met) get returns immediately and gives me the value
	// if value not already set (meaning promise hasn't been kept yet) get is BLOCKING
	// ---- is blocking until the data is set in the promise  (waiting on main to set data)
	cout << "got " << val << "! Continue working.\n\t";

	// simulate work
	for (size_t i = 0; i < 50u; ++i)
	{
		this_thread::sleep_for(50ms);
		cout << ".";
	}

	cout << "\n[" << this_thread::get_id() << "] Work Finished.\n";
}


int main()
{
	// one of the biggest issues with threads
	// sync access to shared states [variable that can be shared between multiple threads]

	// if AT LEAST one thread updates/modifies the shared state => must sync access to it
	// if ALL threads just read the shared state => no sync is necessary
		
	// c++ offers a solution [promise/future] with drawback you can not pass data back and forth

	// promise/future [two classes]
	// allows you to pass data one time 

	// promise -- a thread promises to pass some data (sets the data)
	// future  -- the promise will be checked in the future (reads the data)

	// can only be USED ONCE
	// one time sends promise one time recieves

	// type of data not important as classes are templated

	cout << "[" << this_thread::get_id() << "] Main thread started.\n";

	// need objects to use to transmit data between threads:
	// going to create promise object; promise is templated class
	std::promise<double> p;

	// now need future associated to this promise
	std::future<double> f = p.get_future();
	// need future assocated to this promise p

	// need to pass pointer to a function that is the main function of thread (doWork)
	// and the params for the thread
	// here need to pass references between threads so we use
	// std:: ref to create a wrapper for my future
	std::thread t(doWork, std::ref(f));
	// above start the child thread (worker)
	
	// ... busy calculating the value to be sent to the worker
	// simulate this 'busy':
	this_thread::sleep_for(5s);

	// assume now the value is ready, send it to the other thread
	// we use promise
	p.set_value(1.2345);

	// wait until the worker finishes
	t.join();

	cout << "[" << this_thread::get_id() << "] Main thread ended.\n";

	// if child thread needs to pass value to main
	// above main was passing value to child thread

	// need to switch which object we pass to the thread
	// whichever thread is producing the value needs to have the promise object
	// whichever thread will consume the value needs to have the future object

	// doWork would need to receive a promise instead of a future
	// and val would set the value not read the value

}