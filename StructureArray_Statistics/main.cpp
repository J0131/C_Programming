/************************************
* ���ϸ��� : �л��� ������ ����ü�� ���� ��Ÿ���� ���� �л����� ������ ����ü�迭�� �����Ͽ� �����ϴ� ���α׷�
* �ۼ��� : �ֹ���
* Final update : 2020-05-28
*************************************/

#include <stdio.h>
#include "Student.h"
#define MAX_NUM_STUDENTS 100
void main()
{
	int num_students = 0; // �л��� ���� �����ϰ� 0�����ʱ�ȭ
	int menu;
	Student* pST_GPA_max, * pST_GPA_min; // ����ü ������ ����
	extern Student students[]; // �ܺο��� ������ student����ü �迭 �ҷ�����
	for (int i = 0; i < MAX_NUM_STUDENTS; i++)
	{
		if (students[i].st_id == -1)
			break; // students[]����ü �迭�� ���ʷ� �а� �й��� -1�̵Ǹ� �ݺ��� ������
		else
			num_students++; // �л��� 1����
	}
	printf("Number of students = %d\n", num_students);
	while (1)
	{
		printf("\n");
		printf(" 1 : print student records\n");
		printf(" 2 : calculate statistics GPA (max, min, avg) of students' \n");
		printf(" 3 : search students of best GPA and worst GPA\n");
		printf(" 4 : sort students by student ID\n");
		printf(" 5 : sort students by GPA\n");
		printf(" 6 : sort students by name\n");
		printf(" 7 : sort students by date of birth\n");
		printf(" 8 : sort studetns by telephone number\n");
		printf("-1 : Quit\n");
		printf("Input menu = ");
		scanf("%d", &menu); // ���۸� ����ؼ� ���� �Է¹����� menu�� ����
		if (menu == -1)
			break; 
		switch (menu)
		{
		case 1: // students����ü�迭 ���
			printStudents(students, num_students);
			printf("\n");
			break;
		case 2: // students����ü�迭 ��賻��
			statisticsGPA(students, num_students);
			break;
		case 3: // stduents����ü�迭������ ���� �����̳��� �л��� �����л��� �������
			pST_GPA_max = searchBestGPAStudent(students, num_students);
			pST_GPA_min = searchWorstGPAStudent(students, num_students);
			printf("Student with best GPA : ");
			printStudent(pST_GPA_max);
			printf("\n");
			printf("Student with worst GPA : ");
			printStudent(pST_GPA_min);
			printf("\n");
			break;
		case 4: // students����ü�迭�� �й������� �������� �����ϱ�
			sortStudents_by_ST_ID(students, num_students);
			printf("After sorting students by increasing order of student ID:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 5: // students����ü�迭�� ���������� �������� �����ϱ�
			sortStudents_by_GPA(students, num_students);
			printf("After sorting students by decreasing order of GPA:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 6: // students����ü�迭�� �̸������� �������� �����ϱ�
			sortStudents_by_name(students, num_students);
			printf("After sorting students by increasing order of student name:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 7: // students����ü�迭�� ������ϼ����� �������� �����ϱ�
			sortStudents_by_BirthDate(students, num_students);
			printf("After sorting students by increasing order of student birth date : \n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 8:  // students����ü�迭�� ��ȭ��ȣ������ �������� �����ϱ�
			sortStudents_by_TelNumber(students, num_students);
			printf("After sorting students by increasing order of student's telephone number:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		default:
			break;
		} 
		shuffleStudents(students, num_students);	// students����ü�迭 ���� ����	
	} 
}