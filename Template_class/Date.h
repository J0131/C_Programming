#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Date
{
	friend istream& operator>>(istream&, const Date&);
	friend ostream& operator<<(ostream&, Date&); // 출력연산자
public:
	Date(); //
	Date(int y, int m, int d); // 생성자
	void setDate(int newYear, int newMonth, int newDay); // 날짜설정
	int getYear() { return year; }
	int getYearDay();
	int getWeekDay();
	int getElapsedDays(); // 1년1월1일부터 현재까지의일수
	const Date operator=(const Date& rightSide); // 대입연산자
	bool operator>(Date& rightSide);
	bool operator>=(Date& rightSide);
	bool operator<(Date& rightSide);
	bool operator<=(Date& rightSide);
	bool operator==(Date& rightSide);
	bool operator!=(Date& rightSide);
	bool isLeapYear(int y); // 윤년확인 
private:
	bool isLeapYear(); // 
	bool isValidDate(int y, int m, int d); // 유효한 날짜인지 확인
	int year;
	int month;
	int day;
};
