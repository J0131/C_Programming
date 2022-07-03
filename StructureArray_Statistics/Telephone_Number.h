#ifndef TELEPHONE_NUMBER_H
#define TELEPHONE_NUMBER_H
typedef struct
{
	unsigned short nation_code;
	unsigned short region_no;
	unsigned short switch_no;
	unsigned short line_no;
}Tel_Number; // Tel_number ����ü ����
void printTelephoneNumber(Tel_Number telNo); // ��ȭ��ȣ�� ����ϴ� �Լ�
int compareTelNumber(Tel_Number tn1, Tel_Number tn2); // ��ȭ��ȣ ���ϴ� �Լ�
#endif