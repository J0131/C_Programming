#include "Person.h"

ostream& operator<< (ostream& fout, Person& p)
{
	fout << setw(10) << p.name;
	fout << setw(10) << p.dateOfBirth;
	return fout;
} // ��¿����� �����ε�
Person::Person()
{
	name = "string";
	dateOfBirth = Date();
} // �⺻������
Person::Person(string n,Date bod)
{
	name = n;
	dateOfBirth = bod;
} // ������