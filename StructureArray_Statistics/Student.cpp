#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Student.h"
#include "Date.h"
#include "Telephone_number.h"
void printStudent(Student* pST)
{
	printf("Student [ID: %08d, %-10s", pST->st_id, pST->name);  // �й�, �̸����
	printf(", GPA: %5.2lf", pST->GPA); // ���� ���
	printf(", ");
	printDate(pST->birth_date); // ������� ���
	printf(", ");
	printTelephoneNumber(pST->tel_number); // ��ȭ��ȣ ���
	printf("]");
}
void printStudents(Student* stArr, int num)
{
	Student* st = stArr; // student����ü������ ������ ����
	for (int i = 0; i < num; i++)
	{
		printStudent(st);// stArr�� ����ü�� ���
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
		st_2 = rand() % num_students; // ������ġ ����
		st_temp = stArray[st_1];
		stArray[st_1] = stArray[st_2];
		stArray[st_2] = st_temp; // stArray[st_1]�� stArray[st_2]�� ��°�� �ٲ��ش�
	}
}
void statisticsGPA(Student students[], int num_students)
{
	Student* pST, * pST_max, * pST_min; // stduent����ü �����ͷ� ����
	pST_max = pST_min = pST = students; // ������ ������ �������� ��� �ҷ��� students����ü �迭�� ������ش�
	double GPA_max, GPA_min, GPA_avg, GPA_sum = 0.0; // �ʱⰪ 0
	GPA_max = GPA_min = pST->GPA;// �ִ밪�� �ּҰ��� �ʱⰪ���� students����ü�迭�� ���������� ������ش�
	GPA_sum = pST->GPA; // ������ ���� �ʱⰪ���� students����ü�迭�� ���������� ������ش�
	for (int i = 1; i < num_students; i++) // �л��� ����ŭ �ݺ�
	{
		pST = &students[i];
		if (pST->GPA > GPA_max)
			GPA_max = pST->GPA; // pST->GPA�� GPA_max���� ũ�� GPA_MAX�� pST->GPA���ȴ�
		if (pST->GPA < GPA_min)
			GPA_min = pST->GPA; // pST->GPA�� GPA_min���� ������ GPA_min�� pST->GPA���ȴ�
		GPA_sum += pST->GPA; // GPA_sum�� pST->GPA���� �������ش�
	} 
	GPA_avg = GPA_sum / (double)num_students; // ����� ������ �հ迡 �л��� ���� ������ ���Ѵ�
	printf("GPA_max (%5.2lf), GPA_min (%5.2lf), GPA_avg (%5.2lf)\n",GPA_max, GPA_min, GPA_avg);
}
Student* searchBestGPAStudent(Student students[], int num)
{
	Student* pST, * pST_max;
	pST_max = pST = students;
	double GPA_max;
	GPA_max = pST->GPA; // �ּҰ��� �ʱⰪ���� students����ü�迭�� ���������� ������ش�
	for (int i = 1; i < num; i++)
	{
		pST = &students[i];
		if (pST->GPA > GPA_max)
		{
			GPA_max = pST->GPA; // pST->GPA�� GPA_max���� ũ�� GPA_MAX�� pST->GPA���ȴ�
			pST_max = pST; // ������ ���� �����л��϶��� pST�� pST_max�εд�
		} 
	}
	return pST_max; // pST_max����ȯ
}
Student* searchWorstGPAStudent(Student students[], int num)
{
	Student* pST, * pST_min;
	pST_min = pST = students;
	double GPA_min;
	GPA_min = pST->GPA; // �ִ밪�� �ʱⰪ���� students����ü�迭�� ���������� ������ش�
	for (int i = 1; i < num; i++)
	{
		pST = &students[i];
		if (pST->GPA < GPA_min)
		{
			GPA_min = pST->GPA; // pST->GPA�� GPA_min���� ������ GPA_min�� pST->GPA���ȴ�
			pST_min = pST; // ������ ���� �����л��϶��� pST�� pST_max�εд�
		}
	}
	return pST_min; // pST_max����ȯ
}
void sortStudents_by_GPA(Student students[], int num)
{
	Student* pST, * pST_max;
	Student temp; // ����ü�� �ӽ÷� �����ص� ����
	int st_max_id; // ������ ������� �л��� ����ü�迭��ġ
	for (int i = 0; i < num; i++) // 0���� num-1��ŭ �ݺ�
	{
		pST_max = pST = &students[i];
		st_max_id = i; // �ʱⰪ�� i�εд�
		for (int j = i + 1; j < num; j++) // i+1���� num-1��ŭ�ݺ�
		{
			pST = &students[j];
			if (pST->GPA > pST_max->GPA) 
			{
				pST_max = pST; // pST->GPA�� pST_max->GPA����ũ�� �׶��� pST�� pST_max�� �д�
				st_max_id = j; // ������ ������� �л��ǹ迭��ġ�� j�̴�
			}
		} 
		if (st_max_id != i) // st_max_id�� i�� �ƴϸ� students[i]�� students[st_max_id]�� �ٲ��ش�
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
	Student temp; // ����ü�� �ӽ÷� �����ص� ����
	int st_id_min; // �й��� �������� �л��� ����ü�迭��ġ
	for (int i = 0; i < num; i++) // 0���� num-1��ŭ �ݺ�
	{
		pST_min = pST = &students[i];
		st_id_min = i; // �ʱⰪ�� i�εд�
		for (int j = i + 1; j < num; j++) // i+1���� num-1��ŭ�ݺ�
		{
			pST = &students[j];
			if (pST->st_id < pST_min->st_id) 
			{
				pST_min = pST; // pST->st_id�� pST_min->st_id���������� �׶��� pST�� pST_min���� �д�
				st_id_min = j; // �й��� �������� �л��ǹ迭��ġ�� j�̴�
			}
		} 
		if (st_id_min != i) // st_id_min�� i�� �ƴϸ� students[i]�� students[st_id_min]�� �ٲ��ش�
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
	Student temp; // ����ü�� �ӽ÷� �����ص� ����
	int st_name_min; // �̸��� ������ ȯ�������� �������� �л��� ����ü�迭��ġ
	for (int i = 0; i < num; i++) // 0���� num-1��ŭ �ݺ�
	{
		pST_min = pST = &students[i];
		st_name_min = i;  // �ʱⰪ�� i�εд�
		for (int j = i + 1; j < num; j++) // i+1���� num-1��ŭ�ݺ�
		{
			pST = &students[j];
			if (strcmp(pST->name, pST_min->name) < 0)
			{
				pST_min = pST; // ���ڿ��� ���Ͽ� pST->name�� pST_min->name���������� �׶��� pST�� pST_min���� �д�
				st_name_min = j; // �̸����� �������� �л��ǹ迭��ġ�� j�̴�
			}
		} 
		if (st_name_min != i) //st_name_min�� i�� �ƴϸ� students[i]�� students[st_name_min]�� �ٲ��ش�
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
	Student temp; // ����ü�� �ӽ÷� �����ص� ����
	int st_date_min; // ��������� ������� �л��� ����ü�迭��ġ
	for (int i = 0; i < num; i++) // 0���� num-1��ŭ �ݺ�
	{
		pST_min = pST = &students[i];
		st_date_min = i; // �ʱⰪ�� i�εд�
		for (int j = i + 1; j < num; j++) // i+1���� num-1��ŭ�ݺ�
		{
			pST = &students[j];
			if (compareDate(pST->birth_date, pST_min->birth_date) < 0)
			{
				pST_min = pST; //��¥���Լ��� �̿��Ͽ� ���°��� 0���������� �׶��� pST�� pST_min���� �д�
				st_date_min = j; // ��������� ������� �л��ǹ迭��ġ�� j�̴�
			}
		}
		if (st_date_min != i) //st_date_min�� i�� �ƴϸ� students[i]�� students[st_date_min]�� �ٲ��ش�
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
	Student temp; // ����ü�� �ӽ÷� �����ص� ����
	int st_telno_min; // ��ȭ��ȣ�ǰ��� �������� �л��� ����ü�迭��ġ
	for (int i = 0; i < num; i++) // 0���� num-1��ŭ �ݺ�
	{
		pST_min = pST = &students[i];
		st_telno_min = i; // �ʱⰪ�� i�εд�
		for (int j = i + 1; j < num; j++) // i+1���� num-1��ŭ�ݺ�
		{
			pST = &students[j];
			if (compareTelNumber(pST->tel_number, pST_min->tel_number) < 0) 
			{ //��ȭ��ȣ ���Լ��� �̿��Ͽ� ���°��� 0���������� �׶��� pST�� pST_min���� �д�
				pST_min = pST;
				st_telno_min = j; // ��ȭ��ȣ���� �������� �л��ǹ迭��ġ�� j�̴�
			}
		}
		if (st_telno_min != i) //st_telno_min�� i�� �ƴϸ� students[i]�� students[st_telno_min]�� �ٲ��ش�
		{
			temp = students[i];
			students[i] = students[st_telno_min];
			students[st_telno_min] = temp;
		}
	}
}