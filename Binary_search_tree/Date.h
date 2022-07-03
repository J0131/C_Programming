/* Date.h */
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define WEEKDAY_AD01Jan01 MON // 1년1월1일을 월요일로설정
#define DAYS_PER_WEEK 7 // 한주의 일수를 7일로 설정
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
	Date(); // 기본 생성자
	Date(int y, int m, int d); // 생성자
	~Date(); // 소멸자
	void inputDate(); // Date 입력하여 설정하는 함수
	void fprintDate(ostream& fout); // Date 출력하는 함수
	void setDate(int y, int m, int dy); // Date 설정하는 함수
	void setRandDateAttributes(); // 랜덤Date 설정하는 함수
	void setMonth(int m); // Date.month설정하는 함수
	void setYear(int y); // Date.Year설정하는 함수
	int getYear() { return year; } // Date.yaer 읽어오는 함수
	int getMonth() { return month; } // Date.month 읽어오는 함수
	int getDay() { return day; } // Date.day 읽어오는 함수
	int getYearDay(); //
	int getYearDay(int m, int d); // 올해의 현재날짜까지의 일수 
	int getWeekDay(); // 현재 날짜의 요일
	int getElapsedDaysFromAD010101();
	int getElapsedDaysFromAD010101(Date); // 1년 1월 1일부터 현재날짜까지의 일수를 계산하는 함수
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
	bool isLeapYear(int y); // y가 윤년인지 아닌지 확인하는 함수
	bool isValidDate(int y, int m, int d); // 날짜가 유효한지 아닌지 확인하는 함수
	int year;
	int month;
	int day; // 데이터 멤버
};
#endif 

