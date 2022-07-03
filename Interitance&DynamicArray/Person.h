#pragma once
#include <iostream>
#include <string>
#include "Date.h"
class Person
{
	friend ostream& operator<< (ostream& cout, const Person& p)
	{
		cout << "persone name : " << p.name << " birth date : " << p.birthDate;
	}; // ��� ������ �����ε�
public:
	Person()
	{ 
		int i;
		int length = rand() % 4 + 4;// name�� ���̴� 4~7
		char names[8];
		names[0] = rand() % 26 + 'A'; // name�� ù��° ���ڴ� �빮��
		for (i = 1; i < length; i++)
			names[i] = rand() % 26 + 'a'; // name�� ������ ���ڴ� �ҹ���
		names[i] = '\0'; // ���ڿ� �������� �ι��� 
		birthDate = Date(); // Date() ������� birthDate�� ����
		name = names; 
	};
	Person(string n, Date bd) { name = n; birthDate = bd; };
	void setName(string n) { name = n; }
	void setBirthDate(Date bd) { birthDate = bd; }
	string getName() const { return name; }
	Date getBirthDate() const { return birthDate; }
protected:
	Date birthDate;
	string name;
};
