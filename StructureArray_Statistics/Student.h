#ifndef STUDENT_H
#define STUDENT_H
#include "Date.h"
#include "Telephone_number.h"
#define MAX_NAME_LEN 20
#define NUM_STUDENTS 10
typedef struct
{
	int st_id;
	char name[MAX_NAME_LEN];
	Date birth_date;
	Tel_Number tel_number;
	double GPA; 
} Student; // student����ü ����
// �ڱ���������ü

void printStudent(Student* pST); // student����ü ����ϴ��Լ�
void printStudents(Student* stArr, int num_students); // student ����ü �迭 ����ϴ��Լ�
void shuffleStudents(Student students[], int num_students); // student����ü�迭�� �����ִ� �Լ�
void statisticsGPA(Student students[], int num_students); // student����ü�迭�� ��踦 ���� �Լ�
Student* searchBestGPAStudent(Student students[], int num); // stduent����ü�迭������ �����̰��� ���� �л��� ã���Լ�
Student* searchWorstGPAStudent(Student students[], int num); // stduent����ü�迭������ �����̰��� ���� �л��� ã���Լ�
void sortStudents_by_GPA(Student students[], int num); // student����ü�迭�� ���������� �����ϴ� �Լ�
void sortStudents_by_ST_ID(Student students[], int num); // student����ü�迭�� �й������� �����ϴ� �Լ�
void sortStudents_by_name(Student students[], int num); // student����ü�迭�� �̸������� �����ϴ� �Լ�
void sortStudents_by_BirthDate(Student students[], int num); // student����ü�迭�� ������ϼ����� �����ϴ� �Լ�
void sortStudents_by_TelNumber(Student students[], int num); // student����ü�迭�� ��ȭ��ȣ������ �����ϴ� �Լ�
#endif