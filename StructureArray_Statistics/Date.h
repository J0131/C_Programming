#ifndef DATE_H
#define DATE_H
typedef struct
{
	int year;
	int month;
	int day;
} Date; // Date����ü ����
void printDate(Date date); // Date����ü ����ϴ� �Լ�
int compareDate(Date d1, Date d2); // Date����ü�� ���ϴ� �Լ�
#endif