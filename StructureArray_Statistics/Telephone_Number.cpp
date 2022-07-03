#include <stdio.h>
#include "Telephone_number.h"
void printTelephoneNumber(Tel_Number telNo)
{
	printf("(tel: +%d-", telNo.nation_code);
	printf("%03d-%04d-%04d)", telNo.region_no, telNo.switch_no, telNo.line_no); // telNo내의 nation_code - region_no - switch_no - line_no 순으로 출력
}
int compareTelNumber(Tel_Number tn1, Tel_Number tn2)
{
	if (tn1.nation_code > tn2.nation_code)
		return 1; 
	else if (tn1.nation_code < tn2.nation_code)
		return -1; // 각 구조체의 nation_code를 비교하여 tn1>tn2이면 1을 반환, tn1<tn2이면 -1을 반환
	else if (tn1.region_no > tn2.region_no) // nation_code가 같은 경우 region_no를 비교
		return 1; 
	else if (tn1.region_no < tn2.region_no)
		return -1; // tn1 > tn2이면 1을 반환, tn1 < tn2이면 - 1을 반환
	else if (tn1.switch_no > tn2.switch_no) // region_no가 같은경우 switch_no를 비교
		return 1;
	else if (tn1.switch_no < tn2.switch_no)
		return -1;  // tn1 > tn2이면 1을 반환, tn1 < tn2이면 - 1을 반환
	else if (tn1.line_no > tn2.line_no) // switch_no가 같은경우 line_no를 비교
		return 1;
	else if (tn1.line_no < tn2.line_no)
		return -1; // tn1 > tn2이면 1을 반환, tn1 < tn2이면 - 1을 반환
	else
		return 0; // 모두 같을경우 0을반환
}