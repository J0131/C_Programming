#include "Student.h"

void selectionSortStudents_by_ST_ID(STUDENT students[], int num)
{
	STUDENT* pST, * pST_min;
	STUDENT temp; // ����ü�� �ӽ÷� �����ص� ����
	int st_id_min; // �й��� �������� �л��� ����ü�迭��ġ
	for (int i = 0; i < num; i++) // 0���� num-1��ŭ �ݺ�
	{
		pST_min = pST = &students[i];
		st_id_min = i; // �ʱⰪ�� i�εд�
		for (int j = i + 1; j < num; j++) // i+1���� num-1��ŭ�ݺ�
		{
			pST = &students[j];
			if (pST->st_id < pST_min->st_id)
			{
				pST_min = pST; // pST->st_id�� pST_min->st_id���������� �׶��� pST�� pST_min���� �д�
				st_id_min = j; // �й��� �������� �л��ǹ迭��ġ�� j�̴�
			}
		}
		if (st_id_min != i) // st_id_min�� i�� �ƴϸ� students[i]�� students[st_id_min]�� �ٲ��ش�
		{
			temp = students[i];
			students[i] = students[st_id_min];
			students[st_id_min] = temp;
		}
	}
}

void printStudents(STUDENT* stArr, int num)
{
	STUDENT* st = stArr; // student����ü������ ������ ����
	for (int i = 0; i < num; i++)
	{
		printStudent(st);// stArr�� ����ü�� ���
		printf("\n");
		st++;
	}
}

void printStudent(STUDENT* pST)
{
	printf("Student [ID: %08d, %-10s", pST->st_id, pST->name);  // �й�, �̸����
	printf(", GPA: %5.2lf", pST->GPA); // ���� ���
	printf(", ");
	printDate(pST->birth_date); // ������� ���
	printf(", ");
	printTelephoneNumber(pST->tel_number); // ��ȭ��ȣ ���
	printf("]");
}

void printTelephoneNumber(Tel_Number telNo)
{
	printf("(tel: +%d-", telNo.nation_code);
	printf("%03d-%04d-%04d)", telNo.region_no, telNo.switch_no, telNo.line_no); // telNo���� nation_code - region_no - switch_no - line_no ������ ���
}

void fprintTelephoneNumber(FILE* fout,Tel_Number telNo)
{
	fprintf(fout,"(tel: +%d-", telNo.nation_code);
	fprintf(fout,"%03d-%04d-%04d)", telNo.region_no, telNo.switch_no, telNo.line_no); // telNo���� nation_code - region_no - switch_no - line_no ������ ���
}

void printDate(Date date)
{
	printf("(%04d, %2d, %2d)",date.year, date.month, date.day);
}

void fprintDate(FILE*fout,Date date)
{
	fprintf(fout,"(%04d, %2d, %2d)", date.year, date.month, date.day);
}

void fprintStudents(FILE* fout, STUDENT* stArr, int num)
{
	STUDENT* st = stArr; // student����ü������ ������ ����
	for (int i = 0; i < num; i++)
	{
		fprintf(fout,"Student [ID: %08d, %-10s", st->st_id, st->name);  // �й�, �̸����
		fprintf(fout,", GPA: %5.2lf", st->GPA); // ���� ���
		fprintf(fout,", ");
		fprintDate(fout, st->birth_date); // ������� ���
		fprintf(fout,", ");
		fprintTelephoneNumber(fout,st->tel_number); // ��ȭ��ȣ ���
		fprintf(fout,"]");// stArr�� ����ü�� ���
		fprintf(fout,"\n");
		st++;
	}
}