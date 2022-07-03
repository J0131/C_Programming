#include <stdio.h>
#include "Date.h"
void printDate(Date date)
{
	printf("(%04d, %2d, %2d)",
		date.year, date.month, date.day);
} // year-month-day ������ ���
int compareDate(Date d1, Date d2)
{
	if (d1.year > d2.year)
		return 1; // �� ����ü�� year�� ���Ͽ� d1>d2�̸� 1�� ��ȯ, d1<d2�̸� -1�� ��ȯ
	else if (d1.year < d2.year)
		return -1;
	else if (d1.month > d2.month) // year�� ������� month�� ��
		return 1;
	else if (d1.month < d2.month)
		return -1; // month�� ���Ͽ� d1>d2�̸� 1�� ��ȯ, d1<d2�̸� -1�� ��ȯ
	else if (d1.day > d2.day) // month�� ������� day�� ��
		return 1;
	else if (d1.day < d2.day)
		return -1;  // day�� ���Ͽ� d1 > d2�̸� 1�� ��ȯ, d1 < d2�̸� - 1�� ��ȯ
    else
		return 0; // year,month,day�� ��ΰ������ 0�� ��ȯ
}