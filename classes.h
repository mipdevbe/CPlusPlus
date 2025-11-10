#pragma once
#include <iostream>
#include <string>

using namespace std;

class Employee;
class Project
{
	string _name;

public:
	shared_ptr<Employee> _employee;

	Project() {
		cout << "Project created." << endl;
	}

	~Project() {
		cout << "Project destroyed." << endl;
	}	

	void SetName(const string& name) {
		_name = name;
	}

	void ShowProjectDetails() const {
		cout << "Project Name: " << _name << endl;
	}
};

class Employee
{

public:

	weak_ptr<Project> _project{ };

	Employee() {
		cout << "Employee created." << endl;
	}	

	~Employee() {
		cout << "Employee destroyed." << endl;
	}

	/*
	void SetProject(const shared_ptr<Project>& project) {
		_project = project;
	}
	 
	const shared_ptr<Project>& GetProject() const {
		return _project;
	} 
	*/
};

class Printer {
	weak_ptr<int> _valuePtr{ };
public:
	void SetValue(const weak_ptr<int> valuePtr) {
		_valuePtr = valuePtr;
	}

	void Print() const {

		if (_valuePtr.expired()) {
			cout << "Value pointer is no longer available." << endl;
			return;
		}
		
		auto sp = _valuePtr.lock(); // increment by 1
		cout << "Value: " << *sp << endl;
		cout << "Reference count: " << sp.use_count() << endl;
	}
};

class Point {
	int _x;
	int _y;
public:
	Point(int x ,int y ) :_x(x), _y(y) {
		cout << "Point constructed." << endl;
	}
};

class Distance {
	long double _kilometers;

public:
	Distance(long double km) :_kilometers(km) {
		cout << "Distance constructed with " << km << " kilometers." << endl;
	}
	~Distance() {
		cout << "Distance destructed." << endl;
	}

	long double GetKm() const {
		return _kilometers;
	}

	void SetKm(long double km) {
		_kilometers = km;
	}

};

Distance operator "" _meters(long double km);
Distance operator "" _mi(long double km);