#include "Person.h"

ostream& operator<< (ostream& fout, Person& p)
{
	fout << setw(10) << p.name;
	fout << setw(10) << p.dateOfBirth;
	return fout;
} // 출력연산자 오버로딩
Person::Person()
{
	name = "string";
	dateOfBirth = Date();
} // 기본생성자
Person::Person(string n,Date bod)
{
	name = n;
	dateOfBirth = bod;
} // 생성자