/************************************
* ���ϸ��� : ���Ŭ��������� �л��迭�� �����ϰ� �����Ͽ� ���Ͽ� ����ϴ� ���α׷�
* �ۼ��� : �ֹ���
* final update : 2020.10.08
************************************/
#include <iostream>
#include <fstream>
#include "StudentArray.h"
#include <string>

#define NUM_STUDENTS 5
Student genStudent();
void main()
{
	StudentArray studentArray(NUM_STUDENTS); // StudentArray���� studentArray����
	Student st; // Student���� st����
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open an output file (output.txt)\n";
		exit(1);
	}
	fout << "Initializing student array (num_students: " << NUM_STUDENTS << ")" << endl;
	srand(time(0)); // �õ��ʱ�ȭ
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		st = genStudent(); // genStudent()�� ����� st�� ����
		studentArray[i] = st; // studentArray[i]�� st�� ����
	}
	fout << studentArray;
	fout << "\nSorting studentArray by student id : " << endl;
	studentArray.sortByST_ID(); // �й��� ���� ����
	fout << studentArray;
	fout << "\nSorting studentArray by student name : " << endl;
	studentArray.sortByName(); // �̸��� ���� ����
	fout << studentArray;
	fout << "\nSorting studentArray by GPA : " << endl;
	studentArray.sortByGPA(); // ������ ���� ����
	fout << studentArray;
	fout << "\nSorting studentArray by BirthDate : " << endl;
	studentArray.sortByBirthDate(); // ���Ͽ� ���� ����
	fout << studentArray;
	fout << endl;
	fout.close();
}

Student genStudent()
{
	int i, j=1;
	static int student[50000] = { 0 }; // ���� �迭 student����
	while (j == 1)
	{
		Student st; // Student�� st����
		st = Student(); // Student()�� ����� st�� ���� 
		i = st.getST_id(); // st�� �й��� �о� i�� ����
		if (student[i] == 1) // �̹� ������������ִٸ� �ٽû���
			continue;
		else
		{
			student[i] = 1; // ����������̾��ٸ� i�ε����� ���Ҹ� 1�� ����
			return st; // st��ȯ
		}
	}
}