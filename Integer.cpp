#include "Integer.h"


using namespace std;

Integer::Integer()
{
	cout << "Integer::Integer()" << endl;
	m_intPtr = new int(0);
}

Integer::~Integer()
{
	cout << "Integer::~Integer()" << endl;
	delete m_intPtr;
	m_intPtr = nullptr;
}

Integer::Integer(int value)
{
	cout << "Integer::Integer(int)" << endl;
	m_intPtr = new int(value);
}
Integer::Integer(const Integer& other)
{
	cout << "Integer::Integer(const Integer&)" << endl;
	m_intPtr = new int(*other.m_intPtr);
}

Integer::Integer(Integer&& other) noexcept
{
	cout << "Integer::Integer(Integer&& other)" << endl;
	std::exchange(m_intPtr, other.m_intPtr);
	other.m_intPtr = nullptr;
}

int Integer::GetValue() const
{
	return *m_intPtr;
}

void Integer::SetValue(int value)
{
	*m_intPtr = value;
}

Integer& Integer::operator +(const Integer& other)
{	
	SetValue(*m_intPtr + *other.m_intPtr);
	return *this;
}

Integer& Integer::operator =(const Integer& other)
{
	if (this != &other)
	{
		delete m_intPtr;
		m_intPtr = new int(*other.m_intPtr);
	}

	return *this;
}

Integer& Integer::operator =(Integer&& other)  noexcept
{
	if (this != &other)
	{
		delete m_intPtr;
		std::exchange(m_intPtr, other.m_intPtr);
		other.m_intPtr = nullptr;
	}

	return *this;
}

void Integer::operator ()()
{
	cout << *m_intPtr << endl;
}

Integer::operator int() const
{
	return *m_intPtr;
}