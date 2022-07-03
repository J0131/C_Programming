#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"
#define DAYS_PER_WEEK 7
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT }; // 요일을 나타내는 문자열
enum MONTH { JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, NUM_MONTHS }; // 월을 나타내는 문자열
const char* weekDayName[DAYS_PER_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday" }; // 요일을 나타내는 문자열
const char* weekDayNameShort[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };
const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December" };// 월을 나타내는 문자열

Date::Date()
{
	year = rand() % 1000 + 2000;
	month = rand() % 12 + 1;
	day = rand() % 31 + 1;
} // 생성자
// 초기화 기능 수행
Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}

// 클래스도 만든 객체가 소멸될때 실행
bool Date::isValidDate(int y, int m, int d)
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeapYear(y))
		days_month[2] = 29; // 만약 y가 윤년일경우 2월을 29일로 변경
	if ((m >= 1) && (m <= 12) && (d >= 1) && (d <= days_month[m]))
	{
		return true; // 월과 일의 범위가 일치할경우 true를 반환
	}
	else { // 범위가 맞지않을경우 false를 반환
		cout << "Illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}
void Date::setDate(int y, int m, int d)
{
	if (isValidDate(y, m, d)) // 받아온 날짜가 유효하면 받아온 날짜로 Date를 설정
	{
		year = y;
		month = m;
		day = d;
	}
	else { // 유효하지않을때 에러메세지 출력
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
		days_month[2] = 29; // 윤년일경우 2월의 일수를 29일로변경
	for (int m = 1; m < month; m++)
	{
		yearDay += days_month[m];
	} // 1월부터 month까지 그 달의 일수를 누적하여 더함
	yearDay += day; // 현재 day를 yearDay에 누적

	return yearDay;
}

int Date::getElapsedDays() // 인수가 전달되지않앗을때
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < year; y++) // year전까지 반복
	{
		if (isLeapYear(y))
			elpsDay += 366; // 윤년일경우 366일을 누적
		else
			elpsDay += 365; // 윤년이 아닐경우 365일을 누적
	}
	yearDay = getYearDay(); // 이번해의 일수를 계산
	elpsDay += yearDay; // elpsDay에 yearDay를 누적
	return elpsDay;
}

int Date::getWeekDay()
{
	int weekDay_AD010101 = MON; // 1년 1월 1일은 월요일
	int weekDay;
	int elapsedDays = 0;
	elapsedDays = getElapsedDays(); // 1년 1월 1일부터 현재까지 일수 계산
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7; // 1년 1월 1일이 월요일이므로 1을뺌 

	return weekDay;
}

bool Date::isLeapYear(int y)
{
	if ((((y % 4) == 0) && ((y % 100) != 0)) || ((y % 400) == 0)) // y가 4의 배수이면서 100의 배수는 아니거나 400의 배수일때 윤년이다
		return true;
	else
		return false;
}
bool Date::isLeapYear()
{
	return isLeapYear(year);
}

