#pragma once
#include <iostream>
#include <iomanip>
#include "Time.h"
#include "Date.h"
#include <string>
using namespace std;

class Person
{
	friend ostream& operator<< (ostream&, Person&); // 출력연산자
public:
	Person();
	Person(string n, Date dob); // 생성자
	void setName(string n) { name = n; } // 설정
	string getName() { return name; } // 읽어오기
protected:
	string name;
	Date dateOfBirth;
};

