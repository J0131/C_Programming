#ifndef TELEPHONE_NUMBER_H
#define TELEPHONE_NUMBER_H
typedef struct
{
	unsigned short nation_code;
	unsigned short region_no;
	unsigned short switch_no;
	unsigned short line_no;
}Tel_Number; // Tel_number 구조체 선언
void printTelephoneNumber(Tel_Number telNo); // 전화번호를 출력하는 함수
int compareTelNumber(Tel_Number tn1, Tel_Number tn2); // 전화번호 비교하는 함수
#endif