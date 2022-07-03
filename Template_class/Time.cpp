#include "Time.h"

ostream& operator<<(ostream& fout, Time& t)
{
	fout <<"( " << setw(2) << t.hour << ":" << setw(2) << t.min << ":" << setw(2) << t.sec << ")";
	return fout;
} // 출력연산자 오버로딩
Time::Time()
{
	hour = 0;
	min = 0;
	sec = 0;
} // 기본생성자
Time::Time(int h, int m, int s)
{
	hour = h;
	min = m;
	sec = s;
} // 생성자
Time& Time::operator+(int s)
{
	sec = sec + s;
	if (sec >= 60)
	{
		sec = sec - 60;
		min = min + 1;
	}
	if (min >= 60)
	{
		min = min - 60;
		hour = hour + 1;
	}
	if (hour >= 24)
	{
		hour = hour - 24;
	}

	return *this;
} // 덧셈연산자 오버로딩
int Time::elasedSec()
{
	int sum, a, b;
	a = hour * 3600;
	b = min * 60;
	sum = a + b + sec;

	return sum;
} // 0시0분0초로부터 흐르시간
Time Time::getTime()
{
	return *this;
} // 
bool Time::operator<(Time& t)
{
	return (this->elasedSec() < t.elasedSec());
}
bool Time::operator<=(Time& t)
{
	return (this->elasedSec() <= t.elasedSec());
}
bool Time::operator>(Time& t)
{
	return (this->elasedSec() > t.elasedSec());
}
bool Time::operator>=(Time& t)
{
	return (this->elasedSec() >= t.elasedSec());
}
bool Time::operator==(Time& t)
{
	return (this->elasedSec() == t.elasedSec());
}
bool Time::isValidTime(int hour_, int min_, int sec_)
{
	if ((hour_ >= 0 && hour_ < 24) && (min_ >= 0 && min < 60) && (sec_ >= 0 && sec < 60))
		return 1;
	else
		return 0;
} // 유효한 시간인지 확인한는 함수