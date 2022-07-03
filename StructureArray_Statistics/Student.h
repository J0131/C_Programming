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
} Student; // student구조체 선언
// 자기참조구조체

void printStudent(Student* pST); // student구조체 출력하는함수
void printStudents(Student* stArr, int num_students); // student 구조체 배열 출력하는함수
void shuffleStudents(Student students[], int num_students); // student구조체배열을 섞어주는 함수
void statisticsGPA(Student students[], int num_students); // student구조체배열의 통계를 내는 함수
Student* searchBestGPAStudent(Student students[], int num); // stduent구조체배열내에서 성적이가장 높은 학생을 찾는함수
Student* searchWorstGPAStudent(Student students[], int num); // stduent구조체배열내에서 성적이가장 낮은 학생을 찾는함수
void sortStudents_by_GPA(Student students[], int num); // student구조체배열을 성적순으로 정렬하는 함수
void sortStudents_by_ST_ID(Student students[], int num); // student구조체배열을 학번순으로 정렬하는 함수
void sortStudents_by_name(Student students[], int num); // student구조체배열을 이름순으로 정렬하는 함수
void sortStudents_by_BirthDate(Student students[], int num); // student구조체배열을 생년월일순으로 정렬하는 함수
void sortStudents_by_TelNumber(Student students[], int num); // student구조체배열을 전화번호순으로 정렬하는 함수
#endif