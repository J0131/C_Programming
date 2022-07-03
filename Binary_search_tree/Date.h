/* Date.h */
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define WEEKDAY_AD01Jan01 MON // 1��1��1���� �����Ϸμ���
#define DAYS_PER_WEEK 7 // ������ �ϼ��� 7�Ϸ� ����
#define Secs_in_Minute 60
#define Secs_in_Hour (Secs_in_Minute * 60)
#define Secs_in_DAY (Secs_in_Hour * 24)
#define LOCAL_GMT_OFFSET_HOUR 9

class Date
{
	friend ostream& operator<<(ostream& fout, Date d)
	{
		fout << "(" << d.year << " , " << d.month << "," << d.day << ")";
		return fout;
	}
public:
	Date(); // �⺻ ������
	Date(int y, int m, int d); // ������
	~Date(); // �Ҹ���
	void inputDate(); // Date �Է��Ͽ� �����ϴ� �Լ�
	void fprintDate(ostream& fout); // Date ����ϴ� �Լ�
	void setDate(int y, int m, int dy); // Date �����ϴ� �Լ�
	void setRandDateAttributes(); // ����Date �����ϴ� �Լ�
	void setMonth(int m); // Date.month�����ϴ� �Լ�
	void setYear(int y); // Date.Year�����ϴ� �Լ�
	int getYear() { return year; } // Date.yaer �о���� �Լ�
	int getMonth() { return month; } // Date.month �о���� �Լ�
	int getDay() { return day; } // Date.day �о���� �Լ�
	int getYearDay(); //
	int getYearDay(int m, int d); // ������ ���糯¥������ �ϼ� 
	int getWeekDay(); // ���� ��¥�� ����
	int getElapsedDaysFromAD010101();
	int getElapsedDaysFromAD010101(Date); // 1�� 1�� 1�Ϻ��� ���糯¥������ �ϼ��� ����ϴ� �Լ�
	bool operator>=(Date& right) 
	{
		if (this->getElapsedDaysFromAD010101() >= right.getElapsedDaysFromAD010101())
			return 1;
		else 
			return 0;
	}
	bool operator<=(Date& right) 
	{
		if (this->getElapsedDaysFromAD010101() <= right.getElapsedDaysFromAD010101())
			return 1;
		else
			return 0;
	}
	bool operator>(Date& right)
	{
		if (this->getElapsedDaysFromAD010101() > right.getElapsedDaysFromAD010101())
			return 1;
		else
			return 0;
	}
	bool operator<(Date& right)
	{
		if (this->getElapsedDaysFromAD010101() < right.getElapsedDaysFromAD010101())
			return 1;
		else
			return 0;
	}
	bool operator==(Date& right)
	{
		if (this->getElapsedDaysFromAD010101() == right.getElapsedDaysFromAD010101())
			return 1;
		else
			return 0;
	}
private:
	bool isLeapYear(); // 
	bool isLeapYear(int y); // y�� �������� �ƴ��� Ȯ���ϴ� �Լ�
	bool isValidDate(int y, int m, int d); // ��¥�� ��ȿ���� �ƴ��� Ȯ���ϴ� �Լ�
	int year;
	int month;
	int day; // ������ ���
};
#endif 

