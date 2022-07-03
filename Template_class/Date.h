#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Date
{
	friend istream& operator>>(istream&, const Date&);
	friend ostream& operator<<(ostream&, Date&); // ��¿�����
public:
	Date(); //
	Date(int y, int m, int d); // ������
	void setDate(int newYear, int newMonth, int newDay); // ��¥����
	int getYear() { return year; }
	int getYearDay();
	int getWeekDay();
	int getElapsedDays(); // 1��1��1�Ϻ��� ����������ϼ�
	const Date operator=(const Date& rightSide); // ���Կ�����
	bool operator>(Date& rightSide);
	bool operator>=(Date& rightSide);
	bool operator<(Date& rightSide);
	bool operator<=(Date& rightSide);
	bool operator==(Date& rightSide);
	bool operator!=(Date& rightSide);
	bool isLeapYear(int y); // ����Ȯ�� 
private:
	bool isLeapYear(); // 
	bool isValidDate(int y, int m, int d); // ��ȿ�� ��¥���� Ȯ��
	int year;
	int month;
	int day;
};
