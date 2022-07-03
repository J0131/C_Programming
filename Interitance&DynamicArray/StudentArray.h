#pragma once
#include <iostream>
#include "Student.h"

class StudentArray
{
	friend ostream& operator<< (ostream&, StudentArray&); // ��� ������ �����ε�
public:
	StudentArray(int size); // ������
	StudentArray(const StudentArray& obj);
	~StudentArray();
	int size() { return num_students; }
	Student& operator[](int index);
	void sortByBirthDate();
	void sortByName();
	void sortByST_ID();
	void sortByGPA();
private:
	Student* students;
	int num_students;
	bool isValidIndex(int index);
};