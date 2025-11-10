#pragma once

#include <iostream>

using namespace std;

class Integer
{
public:
	Integer();
	~Integer();
	/*explicit*/ Integer(int value);
	Integer(const Integer& other); // Copy constructor
	Integer(Integer&& other) noexcept;

	int GetValue() const;
	void SetValue(int value);

	Integer& operator+(const Integer& other); // Copy assignment operator

	Integer& operator=(const Integer& other); // Copy assignment operator
	Integer& operator=(Integer&& other) noexcept; // Copy assignment operator

	void operator ()();

	explicit operator int() const; // Type conversion operator

	friend istream& operator >> (istream& input, Integer& a);

private:
	int* m_intPtr{ nullptr };
};

