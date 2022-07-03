#pragma once
#include <iostream>
#include <string>
#include "Date.h"
class Person
{
	friend ostream& operator<< (ostream& cout, const Person& p)
	{
		cout << "persone name : " << p.name << " birth date : " << p.birthDate;
	}; // 출력 연산자 오버로딩
public:
	Person()
	{ 
		int i;
		int length = rand() % 4 + 4;// name의 길이는 4~7
		char names[8];
		names[0] = rand() % 26 + 'A'; // name의 첫번째 문자는 대문자
		for (i = 1; i < length; i++)
			names[i] = rand() % 26 + 'a'; // name의 나머지 문자는 소문자
		names[i] = '\0'; // 문자열 마지막에 널문자 
		birthDate = Date(); // Date() 결과값을 birthDate에 저장
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
