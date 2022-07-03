/************************************
* 파일목적 : 상속클래스기반의 학생배열을 생성하고 정렬하여 파일에 출력하는 프로그램
* 작성자 : 최범준
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
	StudentArray studentArray(NUM_STUDENTS); // StudentArray형의 studentArray생성
	Student st; // Student형의 st선언
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open an output file (output.txt)\n";
		exit(1);
	}
	fout << "Initializing student array (num_students: " << NUM_STUDENTS << ")" << endl;
	srand(time(0)); // 시드초기화
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		st = genStudent(); // genStudent()의 결과를 st에 대입
		studentArray[i] = st; // studentArray[i]에 st를 대입
	}
	fout << studentArray;
	fout << "\nSorting studentArray by student id : " << endl;
	studentArray.sortByST_ID(); // 학번에 따른 정렬
	fout << studentArray;
	fout << "\nSorting studentArray by student name : " << endl;
	studentArray.sortByName(); // 이름에 따른 정렬
	fout << studentArray;
	fout << "\nSorting studentArray by GPA : " << endl;
	studentArray.sortByGPA(); // 학점에 따른 정렬
	fout << studentArray;
	fout << "\nSorting studentArray by BirthDate : " << endl;
	studentArray.sortByBirthDate(); // 생일에 따른 정렬
	fout << studentArray;
	fout << endl;
	fout.close();
}

Student genStudent()
{
	int i, j=1;
	static int student[50000] = { 0 }; // 정적 배열 student선언
	while (j == 1)
	{
		Student st; // Student형 st선언
		st = Student(); // Student()의 결과를 st에 대입 
		i = st.getST_id(); // st의 학번을 읽어 i에 저장
		if (student[i] == 1) // 이미 만들어진적이있다면 다시생성
			continue;
		else
		{
			student[i] = 1; // 만들어진적이없다면 i인덱스의 원소를 1로 변경
			return st; // st반환
		}
	}
}