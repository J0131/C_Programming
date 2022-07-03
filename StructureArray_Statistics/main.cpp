/************************************
* 파일목적 : 학생의 정보를 구조체를 통해 나타내고 여러 학생들의 정보를 구조체배열에 저장하여 정렬하는 프로그램
* 작성자 : 최범준
* Final update : 2020-05-28
*************************************/

#include <stdio.h>
#include "Student.h"
#define MAX_NUM_STUDENTS 100
void main()
{
	int num_students = 0; // 학생의 수를 선언하고 0으로초기화
	int menu;
	Student* pST_GPA_max, * pST_GPA_min; // 구조체 포인터 선언
	extern Student students[]; // 외부에서 선언한 student구조체 배열 불러오기
	for (int i = 0; i < MAX_NUM_STUDENTS; i++)
	{
		if (students[i].st_id == -1)
			break; // students[]구조체 배열을 차례로 읽고 학번이 -1이되면 반복문 나가기
		else
			num_students++; // 학생수 1증가
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
		scanf("%d", &menu); // 버퍼를 사용해서 값을 입력받은뒤 menu에 저장
		if (menu == -1)
			break; 
		switch (menu)
		{
		case 1: // students구조체배열 출력
			printStudents(students, num_students);
			printf("\n");
			break;
		case 2: // students구조체배열 통계내기
			statisticsGPA(students, num_students);
			break;
		case 3: // stduents구조체배열내에서 가장 성적이높은 학생과 낮은학생의 정보출력
			pST_GPA_max = searchBestGPAStudent(students, num_students);
			pST_GPA_min = searchWorstGPAStudent(students, num_students);
			printf("Student with best GPA : ");
			printStudent(pST_GPA_max);
			printf("\n");
			printf("Student with worst GPA : ");
			printStudent(pST_GPA_min);
			printf("\n");
			break;
		case 4: // students구조체배열을 학번순으로 오름차순 정렬하기
			sortStudents_by_ST_ID(students, num_students);
			printf("After sorting students by increasing order of student ID:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 5: // students구조체배열을 성적순으로 내림차순 정렬하기
			sortStudents_by_GPA(students, num_students);
			printf("After sorting students by decreasing order of GPA:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 6: // students구조체배열을 이름순으로 오름차순 정렬하기
			sortStudents_by_name(students, num_students);
			printf("After sorting students by increasing order of student name:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 7: // students구조체배열을 생년월일순으로 오름차순 정렬하기
			sortStudents_by_BirthDate(students, num_students);
			printf("After sorting students by increasing order of student birth date : \n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 8:  // students구조체배열을 전화번호순으로 오름차순 정렬하기
			sortStudents_by_TelNumber(students, num_students);
			printf("After sorting students by increasing order of student's telephone number:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		default:
			break;
		} 
		shuffleStudents(students, num_students);	// students구조체배열 순서 섞기	
	} 
}