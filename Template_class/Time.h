#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class Time
{
	friend ostream& operator<<(ostream&,Time&); // ��¿�����
public:
	Time(); // 
	Time(int h, int m, int s); // ������
	Time& operator+(int s); // ����������
	int elasedSec();
	Time getTime();
	bool operator<(Time&);
	bool operator<=(Time&);
	bool operator>(Time&);
	bool operator>=(Time&);
	bool operator==(Time&); // �񱳿�����
private:
	bool isValidTime(int, int, int); // ��ȿ�� �ð����� Ȯ��
	int hour;
	int min;
	int sec;
};
