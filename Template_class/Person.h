#pragma once
#include <iostream>
#include <iomanip>
#include "Time.h"
#include "Date.h"
#include <string>
using namespace std;

class Person
{
	friend ostream& operator<< (ostream&, Person&); // ��¿�����
public:
	Person();
	Person(string n, Date dob); // ������
	void setName(string n) { name = n; } // ����
	string getName() { return name; } // �о����
protected:
	string name;
	Date dateOfBirth;
};

