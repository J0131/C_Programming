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
	}; // Date 출력 연산자 오버로딩
	friend class DateArray;
public:
	Date(); // 기본생성자
	Date(int y, int m, int d); // 생성자
	void setDate(int newYear, int newMonth, int newDay);
	int getYear() const { return year; };
	int getYearDay();
	int getWeekDay();
	int getElapsedDays(); // 1년1월1일부터의 일수
	const Date& operator=(const Date& rightSide)
	{
		year = rightSide.year;
		month = rightSide.month;
		day = rightSide.day;

		return *this;
	}; // Date 대입연산자 오버로딩
	bool operator>(const Date rightSide);
	bool operator<( Date rightSide)
	{
		if (this->getElapsedDays() < rightSide.getElapsedDays())
			return true;
		else
			return false;
	}; // Date 비교연산자 오버로딩
	bool operator==(const Date rightSide);
	bool isLeapYear(int y); // check whether the given year y is leap year
private:
	bool isLeapYear(); // check whether the year is leap year
	bool isValidDate(int y, int m, int d);
	int year; // 년
	int month; // 월
	int day; // 일
};
