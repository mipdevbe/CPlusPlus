#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include "Integer.h"
#include "classes.h"

using namespace std;

//
//// Rerturn r-value
//int Add(int x, int y)
//{
//    return x + y;
//}
//
//// return l-value
//int & Transform(int &x)
//{
//    x *= x;
//    return x;
//}
//
//void Print(int &x)
//{
//	std::cout << "Print(int& x)" << std::endl;
//}
//
//void Print(const int& x)
//{
//	std::cout << "Print(const int& x)" << std::endl;
//}
//
//void Print(int&& x)
//{
//	std::cout << "Print(int&& x)" << std::endl;
//}

Integer operator +(int x, const Integer& y)
{
	Integer temp;
	temp.SetValue(x + y.GetValue());
	return temp; // R-value
}


Integer Add(const Integer& a, const Integer& b)
{
	Integer temp;
	temp.SetValue(a.GetValue() + b.GetValue());
	return temp; // R-value
}

ostream& operator << (ostream& out , const Integer& a)
{
	out << a.GetValue();
	return out;
}

istream& operator >> (istream& input, Integer& a)
{
	int x;
	input >> x;
	*a.m_intPtr = x;
	a.SetValue(x);
	return input;
}

class IntPtr {
private:
	Integer* m_ptr{ nullptr };

public:
	IntPtr(Integer* p) : m_ptr{ p } {
		 
	}
	~IntPtr() {
		delete m_ptr;
	}

	Integer* operator->() {
		return m_ptr;
	}

	Integer& operator *() {
		return *m_ptr;
	}
};

void CreateInteger() {
	IntPtr p = new Integer();

	(*p).SetValue(10);
	cout << "Created Integer with value: " << (*p).GetValue() << endl;
}


void ProcessInteger(shared_ptr<Integer> p) {
	cout << "Processing Integer with value: " << (*p).GetValue() << endl;
}

void CreateIntegerV2() {
	shared_ptr<Integer> p(new Integer);
	(*p).SetValue(10);

	ProcessInteger(p);

	//cout << "Created Integer with value: " << (*p).GetValue() << endl;
}

class Product 
{
	Integer m_Id;
	int x;
public:
	Product(const Integer& id):m_Id{id}, x(id.GetValue()) {
		cout << "Product::Product(const Integer& id)" << endl;
	}

	~Product() {
		cout << "Product::~Product()" << endl;
	}

	const Integer& GetInteger() const {
		return m_Id;
	}	

	operator Integer() {
		return m_Id;
	}
};

void Display(Integer* p) {
	if (!p) {
		cout << "Null pointer received." << endl;
		return;
	}

	cout << "Integer value: " << p->GetValue() << endl;
}

Integer* GetPointer(int value) {
	Integer* p = new Integer{value};
	return p; // Dangling pointer
}

void Operate(int value) {
	Integer* p = GetPointer(value);
	if (p == nullptr) {
		p = new Integer{};
	}

	p->SetValue(100);
	Display(p);
	delete p;

	p = new Integer{};
	*p = __LINE__;
	Display(p);
	delete p;
	p = nullptr;
}
/*
void ShowInfo(const shared_ptr<Employee>& emp) {
	if (emp == nullptr) {
		cout << "Employee pointer is null." << endl;
		return;
	}

	emp->GetProject()->ShowProjectDetails();
}
*/

// Deleter for unique_ptr
struct Free {
	void operator()(int* p) const {
		cout << "Custom free for pointer: " << p << endl;
		free(p);
	}
};

void MallocFree(int* valuePtr) {
	cout << "Value: " << *valuePtr << endl;
	free(valuePtr);
}

void UniquePtrDeleters()
{
	//unique_ptr<int, Free> p{ (int*)malloc(sizeof(int)) , Free {} };
	unique_ptr<int, void(*)(int*)> p{ (int*)malloc(sizeof(int)) , MallocFree };
	*p = 100;
	cout << *p << endl;
}

void SharedPtrDeleters()
{
//	shared_ptr<int> p{ (int*)malloc(sizeof(int)) , MallocFree };
	shared_ptr<int> p{ (int*)malloc(sizeof(int)) , Free{} };
	*p = 100;
	cout << *p << endl;

}

enum class Color : int{
	Red,
	Green,
	Blue
};

void FillColor(Color color)
{
	switch (color)
	{
		case Color::Red:
			cout << "Filling Red color." << endl;
			break;
		case Color::Green:
			cout << "Filling Green color." << endl;
			break;
		case Color::Blue:
			cout << "Filling Blue color." << endl;
			break;
	}
}

// scoped enum with underlying type char
enum class TrafficLight : char {   
	Red = 'r',
	Green = 'g',
	Blue = 'b'
};

const string Combine(const string& firstName, const string& lastName)
{
	string fullName = firstName + " " + lastName;	
	return fullName;
}

// only a single line statement
constexpr int GetNumber()
{
	return 42;
}

// only a single line statement
constexpr int Add(int a, int b)
{
	return a + b;
}

// if then else only in c++ 14
// below c++ 14 a > b ? a : b;
constexpr int Max(int a, int b)
{
	if (a > b)
		return a;
	
	return b;
}


int main()
{
/*
	Integer a(1), b(3);
	a.SetValue(Add(a, b).GetValue());

	a();

	Integer sum = a + 5;

	Integer sum2 = 5 + a;
	//cin >> a;
	//cout << sum << endl;
*/

	//CreateInteger();
	//CreateIntegerV2();

	//int a = 5, b = 2;
	//float b = static_cast<float>(a) / b;

	//const int x = 1;
	//int* p = const_cast<int*>(&x);

	//float f = 1.23f;
	//char* p = reinterpret_cast<char*>(&f);

	//Integer a1{ 5 };

	//// Initialization
	//Integer a2 = 3; // Copy constructor

	//// Assignment
	//a1 = 10;

	//int val = static_cast<int>(a1);  // because explicit is applied.

	//Product p2{ 5 };
	//Integer id = p2; // id = p2.operator Integer();

	//Product p3(5);


	Operate(5);

	shared_ptr<Employee> emp1{ new Employee() };
	shared_ptr<Project> proj{ new Project() };
	proj->SetName("AI Development");

	emp1->_project = proj;
	proj->_employee = emp1;

	/*
	shared_ptr<Employee> emp1{ new Employee() };
	emp1->SetProject(proj);
	ShowInfo(emp1);

	shared_ptr<Employee> emp2{ new Employee() };
	emp2->SetProject(proj);
	ShowInfo(emp2);

	shared_ptr<Employee> emp3{ new Employee() };
	emp3->SetProject(proj);
	ShowInfo(emp3);
	*/

	// emp1.reset();
	// emp1.reset(new Employee());
	/*
	if (emp3) {
		// valid			
	}
	cout << "Project reference count: " << proj.use_count() << endl;

	proj->ShowProjectDetails();

	Printer printer;
	int num{};
	cin >> num;

	shared_ptr<int> valuePtr{ new int{ num } };
	printer.SetValue(valuePtr);

	if (*valuePtr > 10) {
		valuePtr = nullptr;
	}

	printer.Print();
	*/

	UniquePtrDeleters();
	SharedPtrDeleters();

	unique_ptr<int[]> p1{new int[5] {1,2,3,4,5}};
	p1[0] = 100;

	shared_ptr<int[]> p2{ new int[5] {1,2,3,4,5} };
	p2[0] = 100;

	auto p3 = make_unique<int>(5);
	auto p4 = make_unique<Point>(1, 2);

	auto p5 = make_unique<int[]>(5) ;
	p5[0] = 10;

	auto p6 = make_shared<int>(10);
	cout << *p6 << endl;

	Color c = Color::Red;
	FillColor(c);

	int x = static_cast<int>(Color::Blue); // Error

	string firstName;
	string lastName;

//	std::getline(cin, firstName);
	//std::getline(cin, lastName);

	string fullName = firstName + " " + lastName;
	cout << "Full Name: " << fullName << endl;

	//const char* fullNamePtr = Combine(firstName, lastName);
	// 
	// insert into databe
	// 
	
	//cout << "Full Name: " << fullNamePtr << endl;	


	// Initialize and assign
	string s = "Hello";
	s = "World";

	// Access
	s[0] = 'h';
	char ch = s[1];

//	getline(cin, s);

	// Size
	size_t l = s.length(); // faster

	// Insert and concatenate
	string s1 = "Hello";
	string s2 = "World";
	s = s1 + " " + s2;	

	s += "!";

	s.insert(5, ",");

	// Comparaison
	if (s1 != s2) {
		cout << "Strings are different." << endl;
	}

	// Removal
	s.erase(5, 1); // remove comma
	s.erase();

	s.clear();

	// Search.
	auto position = s.find("lo", 0);
	if (position != string::npos) {
		cout << "'lo' found at position: " << position << endl;
	}
	else {
		cout << "'lo' not found." << endl;
	}

	printf("%s", s.c_str());

	int a{ 5 }, b{ 6 };
	int sum = a + b;
	cout << "Sum of " << a << " & " << b << " is : " << sum << endl;

	stringstream ss;

	ss << "Sum of " << a << " & " << b << " is : " << sum << endl;
	string st = ss.str();
	cout << st << endl;

	ss.str(""); // clear the stringstream	
	ss << sum;
	auto ssum = ss.str();
	cout << "Sum as string: " << ssum << endl;

	auto sumStr = to_string(sum); // for all primitive type.
	cout << "Sum as string: " << sumStr << endl;

	string data = "12 89 21";
	int aValue;
	stringstream ssdata;
	ssdata.str(data);
	while (!ssdata.eof()) {
		ssdata >> aValue;
		cout << "Extracted integer: " << aValue << endl;
	}

	ssdata.str(data);
	while (ssdata >> aValue) {
		cout << "Extracted integer: " << aValue << endl;
	}

	int xValue = stoi("1234");

	istringstream is;
	ostringstream os;

	Distance dist1{ 32.0_mi };
	Distance dist2{ 32.0_meters };

	cout << "Distance in kilometers: " << dist1.GetKm() << " km" << endl;
	cout << "Distance in kilometers: " << dist2.GetKm() << " km" << endl;
	
	constexpr int i = GetNumber(); 
	int arr[i];

/*	
	const int j = GetNumber();
	int arr1[j];
*/

	int x = GetNumber();

	// compiled time value
	constexpr int sumConst = Add(10, 20);

	// runtime time value
	int sumVar = Add(15, 25);

	//free(p);
	return 0;
}

