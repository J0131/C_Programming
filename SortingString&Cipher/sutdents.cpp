#include "Student.h"

void selectionSortStudents_by_ST_ID(STUDENT students[], int num)
{
	STUDENT* pST, * pST_min;
	STUDENT temp; // 구조체를 임시로 저장해둘 변수
	int st_id_min; // 학번이 가장작은 학생의 구조체배열위치
	for (int i = 0; i < num; i++) // 0에서 num-1만큼 반복
	{
		pST_min = pST = &students[i];
		st_id_min = i; // 초기값을 i로둔다
		for (int j = i + 1; j < num; j++) // i+1에서 num-1만큼반복
		{
			pST = &students[j];
			if (pST->st_id < pST_min->st_id)
			{
				pST_min = pST; // pST->st_id가 pST_min->st_id보다작으면 그때의 pST를 pST_min으로 둔다
				st_id_min = j; // 학번이 가장작은 학생의배열위치는 j이다
			}
		}
		if (st_id_min != i) // st_id_min이 i가 아니면 students[i]와 students[st_id_min]를 바꿔준다
		{
			temp = students[i];
			students[i] = students[st_id_min];
			students[st_id_min] = temp;
		}
	}
}

void printStudents(STUDENT* stArr, int num)
{
	STUDENT* st = stArr; // student구조체형식의 포인터 선언
	for (int i = 0; i < num; i++)
	{
		printStudent(st);// stArr의 구조체를 출력
		printf("\n");
		st++;
	}
}

void printStudent(STUDENT* pST)
{
	printf("Student [ID: %08d, %-10s", pST->st_id, pST->name);  // 학번, 이름출력
	printf(", GPA: %5.2lf", pST->GPA); // 성적 출력
	printf(", ");
	printDate(pST->birth_date); // 생년월일 출력
	printf(", ");
	printTelephoneNumber(pST->tel_number); // 전화번호 출력
	printf("]");
}

void printTelephoneNumber(Tel_Number telNo)
{
	printf("(tel: +%d-", telNo.nation_code);
	printf("%03d-%04d-%04d)", telNo.region_no, telNo.switch_no, telNo.line_no); // telNo내의 nation_code - region_no - switch_no - line_no 순으로 출력
}

void fprintTelephoneNumber(FILE* fout,Tel_Number telNo)
{
	fprintf(fout,"(tel: +%d-", telNo.nation_code);
	fprintf(fout,"%03d-%04d-%04d)", telNo.region_no, telNo.switch_no, telNo.line_no); // telNo내의 nation_code - region_no - switch_no - line_no 순으로 출력
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
	STUDENT* st = stArr; // student구조체형식의 포인터 선언
	for (int i = 0; i < num; i++)
	{
		fprintf(fout,"Student [ID: %08d, %-10s", st->st_id, st->name);  // 학번, 이름출력
		fprintf(fout,", GPA: %5.2lf", st->GPA); // 성적 출력
		fprintf(fout,", ");
		fprintDate(fout, st->birth_date); // 생년월일 출력
		fprintf(fout,", ");
		fprintTelephoneNumber(fout,st->tel_number); // 전화번호 출력
		fprintf(fout,"]");// stArr의 구조체를 출력
		fprintf(fout,"\n");
		st++;
	}
}