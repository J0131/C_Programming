#include <stdio.h>
#include "Date.h"
void printDate(Date date)
{
	printf("(%04d, %2d, %2d)",
		date.year, date.month, date.day);
} // year-month-day 순으로 출력
int compareDate(Date d1, Date d2)
{
	if (d1.year > d2.year)
		return 1; // 각 구조체의 year를 비교하여 d1>d2이면 1을 반환, d1<d2이면 -1을 반환
	else if (d1.year < d2.year)
		return -1;
	else if (d1.month > d2.month) // year이 같을경우 month를 비교
		return 1;
	else if (d1.month < d2.month)
		return -1; // month를 비교하여 d1>d2이면 1을 반환, d1<d2이면 -1을 반환
	else if (d1.day > d2.day) // month이 같을경우 day를 비교
		return 1;
	else if (d1.day < d2.day)
		return -1;  // day를 비교하여 d1 > d2이면 1을 반환, d1 < d2이면 - 1을 반환
    else
		return 0; // year,month,day가 모두같을경우 0을 반환
}