#pragma once
#include <fstream>
#include <time.h>
#include <iomanip>
using namespace std;
class Date
{
	friend istream& operator>>(istream&, Date&);
	friend ostream& operator<<(ostream& fout, const Date& d)
	{
		fout.setf(ios::right);
		fout << d.year << "." <<setw(2)<< d.month << "." <<setw(2)<< d.day;
		return fout;
	}; // Date ��� ������ �����ε�
	friend class DateArray;
public:
	Date(); // �⺻������
	Date(int y, int m, int d); // ������
	void setDate(int newYear, int newMonth, int newDay);
	int getYear() const { return year; };
	int getYearDay();
	int getWeekDay();
	int getElapsedDays(); // 1��1��1�Ϻ����� �ϼ�
	const Date& operator=(const Date& rightSide)
	{
		year = rightSide.year;
		month = rightSide.month;
		day = rightSide.day;

		return *this;
	}; // Date ���Կ����� �����ε�
	bool operator>(const Date rightSide);
	bool operator<( Date rightSide)
	{
		if (this->getElapsedDays() < rightSide.getElapsedDays())
			return true;
		else
			return false;
	}; // Date �񱳿����� �����ε�
	bool operator==(const Date rightSide);
	bool isLeapYear(int y); // check whether the given year y is leap year
private:
	bool isLeapYear(); // check whether the year is leap year
	bool isValidDate(int y, int m, int d);
	int year; // ��
	int month; // ��
	int day; // ��
};
