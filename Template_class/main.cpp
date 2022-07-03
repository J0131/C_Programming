/*****************************************
* ���ϸ��� : ���ø��� �̿��Ͽ� �л����� �����ϰ� ����ϴ� ���α׷� 
* �ۼ��� : �ֹ��� 
* final update : 2020.10.15
*****************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Student.h"
#include "T_Entry.h"
#include "TA_Entry.h"
using namespace std;
#define NUM_EVENTS 10
#define Events_per_Line 1
#define NUM_STUDENTS 10
#define Students_per_Line 1
Student sample_students[NUM_STUDENTS] =
{
	Student(21811000, string("Kim,   G-M"), Date(1990, 10, 5), Time(11, 45, 10), 3.57),
	Student(21611075, string("Yoon,  S-M"), Date(1990, 4, 5), Time(7, 30, 0), 4.37),
	Student(21411015, string("Hwang, S-S"), Date(1989, 1, 10), Time(3, 0, 0), 2.72),
	Student(21611054, string("Lee,   K-M"), Date(1991, 5, 15), Time(8, 30, 0), 3.35),
	Student(21311340, string("Hong,  G-M"), Date(1990, 2, 5), Time(2, 10, 0), 3.89),
	Student(21712056, string("Jang,  S-M"), Date(1990, 3, 15), Time(9, 20, 0), 4.42),
	Student(21411017, string("Park,  S-T"), Date(1989, 7, 10), Time(4, 20, 0), 4.12),
	Student(21512051, string("Choi,  Y-H"), Date(1992, 9, 25), Time(11, 45, 15), 3.85),
	Student(21211019, string("Shin,  D-J"), Date(1988, 10, 3), Time(1, 0, 0), 3.21),
	Student(21111053, string("Kwak,  S-B"), Date(1994, 11, 15), Time(6, 0, 0), 4.45),
}; // �л��迭�� ������ ���� ������ ����
void main()
{
	ofstream fout;
	fout.open("output.txt"); // ������� ����
	if (fout.fail())
	{
		cout << "Fail to open output.txt file for results !!" << endl;
		exit;
	}
	TA_Entry<string, Student*> TA_Students_keyName(NUM_STUDENTS,string("TA_Entry(name, Student)")); // TA_Entry<string, Student*>���� TA_Students_keyName����
	T_Entry<string, Student*> entry_name_student; // T_Entry<string, Student*>���� entry_name_student����
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		entry_name_student.setKey(sample_students[i].getName()); // �л��迭������ �̸��� �о� key�� ����
		entry_name_student.setValue(&sample_students[i]); // �л��迭������ �ּҰ��� value�� ����
		TA_Students_keyName.insert(i, entry_name_student); // TA_Students_keyName�� entry_name_student�� ���ʷ� ����
	}
	fout << "Students (key: name) in TA_Entry(keyName, Student) after initialization: " << endl;
	TA_Students_keyName.fprint(fout, Students_per_Line); // ���
	fout << "Students (key: name) in TA_Entry(keyName, Student) after sorting: " << endl;
	TA_Students_keyName.quick_sort(INCREASING); // ������������ ����
	TA_Students_keyName.fprint(fout, Students_per_Line);
	TA_Entry<int, Student*> TA_Students_keyID(NUM_STUDENTS, string("TA_Entry(st_id, Student)"));  // TA_Entry<int, Student*>���� TA_Students_keyName����
	T_Entry<int, Student*> entry_ID_student; // T_Entry<int, Student*>���� entry_name_student����
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		entry_ID_student.setKey(sample_students[i].getST_id()); // �л��迭������ �й��� �о� key�� ����
		entry_ID_student.setValue(&sample_students[i]); // �л��迭������ �ּҰ��� value�� ����
		TA_Students_keyID.insert(i, entry_ID_student); // TA_Students_keyName�� entry_name_student�� ���ʷ� ����
	}
	fout << "Students (key: ST_ID) in TA_Entry(keyID, Student) after initialization: " << endl;
	TA_Students_keyID.fprint(fout, Students_per_Line);
	fout << "Students (key: ST_ID) in TA_Entry(keyID, Student) after sorting: " << endl;
	TA_Students_keyID.quick_sort(INCREASING);
	TA_Students_keyID.fprint(fout, Students_per_Line);
	TA_Entry<double, Student*> TA_Students_keyGPA(NUM_STUDENTS,string("TA_Entry(GPA, Student)")); // TA_Entry<double, Student*>���� TA_Students_keyName����
	T_Entry<double, Student*> entry_GPA_student; // T_Entry<double, Student*>���� entry_name_student����
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		entry_GPA_student.setKey(sample_students[i].getGPA()); // �л��迭������ ������ �о� key�� ����
		entry_GPA_student.setValue(&sample_students[i]); // �л��迭������ �ּҰ��� value�� ����
		TA_Students_keyGPA.insert(i, entry_GPA_student); // TA_Students_keyName�� entry_name_student�� ���ʷ� ����
	}
	fout << "Students (key: GPA) in TA_Entry(keyGPA, Student) after initialization: " << endl;
	TA_Students_keyGPA.fprint(fout, Students_per_Line);
	fout << "Students (key: GPA) in TA_Entry(keyGPA, Student) after sorting: " << endl;
	TA_Students_keyGPA.quick_sort(DECREASING);
	TA_Students_keyGPA.fprint(fout, Students_per_Line);
	TA_Entry<Time, Student*> TA_Students_keyTime(NUM_STUDENTS,string("TA_Entry(Time, Student)")); // TA_Entry<Time, Student*>���� TA_Students_keyName����
	T_Entry<Time, Student*> entry_Time_student; // T_Entry<Time, Student*>���� entry_name_student����
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		entry_Time_student.setKey(sample_students[i].getArrTime()); // �л��迭������ �����ð��� �о� key�� ����
		entry_Time_student.setValue(&sample_students[i]);  // �л��迭������ �ּҰ��� value�� ����
		TA_Students_keyTime.insert(i, entry_Time_student); // TA_Students_keyName�� entry_name_student�� ���ʷ� ����
	}
	fout << "Students (key: Time) in TA_Entry(keyTime, Student) after initialization: " << endl;
	TA_Students_keyTime.fprint(fout, Students_per_Line);
	fout << "Students (key: Time) in TA_Entry(keyTime, Student) after sorting: " << endl;
	TA_Students_keyTime.quick_sort(INCREASING);
	TA_Students_keyTime.fprint(fout, Students_per_Line);
	fout.close();
}