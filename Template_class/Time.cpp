#include "Time.h"

ostream& operator<<(ostream& fout, Time& t)
{
	fout <<"( " << setw(2) << t.hour << ":" << setw(2) << t.min << ":" << setw(2) << t.sec << ")";
	return fout;
} // ��¿����� �����ε�
Time::Time()
{
	hour = 0;
	min = 0;
	sec = 0;
} // �⺻������
Time::Time(int h, int m, int s)
{
	hour = h;
	min = m;
	sec = s;
} // ������
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
} // ���������� �����ε�
int Time::elasedSec()
{
	int sum, a, b;
	a = hour * 3600;
	b = min * 60;
	sum = a + b + sec;

	return sum;
} // 0��0��0�ʷκ��� �帣�ð�
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
} // ��ȿ�� �ð����� Ȯ���Ѵ� �Լ�