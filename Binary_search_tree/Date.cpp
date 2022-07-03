#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"

enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT }; // 요일을 나타내는 문자열
enum MONTH { JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, NUM_MONTHS }; // 월을 나타내는 문자열
const char* weekDayName[DAYS_PER_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday" }; // 요일을 나타내는 문자열
const char* weekDayNameShort[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };
const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December" };// 월을 나타내는 문자열


Date::Date()
{
	year = 0;
	month = 0;
	day = 0;
} // 생성자
// 초기화 기능 수행
Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}
Date::~Date()
{
	cout << "Date object instance is destructed" << endl;
} // 소멸자
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
void Date::setRandDateAttributes()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	year = rand() % 2000 + 1000; // 1000년부터 2999년까지 랜덤으로 생성
	month = rand() % 12 + 1; // 1월부터 12월까지 랜덤으로 생성
	if (isLeapYear(year) && month == 2)
		days_month[2] = 29; // 만일 year이 윤년이고 month가 2일경우 2월의 일수를 29로 변경
	day = rand() % days_month[month] + 1; // 1일부터 그 달의 최대일수까지 랜덤으로 생성
}

void Date::setMonth(int newMonth)
{
	if ((newMonth >= 1) && (newMonth <= 12))
		month = newMonth; // 새로운 월을 month로 설정
	else
	{
		cout << "Illegal month value! Program aborted.\n";
		exit(1);
	}
	day = 1;
}
void Date::setYear(int y)
{
	year = y; // year을 y로 설정
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
		yearDay += 1; // 윤년일경우 1일을 yearDay에 더함
	return yearDay;
}

int Date::getElapsedDaysFromAD010101() // 인수가 전달되지않앗을때
{
	int elpsDay = 0;
	elpsDay = getElapsedDaysFromAD010101(*this); // 자기자신을 인수로 전달
	return elpsDay;
}
int Date::getElapsedDaysFromAD010101(Date d)
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < d.year; y++) // year전까지 반복
	{
		if (isLeapYear(y))
			elpsDay += 366; // 윤년일경우 366일을 누적
		else
			elpsDay += 365; // 윤년이 아닐경우 365일을 누적
	}
	yearDay = getYearDay(d.month, d.day); // 이번해의 일수를 계산
	elpsDay += yearDay; // elpsDay에 yearDay를 누적
	return elpsDay;
}

int Date::getWeekDay()
{
	int weekDay_AD010101 = MON; // 1년 1월 1일은 월요일
	int weekDay;
	int elapsedDays = 0;
	elapsedDays = getElapsedDaysFromAD010101(); // 1년 1월 1일부터 현재까지 일수 계산
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7; // 1년 1월 1일이 월요일이므로 1을뺌 

	return weekDay;
}
void Date::inputDate()
{
	int y, m, d;
	cout << "Enter date in year month day : ";
	cin >> y >> m >> d; // 입력받아 y,m,d 에 저장
	if (isValidDate(y, m, d)) // 유효한 날짜이면 설정
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
	if ((((y % 4) == 0) && ((y % 100) != 0)) || ((y % 400) == 0)) // y가 4의 배수이면서 100의 배수는 아니거나 400의 배수일때 윤년이다
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
		fout << setw(10) << string(monthName[month]); // monthName[month]에 해당하는 문자열 출력
	fout << " " << setw(2) << day << ", " << setw(4) << year; // year과 day를 출력
	yearDay = getYearDay();
	weekDay = getWeekDay();
	fout << " (" << setw(10) << string(weekDayName[weekDay]) << ")"; // 요일을 출력
}

/*void Date::fprintCalendar_Month(ostream& fout)
{
	cout << "           " << month << endl;
	cout << "=====================" << endl;
	cout << "일 월 화 수 목 금 토" << endl;
	cout << "=====================" << endl;
	if

}*/


