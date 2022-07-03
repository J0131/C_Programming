#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class Time
{
	friend ostream& operator<<(ostream&,Time&); // 출력연산자
public:
	Time(); // 
	Time(int h, int m, int s); // 생성자
	Time& operator+(int s); // 덧셈연산자
	int elasedSec();
	Time getTime();
	bool operator<(Time&);
	bool operator<=(Time&);
	bool operator>(Time&);
	bool operator>=(Time&);
	bool operator==(Time&); // 비교연산자
private:
	bool isValidTime(int, int, int); // 유효한 시간인지 확인
	int hour;
	int min;
	int sec;
};
