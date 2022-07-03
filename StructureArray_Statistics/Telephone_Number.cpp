#include <stdio.h>
#include "Telephone_number.h"
void printTelephoneNumber(Tel_Number telNo)
{
	printf("(tel: +%d-", telNo.nation_code);
	printf("%03d-%04d-%04d)", telNo.region_no, telNo.switch_no, telNo.line_no); // telNo���� nation_code - region_no - switch_no - line_no ������ ���
}
int compareTelNumber(Tel_Number tn1, Tel_Number tn2)
{
	if (tn1.nation_code > tn2.nation_code)
		return 1; 
	else if (tn1.nation_code < tn2.nation_code)
		return -1; // �� ����ü�� nation_code�� ���Ͽ� tn1>tn2�̸� 1�� ��ȯ, tn1<tn2�̸� -1�� ��ȯ
	else if (tn1.region_no > tn2.region_no) // nation_code�� ���� ��� region_no�� ��
		return 1; 
	else if (tn1.region_no < tn2.region_no)
		return -1; // tn1 > tn2�̸� 1�� ��ȯ, tn1 < tn2�̸� - 1�� ��ȯ
	else if (tn1.switch_no > tn2.switch_no) // region_no�� ������� switch_no�� ��
		return 1;
	else if (tn1.switch_no < tn2.switch_no)
		return -1;  // tn1 > tn2�̸� 1�� ��ȯ, tn1 < tn2�̸� - 1�� ��ȯ
	else if (tn1.line_no > tn2.line_no) // switch_no�� ������� line_no�� ��
		return 1;
	else if (tn1.line_no < tn2.line_no)
		return -1; // tn1 > tn2�̸� 1�� ��ȯ, tn1 < tn2�̸� - 1�� ��ȯ
	else
		return 0; // ��� ������� 0����ȯ
}