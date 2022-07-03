#ifndef DATE_H
#define DATE_H
typedef struct
{
	int year;
	int month;
	int day;
} Date; // Date구조체 선언
void printDate(Date date); // Date구조체 출력하는 함수
int compareDate(Date d1, Date d2); // Date구조체를 비교하는 함수
#endif