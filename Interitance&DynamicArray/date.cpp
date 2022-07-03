#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"
#define DAYS_PER_WEEK 7
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT }; // ������ ��Ÿ���� ���ڿ�
enum MONTH { JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, NUM_MONTHS }; // ���� ��Ÿ���� ���ڿ�
const char* weekDayName[DAYS_PER_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday" }; // ������ ��Ÿ���� ���ڿ�
const char* weekDayNameShort[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };
const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December" };// ���� ��Ÿ���� ���ڿ�

Date::Date()
{
	year = rand() % 1000 + 2000;
	month = rand() % 12 + 1;
	day = rand() % 31 + 1;
} // ������
// �ʱ�ȭ ��� ����
Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}

// Ŭ������ ���� ��ü�� �Ҹ�ɶ� ����
bool Date::isValidDate(int y, int m, int d)
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeapYear(y))
		days_month[2] = 29; // ���� y�� �����ϰ�� 2���� 29�Ϸ� ����
	if ((m >= 1) && (m <= 12) && (d >= 1) && (d <= days_month[m]))
	{
		return true; // ���� ���� ������ ��ġ�Ұ�� true�� ��ȯ
	}
	else { // ������ ����������� false�� ��ȯ
		cout << "Illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}
void Date::setDate(int y, int m, int d)
{
	if (isValidDate(y, m, d)) // �޾ƿ� ��¥�� ��ȿ�ϸ� �޾ƿ� ��¥�� Date�� ����
	{
		year = y;
		month = m;
		day = d;
	}
	else { // ��ȿ���������� �����޼��� ���
		cout << "Invalid date (" << y << ", " << m << ", " << d << ")";
		cout << " Program aborted !!\n";
		exit(1);
	}
}

int Date::getYearDay()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;
	if (isLeapYear())
		days_month[2] = 29; // �����ϰ�� 2���� �ϼ��� 29�Ϸκ���
	for (int m = 1; m < month; m++)
	{
		yearDay += days_month[m];
	} // 1������ month���� �� ���� �ϼ��� �����Ͽ� ����
	yearDay += day; // ���� day�� yearDay�� ����

	return yearDay;
}

int Date::getElapsedDays() // �μ��� ���޵����ʾ�����
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < year; y++) // year������ �ݺ�
	{
		if (isLeapYear(y))
			elpsDay += 366; // �����ϰ�� 366���� ����
		else
			elpsDay += 365; // ������ �ƴҰ�� 365���� ����
	}
	yearDay = getYearDay(); // �̹����� �ϼ��� ���
	elpsDay += yearDay; // elpsDay�� yearDay�� ����
	return elpsDay;
}

int Date::getWeekDay()
{
	int weekDay_AD010101 = MON; // 1�� 1�� 1���� ������
	int weekDay;
	int elapsedDays = 0;
	elapsedDays = getElapsedDays(); // 1�� 1�� 1�Ϻ��� ������� �ϼ� ���
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7; // 1�� 1�� 1���� �������̹Ƿ� 1���� 

	return weekDay;
}

bool Date::isLeapYear(int y)
{
	if ((((y % 4) == 0) && ((y % 100) != 0)) || ((y % 400) == 0)) // y�� 4�� ����̸鼭 100�� ����� �ƴϰų� 400�� ����϶� �����̴�
		return true;
	else
		return false;
}
bool Date::isLeapYear()
{
	return isLeapYear(year);
}

