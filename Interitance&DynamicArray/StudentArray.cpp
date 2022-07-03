#include "StudentArray.h"

StudentArray::StudentArray(int size)
{
	num_students = size;
	students = new Student[size]; // size 만큼 동적할당
	for (int i = 0; i < size; i++)
	{
		students[i] = Student(); // students[i]의 원소를 초기화
	}
}

StudentArray::StudentArray(const StudentArray& obj)
{
	students = obj.students;
}

StudentArray::~StudentArray()
{
	if (num_students > 0)
		delete[] students;  // 동적할당 해제
} // 소멸자

bool StudentArray::isValidIndex(int index)
{
	if (index < 0 || index >= num_students)
	{ // index가 범위를 벗어났을때 에러메세지출력
		cout << " ARRAY SIZE ERROR";
		exit(0);
	}
	else
		return true; // index가 정상적인 범위라면 true반환
}

ostream& operator<< (ostream& fout, StudentArray& st)
{
	for (int i = 0; i < st.num_students; i++)
	{
		fout << st[i]<<endl;
	} // StudentArray 출력
	return fout; // fout 반환
}

Student& StudentArray:: operator[](int index)
{
	if (isValidIndex(index))
		return students[index]; // students[index] 반환
}

void StudentArray::sortByBirthDate()
{
	int i, j, mx, min_st;
	char minName[16] = { 0 };
	Student tmp;
	Date min_date;

	for (i = 0; i < num_students - 1; i++)
	{
		min_st = i;
		min_date = students[min_st].getBirthDate(); // min_date 를 students[min_st]의 birthdate로 저장
		for (j = i + 1; j < num_students ; j++)
		{
			if (students[j].getBirthDate() < min_date) // students[j].birthdate 가  min_date보다 작다면
			{
				min_st = j;
				min_date = students[j].getBirthDate();  // min_date 는 students[j].birthdate
			}
		}
		if (min_st != i)
		{
			tmp = students[i];
			students[i] = students[min_st];
			students[min_st] = tmp;
		} // swap
	}
}
void StudentArray::sortByName()
{
	int i, j, mx, min_st;
	char minName[16] = { 0 };
	Student tmp;
	string min_name;

	for (i = 0; i < num_students - 1; i++)
	{
		min_st = i;
		min_name = students[min_st].name; // min_name 를 students[min_st]의 name로 저장
		for (j = i + 1; j < num_students ; j++) 
		{
			if (students[j].name < min_name) // students[j].name 가  min_name보다 작다면
			{
				min_st = j;
				min_name = students[j].name;  // min_name 를 students[j]의 name로 저장
			}
		}
		if (min_st != i)
		{
			tmp = students[i];
			students[i] = students[min_st];
			students[min_st] = tmp;
		} // swap
	}
}
void StudentArray::sortByST_ID()
{
	int i, j, mx, min_st,min_ID;
	char minName[16] = { 0 };
	Student tmp;

	for (i = 0; i < num_students-1 ; i++)
	{
		min_st = i;
		min_ID = students[min_st].st_id; // min_ID를 students[min_st]의 st_id로 저장
		for (j = i + 1; j < num_students ; j++)
		{
			if (students[j].st_id < min_ID)
			{
				min_st = j;
				min_ID = students[j].st_id;  // min_ID를 students[j]의 st_id로 저장
			}
		}
		if (min_st != i)
		{
			tmp = students[i];
			students[i] = students[min_st];
			students[min_st] = tmp;
		} // swap
	}
}
void StudentArray::sortByGPA()
{
	int i, j, mx, max_st;
	char minName[16] = { 0 };
	Student tmp;
	double max_gpa;

	for (i = 0; i < num_students - 1; i++)
	{
		max_st = i;
		max_gpa = students[max_st].gpa; // max_gpa 를 students[max_st].gpa로 저장
		for (j = i + 1; j < num_students ; j++)
		{
			if (students[j].gpa> max_gpa) // students[j].gpa가 max_gpa보다 클때
			{
				max_st = j;
				max_gpa = students[j].gpa; // max_gpa 는 students[j].gpa로 저장
			}
		}
		if (max_st != i)
		{
			tmp = students[i];
			students[i] = students[max_st];
			students[max_st] = tmp;
		} // swap
	}
}