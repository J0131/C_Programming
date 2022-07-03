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
}Tel_Number; // 전화번호를 가르키는 Tel_Number 구조체
typedef struct
{
	int year;
	int month;
	int day;
} Date; // 생년월일을 나타내는 Date 구조체
typedef struct
{
	int st_id;
	char name[MAX_NAME_LEN];
	Date birth_date;
	Tel_Number tel_number;
	double GPA;
} STUDENT; //학생의 정보를 나타내는 student구조체 선언

extern STUDENT students[NUM_STUDENTS]; // STUDENT 구조체형 배열 students선언

void selectionSortStudents_by_ST_ID(STUDENT students[], int num); // 학생의 학번으로 선택정렬하는 함수
void printTelephoneNumber(Tel_Number telNo); // 전화번호를 출력하는 함수
void printDate(Date date); // 날짜를 출력하는 함수
void printStudents(STUDENT* stArr, int num); // 학생의 정보를 화면에 출력하는함수
void printStudent(STUDENT* pST); // 여러학생의 정보를 화면에 출력하는 함수
void fprintDate(FILE* fout, Date date); // 날짜를 파일에 출력하는 함수
void fprintTelephoneNumber(FILE* fout, Tel_Number telNo); // 전화번호를 파일에 출력하는 함수
void fprintStudents(FILE* fout, STUDENT* stArr, int num); // 여러학생의 정보를 파일에 출력하는 함수