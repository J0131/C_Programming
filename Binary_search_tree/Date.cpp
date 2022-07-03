#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"

enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT }; // ������ ��Ÿ���� ���ڿ�
enum MONTH { JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, NUM_MONTHS }; // ���� ��Ÿ���� ���ڿ�
const char* weekDayName[DAYS_PER_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday" }; // ������ ��Ÿ���� ���ڿ�
const char* weekDayNameShort[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };
const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December" };// ���� ��Ÿ���� ���ڿ�


Date::Date()
{
	year = 0;
	month = 0;
	day = 0;
} // ������
// �ʱ�ȭ ��� ����
Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}
Date::~Date()
{
	cout << "Date object instance is destructed" << endl;
} // �Ҹ���
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
void Date::setRandDateAttributes()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	year = rand() % 2000 + 1000; // 1000����� 2999����� �������� ����
	month = rand() % 12 + 1; // 1������ 12������ �������� ����
	if (isLeapYear(year) && month == 2)
		days_month[2] = 29; // ���� year�� �����̰� month�� 2�ϰ�� 2���� �ϼ��� 29�� ����
	day = rand() % days_month[month] + 1; // 1�Ϻ��� �� ���� �ִ��ϼ����� �������� ����
}

void Date::setMonth(int newMonth)
{
	if ((newMonth >= 1) && (newMonth <= 12))
		month = newMonth; // ���ο� ���� month�� ����
	else
	{
		cout << "Illegal month value! Program aborted.\n";
		exit(1);
	}
	day = 1;
}
void Date::setYear(int y)
{
	year = y; // year�� y�� ����
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
int Date::getYearDay(int month, int day)
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;
	for (int m = 1; m < month; m++)
	{
		yearDay += days_month[m];
	}
	yearDay += day;
	if ((month > 2) && isLeapYear(year))
		yearDay += 1; // �����ϰ�� 1���� yearDay�� ����
	return yearDay;
}

int Date::getElapsedDaysFromAD010101() // �μ��� ���޵����ʾ�����
{
	int elpsDay = 0;
	elpsDay = getElapsedDaysFromAD010101(*this); // �ڱ��ڽ��� �μ��� ����
	return elpsDay;
}
int Date::getElapsedDaysFromAD010101(Date d)
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < d.year; y++) // year������ �ݺ�
	{
		if (isLeapYear(y))
			elpsDay += 366; // �����ϰ�� 366���� ����
		else
			elpsDay += 365; // ������ �ƴҰ�� 365���� ����
	}
	yearDay = getYearDay(d.month, d.day); // �̹����� �ϼ��� ���
	elpsDay += yearDay; // elpsDay�� yearDay�� ����
	return elpsDay;
}

int Date::getWeekDay()
{
	int weekDay_AD010101 = MON; // 1�� 1�� 1���� ������
	int weekDay;
	int elapsedDays = 0;
	elapsedDays = getElapsedDaysFromAD010101(); // 1�� 1�� 1�Ϻ��� ������� �ϼ� ���
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7; // 1�� 1�� 1���� �������̹Ƿ� 1���� 

	return weekDay;
}
void Date::inputDate()
{
	int y, m, d;
	cout << "Enter date in year month day : ";
	cin >> y >> m >> d; // �Է¹޾� y,m,d �� ����
	if (isValidDate(y, m, d)) // ��ȿ�� ��¥�̸� ����
	{
		year = y;
		month = m;
		day = d;
	}
	else {
		cout << "Ilegal date! Program aborted.\n";
		exit(1);
	}
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
void Date::fprintDate(ostream& fout)
{
	const char* weekDayName[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday","Saturday" };
	const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July","August", "September", "October", "November", "December" };
	int yearDay = 0;
	int weekDay;
	if ((month >= 1) && (month <= 12))
		fout << setw(10) << string(monthName[month]); // monthName[month]�� �ش��ϴ� ���ڿ� ���
	fout << " " << setw(2) << day << ", " << setw(4) << year; // year�� day�� ���
	yearDay = getYearDay();
	weekDay = getWeekDay();
	fout << " (" << setw(10) << string(weekDayName[weekDay]) << ")"; // ������ ���
}

/*void Date::fprintCalendar_Month(ostream& fout)
{
	cout << "           " << month << endl;
	cout << "=====================" << endl;
	cout << "�� �� ȭ �� �� �� ��" << endl;
	cout << "=====================" << endl;
	if

}*/

