#pragma once
#include "Person.h"
class StudentArray;
class Student : public Person
{
	friend class StudentArray;
	friend ostream& operator<< (ostream&, const Student&);
public:
	Student(); // 기본 생성자
	Student(string n, Date dob, int id, string dept_n, double gpa_);
	const Student& operator =(const Student& right);
	int getST_id() { return st_id; }
	void setST_id(int id) { st_id = id; }
	void setDept_name(string dp_n) { dept_name = dp_n; };
	void setGPA(double g) { gpa = g; }
private:
	int st_id;
	string dept_name;
	double gpa;
};
