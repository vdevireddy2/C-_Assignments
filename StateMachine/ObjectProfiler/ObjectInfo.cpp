
#include "ObjectInfo.h"
#include "TimePrinter.h"

using namespace std;

// Initializing member variable
template<class T>
int ObjectInfo<T>::m_counter = 0;

// Constructor
template<class T>
ObjectInfo<T>::ObjectInfo() :
	m_objectName(typeid(T).name())
{
	m_objectNumber = ++m_counter;
	cout << "Object: " << m_objectName << "# " << m_objectNumber << " created @ " << TimePrinter()  << endl;

}

//Distructor
template<class T>
ObjectInfo<T>::~ObjectInfo(void)
{
	cout << "Object: " << m_objectName << "# " << m_objectNumber << " destroyed @ " << TimePrinter()  << endl;
}

// This method will print the no of objects and size of each object
template<class T>
void ObjectInfo<T>::printSize() {
	std::cout << m_counter << " instances of " << m_objectName <<
		", " << sizeof(T) << " bytes each." << std::endl;
}



// the use pattern
struct _AInfo1 : public ObjectInfo<_AInfo1> {
	_AInfo1() : ObjectInfo() {}
};

//_AInfo is profiling class
//_A  is profiled class
struct _A {
	_AInfo1 m_info;
};


// Test class to test the ObjectInfo class
class _AInfo : public ObjectInfo<_AInfo> {

public:
	_AInfo() : ObjectInfo() {}
	
	/*
	** This method will sleep for given no. of seconds
	** This method is used for testing the TimePrinter() method, to capture the delay between
	** object construction and distruction
	*/
	void sleep(long dwSeconds)
	{
		cout << "Sleeping for " << dwSeconds << "seconds" << endl;
		boost::this_thread::sleep(boost::posix_time::seconds(dwSeconds));
	}
};

/*
** Main method used for testing the functionality of the code
*/
int main()
{
	cout << "Hello, this is my assignment2" << endl;

	_A a1;
	_A a2;
	_A a3;
	a1.m_info.printSize();

	
	_AInfo aInfo1;
	aInfo1.sleep(5);
	_AInfo aInfo2;
	_AInfo aInfo3;

	aInfo1.printSize();

	
}
