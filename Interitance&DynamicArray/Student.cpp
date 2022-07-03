#include "Student.h"

Student::Student()
	:Person()
{
	int i,length = rand() % 2 + 3; // dept길이는 3~4
	char dept[5];
	for (i = 0; i < length; i++)
		dept[i] = rand() % 26 + 'A'; // dept는 모두대문자
	dept[i] = '\0'; // 마지막에 널문자 
	st_id = rand() % 40000 + 10000; // st_id는 10000~50000
	dept_name = dept;
	gpa = (rand()% 10000) / 100.0; // gpa는 0.00~99.9
}

Student::Student(string n, Date dob, int id, string dept_n, double gpa_)
	:Person(n,dob)
{
	st_id = id;
	dept_name = dept_n;
	gpa = gpa_;
} // 생성자

ostream& operator<< (ostream& fout, const Student& st)
{
	fout.setf(ios::fixed);
	fout.precision(2);
	fout.setf(ios::right);

	fout << "Student [ name : " << setw(8)<< st.name << ", birth date : " << st.birthDate << ", st_id : ";
	fout << setw(6)<< st.st_id << ", dept: " << setw(6)<<st.dept_name << ", gpa: " << setw(5)<<st.gpa << " ]";
	return fout;
} // 출력 연산자 오버로딩 함수

const Student& Student::operator =(const Student& right)
{
	birthDate = right.birthDate;
	st_id = right.st_id;
	name = right.name;
	dept_name = right.dept_name;
	gpa = right.gpa;

	return *this;
} // 대입 연산자 오버로딩 함수