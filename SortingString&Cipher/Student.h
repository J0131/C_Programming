#include <stdio.h>
#define MAX_NAME_LEN 20
#define NUM_STUDENTS 10
#define MAX_STRING_LEN 512

typedef struct
{
	unsigned short nation_code;
	unsigned short region_no;
	unsigned short switch_no;
	unsigned short line_no;
}Tel_Number; // ��ȭ��ȣ�� ����Ű�� Tel_Number ����ü
typedef struct
{
	int year;
	int month;
	int day;
} Date; // ��������� ��Ÿ���� Date ����ü
typedef struct
{
	int st_id;
	char name[MAX_NAME_LEN];
	Date birth_date;
	Tel_Number tel_number;
	double GPA;
} STUDENT; //�л��� ������ ��Ÿ���� student����ü ����

extern STUDENT students[NUM_STUDENTS]; // STUDENT ����ü�� �迭 students����

void selectionSortStudents_by_ST_ID(STUDENT students[], int num); // �л��� �й����� ���������ϴ� �Լ�
void printTelephoneNumber(Tel_Number telNo); // ��ȭ��ȣ�� ����ϴ� �Լ�
void printDate(Date date); // ��¥�� ����ϴ� �Լ�
void printStudents(STUDENT* stArr, int num); // �л��� ������ ȭ�鿡 ����ϴ��Լ�
void printStudent(STUDENT* pST); // �����л��� ������ ȭ�鿡 ����ϴ� �Լ�
void fprintDate(FILE* fout, Date date); // ��¥�� ���Ͽ� ����ϴ� �Լ�
void fprintTelephoneNumber(FILE* fout, Tel_Number telNo); // ��ȭ��ȣ�� ���Ͽ� ����ϴ� �Լ�
void fprintStudents(FILE* fout, STUDENT* stArr, int num); // �����л��� ������ ���Ͽ� ����ϴ� �Լ�