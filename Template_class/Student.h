#pragma once
#include "Time.h"
#include "Person.h"

class Student : public Person
{
	friend ostream& operator<< (ostream&, Student&); // 출력연산자
public:
	Student(); // 
	Student(int id, string n, Date bod,Time avt, double gpa_); // 생성자
	int getST_id() { return st_id; } 
	double getGPA() { return gpa; }
	Time getArrTime() { return arrivalTime; }
	void setST_id(int id) { st_id = id; }
	void setGPA(double g) { gpa = g; }
	void setArrivalTime(Time t) { arrivalTime = t; }
	Time getArrivalTime() { return arrivalTime; }
private:
	int st_id;
	double gpa;
	Time arrivalTime;
};

