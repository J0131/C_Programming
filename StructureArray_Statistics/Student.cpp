#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Student.h"
#include "Date.h"
#include "Telephone_number.h"
void printStudent(Student* pST)
{
	printf("Student [ID: %08d, %-10s", pST->st_id, pST->name);  // 학번, 이름출력
	printf(", GPA: %5.2lf", pST->GPA); // 성적 출력
	printf(", ");
	printDate(pST->birth_date); // 생년월일 출력
	printf(", ");
	printTelephoneNumber(pST->tel_number); // 전화번호 출력
	printf("]");
}
void printStudents(Student* stArr, int num)
{
	Student* st = stArr; // student구조체형식의 포인터 선언
	for (int i = 0; i < num; i++)
	{
		printStudent(st);// stArr의 구조체를 출력
		printf("\n");
		st++;
	}
}
void shuffleStudents(Student stArray[], int num_students)
{
	int st_1, st_2;
	Student st_temp;
	srand(time(0));
	for (int i = 0; i < num_students; i++)
	{
		st_1 = rand() % num_students;
		st_2 = rand() % num_students; // 랜덤위치 생성
		st_temp = stArray[st_1];
		stArray[st_1] = stArray[st_2];
		stArray[st_2] = st_temp; // stArray[st_1]과 stArray[st_2]를 통째로 바꿔준다
	}
}
void statisticsGPA(Student students[], int num_students)
{
	Student* pST, * pST_max, * pST_min; // stduent구조체 포인터로 선언
	pST_max = pST_min = pST = students; // 위에서 선언한 변수들을 모두 불러온 students구조체 배열로 만들어준다
	double GPA_max, GPA_min, GPA_avg, GPA_sum = 0.0; // 초기값 0
	GPA_max = GPA_min = pST->GPA;// 최대값과 최소값을 초기값으로 students구조체배열의 성적값으로 만들어준다
	GPA_sum = pST->GPA; // 성적의 합을 초기값으로 students구조체배열의 성적값으로 만들어준다
	for (int i = 1; i < num_students; i++) // 학생의 수만큼 반복
	{
		pST = &students[i];
		if (pST->GPA > GPA_max)
			GPA_max = pST->GPA; // pST->GPA가 GPA_max보다 크면 GPA_MAX는 pST->GPA가된다
		if (pST->GPA < GPA_min)
			GPA_min = pST->GPA; // pST->GPA가 GPA_min보다 작으면 GPA_min은 pST->GPA가된다
		GPA_sum += pST->GPA; // GPA_sum에 pST->GPA값을 누적해준다
	} 
	GPA_avg = GPA_sum / (double)num_students; // 평균은 성적의 합계에 학생의 수를 나누어 구한다
	printf("GPA_max (%5.2lf), GPA_min (%5.2lf), GPA_avg (%5.2lf)\n",GPA_max, GPA_min, GPA_avg);
}
Student* searchBestGPAStudent(Student students[], int num)
{
	Student* pST, * pST_max;
	pST_max = pST = students;
	double GPA_max;
	GPA_max = pST->GPA; // 최소값을 초기값으로 students구조체배열의 성적값으로 만들어준다
	for (int i = 1; i < num; i++)
	{
		pST = &students[i];
		if (pST->GPA > GPA_max)
		{
			GPA_max = pST->GPA; // pST->GPA가 GPA_max보다 크면 GPA_MAX는 pST->GPA가된다
			pST_max = pST; // 성적이 가장 높은학생일때의 pST를 pST_max로둔다
		} 
	}
	return pST_max; // pST_max값반환
}
Student* searchWorstGPAStudent(Student students[], int num)
{
	Student* pST, * pST_min;
	pST_min = pST = students;
	double GPA_min;
	GPA_min = pST->GPA; // 최대값을 초기값으로 students구조체배열의 성적값으로 만들어준다
	for (int i = 1; i < num; i++)
	{
		pST = &students[i];
		if (pST->GPA < GPA_min)
		{
			GPA_min = pST->GPA; // pST->GPA가 GPA_min보다 작으면 GPA_min은 pST->GPA가된다
			pST_min = pST; // 성적이 가장 낮은학생일때의 pST를 pST_max로둔다
		}
	}
	return pST_min; // pST_max값반환
}
void sortStudents_by_GPA(Student students[], int num)
{
	Student* pST, * pST_max;
	Student temp; // 구조체를 임시로 저장해둘 변수
	int st_max_id; // 성적이 가장높은 학생의 구조체배열위치
	for (int i = 0; i < num; i++) // 0에서 num-1만큼 반복
	{
		pST_max = pST = &students[i];
		st_max_id = i; // 초기값을 i로둔다
		for (int j = i + 1; j < num; j++) // i+1에서 num-1만큼반복
		{
			pST = &students[j];
			if (pST->GPA > pST_max->GPA) 
			{
				pST_max = pST; // pST->GPA가 pST_max->GPA보다크면 그때의 pST를 pST_max로 둔다
				st_max_id = j; // 성적이 가장높은 학생의배열위치는 j이다
			}
		} 
		if (st_max_id != i) // st_max_id가 i가 아니면 students[i]와 students[st_max_id]를 바꿔준다
		{
			temp = students[i];
			students[i] = students[st_max_id];
			students[st_max_id] = temp;
		}
	}
}
void sortStudents_by_ST_ID(Student students[], int num)
{
	Student* pST, * pST_min;
	Student temp; // 구조체를 임시로 저장해둘 변수
	int st_id_min; // 학번이 가장작은 학생의 구조체배열위치
	for (int i = 0; i < num; i++) // 0에서 num-1만큼 반복
	{
		pST_min = pST = &students[i];
		st_id_min = i; // 초기값을 i로둔다
		for (int j = i + 1; j < num; j++) // i+1에서 num-1만큼반복
		{
			pST = &students[j];
			if (pST->st_id < pST_min->st_id) 
			{
				pST_min = pST; // pST->st_id가 pST_min->st_id보다작으면 그때의 pST를 pST_min으로 둔다
				st_id_min = j; // 학번이 가장작은 학생의배열위치는 j이다
			}
		} 
		if (st_id_min != i) // st_id_min이 i가 아니면 students[i]와 students[st_id_min]를 바꿔준다
		{
			temp = students[i];
			students[i] = students[st_id_min];
			students[st_id_min] = temp;
		}
	}
}
void sortStudents_by_name(Student students[], int num)
{
	Student* pST, * pST_min;
	Student temp; // 구조체를 임시로 저장해둘 변수
	int st_name_min; // 이름을 값으로 환산했을때 가장작은 학생의 구조체배열위치
	for (int i = 0; i < num; i++) // 0에서 num-1만큼 반복
	{
		pST_min = pST = &students[i];
		st_name_min = i;  // 초기값을 i로둔다
		for (int j = i + 1; j < num; j++) // i+1에서 num-1만큼반복
		{
			pST = &students[j];
			if (strcmp(pST->name, pST_min->name) < 0)
			{
				pST_min = pST; // 문자열을 비교하여 pST->name이 pST_min->name보다작으면 그때의 pST를 pST_min으로 둔다
				st_name_min = j; // 이름값이 가장작은 학생의배열위치는 j이다
			}
		} 
		if (st_name_min != i) //st_name_min이 i가 아니면 students[i]와 students[st_name_min]를 바꿔준다
		{
			temp = students[i];
			students[i] = students[st_name_min];
			students[st_name_min] = temp;
		}
	} 
}
void sortStudents_by_BirthDate(Student students[], int num)
{
	Student* pST, * pST_min;
	Student temp; // 구조체를 임시로 저장해둘 변수
	int st_date_min; // 생년월일이 가장빠른 학생의 구조체배열위치
	for (int i = 0; i < num; i++) // 0에서 num-1만큼 반복
	{
		pST_min = pST = &students[i];
		st_date_min = i; // 초기값을 i로둔다
		for (int j = i + 1; j < num; j++) // i+1에서 num-1만큼반복
		{
			pST = &students[j];
			if (compareDate(pST->birth_date, pST_min->birth_date) < 0)
			{
				pST_min = pST; //날짜비교함수를 이용하여 나온값이 0보다작으면 그때의 pST를 pST_min으로 둔다
				st_date_min = j; // 생년월일이 가장빠른 학생의배열위치는 j이다
			}
		}
		if (st_date_min != i) //st_date_min이 i가 아니면 students[i]와 students[st_date_min]를 바꿔준다
		{
			temp = students[i];
			students[i] = students[st_date_min];
			students[st_date_min] = temp;
		}
	}
}
void sortStudents_by_TelNumber(Student students[], int num)
{
	Student* pST, * pST_min;
	Student temp; // 구조체를 임시로 저장해둘 변수
	int st_telno_min; // 전화번호의값이 가장작은 학생의 구조체배열위치
	for (int i = 0; i < num; i++) // 0에서 num-1만큼 반복
	{
		pST_min = pST = &students[i];
		st_telno_min = i; // 초기값을 i로둔다
		for (int j = i + 1; j < num; j++) // i+1에서 num-1만큼반복
		{
			pST = &students[j];
			if (compareTelNumber(pST->tel_number, pST_min->tel_number) < 0) 
			{ //전화번호 비교함수를 이용하여 나온값이 0보다작으면 그때의 pST를 pST_min으로 둔다
				pST_min = pST;
				st_telno_min = j; // 전화번호값이 가장작은 학생의배열위치는 j이다
			}
		}
		if (st_telno_min != i) //st_telno_min이 i가 아니면 students[i]와 students[st_telno_min]를 바꿔준다
		{
			temp = students[i];
			students[i] = students[st_telno_min];
			students[st_telno_min] = temp;
		}
	}
}