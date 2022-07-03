#include "Student.h"

ostream& operator<< (ostream& fout, Student& s)
{
	fout << "Student [ " << "st_id: " << s.st_id << ", name: " << setw(10) << s.name << ", arrival: " << s.arrivalTime << ", gpa: " << s.gpa << "]";
	return fout;
} // 출력연산자 오버로딩

Student::Student()
	:Person()
{
	st_id = 00000000;
	arrivalTime = Time();
	gpa = 0.0;
}// 기본생성자
Student::Student(int id, string n, Date bod, Time avt, double gpa_)
	:Person(n,bod)
{
	st_id = id;
	arrivalTime = avt;
	gpa = gpa_;
}// 생성자