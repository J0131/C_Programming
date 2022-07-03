#include "StudentArray.h"

StudentArray::StudentArray(int size)
{
	num_students = size;
	students = new Student[size]; // size ��ŭ �����Ҵ�
	for (int i = 0; i < size; i++)
	{
		students[i] = Student(); // students[i]�� ���Ҹ� �ʱ�ȭ
	}
}

StudentArray::StudentArray(const StudentArray& obj)
{
	students = obj.students;
}

StudentArray::~StudentArray()
{
	if (num_students > 0)
		delete[] students;  // �����Ҵ� ����
} // �Ҹ���

bool StudentArray::isValidIndex(int index)
{
	if (index < 0 || index >= num_students)
	{ // index�� ������ ������� �����޼������
		cout << " ARRAY SIZE ERROR";
		exit(0);
	}
	else
		return true; // index�� �������� ������� true��ȯ
}

ostream& operator<< (ostream& fout, StudentArray& st)
{
	for (int i = 0; i < st.num_students; i++)
	{
		fout << st[i]<<endl;
	} // StudentArray ���
	return fout; // fout ��ȯ
}

Student& StudentArray:: operator[](int index)
{
	if (isValidIndex(index))
		return students[index]; // students[index] ��ȯ
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
		min_date = students[min_st].getBirthDate(); // min_date �� students[min_st]�� birthdate�� ����
		for (j = i + 1; j < num_students ; j++)
		{
			if (students[j].getBirthDate() < min_date) // students[j].birthdate ��  min_date���� �۴ٸ�
			{
				min_st = j;
				min_date = students[j].getBirthDate();  // min_date �� students[j].birthdate
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
		min_name = students[min_st].name; // min_name �� students[min_st]�� name�� ����
		for (j = i + 1; j < num_students ; j++) 
		{
			if (students[j].name < min_name) // students[j].name ��  min_name���� �۴ٸ�
			{
				min_st = j;
				min_name = students[j].name;  // min_name �� students[j]�� name�� ����
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
		min_ID = students[min_st].st_id; // min_ID�� students[min_st]�� st_id�� ����
		for (j = i + 1; j < num_students ; j++)
		{
			if (students[j].st_id < min_ID)
			{
				min_st = j;
				min_ID = students[j].st_id;  // min_ID�� students[j]�� st_id�� ����
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
		max_gpa = students[max_st].gpa; // max_gpa �� students[max_st].gpa�� ����
		for (j = i + 1; j < num_students ; j++)
		{
			if (students[j].gpa> max_gpa) // students[j].gpa�� max_gpa���� Ŭ��
			{
				max_st = j;
				max_gpa = students[j].gpa; // max_gpa �� students[j].gpa�� ����
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