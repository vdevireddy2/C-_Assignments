#pragma once

/*
** Class templates are used in the class declaration to allow generic parameters 
** i.e. object of any type can extend this class and we can print the base class statistics using this class
*/
template <class T>
class ObjectInfo
{
public:
	ObjectInfo();
	virtual ~ObjectInfo(void);
	void printSize();
	
private:
	static int  m_counter;
	int         m_objectNumber;
	const char* m_objectName;

};


