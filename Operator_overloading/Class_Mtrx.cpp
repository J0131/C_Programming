#include "Class_Mtrx.h"
#include <iostream>
#include <iomanip>
#define SETW 6
using namespace std;

Mtrx::Mtrx()
{
	name = "string";
	n_row = 0;
	n_col = 0; // �μ��� ���޵����ʾ����� ������ ���� �����͸���ʱ�ȭ

	int i, j;
	dM = new double* [n_row]; // n_row��ŭ ���� �������� ����
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col]; // n_col��ŭ ���� �������� ����
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0; // dM�� ���Ҹ� 0�����ʱ�ȭ
		}
	}
}

Mtrx::Mtrx(string nm, int num_row, int num_col)
	: name(nm), n_row(num_row), n_col(num_col) // ���޵� �μ��� ���������͸�� �ʱ�ȭ
{
	int i, j;
	dM = new double* [n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	} // �������� �������� ����
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0; // dM�� ���Ҹ� 0�����ʱ�ȭ
		}
	}
}
Mtrx::Mtrx(istream& fin)
{
	int i, j, size_row, size_col, num_data, cnt;
	double d;
	fin >> size_row >> size_col; // ���Ͽ��� �����͸� �о� size_row, size_col�� ���� ����
	n_row = size_row; 
	n_col = size_col; // size_row, size_col�� n_row, n_col�� ����
	dM = new double* [n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	} // �������� �������� ����
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			if (fin.eof())
				dM[i][j] = 0.0; // ������ ���� ��Ÿ���� dM[i][j]�� 0���� �ʱ�ȭ
			else
			{
				fin >> d; // ���Ͽ��� �����͸� �о� d�������ϰ�
				dM[i][j] = d; // d�� dM[i][j]�� ����
			}
		}
	}
}
Mtrx::Mtrx(string nm, double* pA, int num_row, int num_col)
	: name(nm), n_row(num_row), n_col(num_col)
{
	int i, j;
	dM = new double* [n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	} // �������� �������� ����
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = pA[j]; // dM[i][j] = pA[j]�� ����
		}
	}
}
Mtrx::~Mtrx()
{
	// cout << "destructor of Mtrx ("
	// << name << ")" << endl;
	/*
	for (int i=0; i<n_row; i++)
	delete [] dM[i];
	delete [] dM;
	*/
}

void Mtrx::init(int num_row, int num_col)
{
	int i, j;
	dM = new double* [num_row];
	n_row = num_row;
	n_col = num_col;
	for (i = 0; i < num_row; i++)
	{
		dM[i] = new double[num_col];
	}   // �������� �������� ����
	for (i = 0; i < num_row; i++) {
		for (j = 0; j < num_col; j++) {
			dM[i][j] = 0.0;
		}
	}
} // ������ ����� �ʱ�ȭ�ϴ� �Լ�
ostream& operator<<(ostream& fout, Mtrx& m)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	fout << m.get_name() << endl;
	for (int i = 0; i < m.n_row; i++) {
		for (int j = 0; j < m.n_col; j++)
		{
			fout.setf(ios::fixed);
			fout.precision(2);
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(SETW) << m.dM[i][j];
			else if ((i == 0) && (j == (m.n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a4;
			else if ((i > 0) && (i < (m.n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(SETW) << m.dM[i][j];
			else if ((i > 0) && (i < (m.n_row - 1)) && (j == (m.n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a2;
			else if ((i == (m.n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(SETW) << m.dM[i][j];
			else if ((i == (m.n_row - 1)) && (j == (m.n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a5;
			else
				fout << setw(SETW) << m.dM[i][j];
		}
		fout << endl;
	}
	fout << endl;
	return fout; // fout�� ��ȯ
} // ���Ͽ� ������¸� ����ϴ��Լ�
istream& operator>> (istream& fin, Mtrx& mA)
{
	fin >> mA.n_col >> mA.n_row; // ���Ͽ��� �����͸� ���ʴ�� �о�  mA.n_col,  mA.n_row�� �����������
	for (int i = 0; i < mA.n_col; i++)
	{
		for (int j = 0; j < mA.n_row; j++)
		{
			fin >> mA.dM[i][j]; // ���Ͽ��� �����͸� �о� mA.dM[i][j]������
		}
	}
	return fin; // fin�� ��ȯ
}
Mtrx Mtrx::operator+(const Mtrx& mA)
{
	int i, j;
	Mtrx mR("mR", n_row, n_col);
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j]; // ����� �������Ͽ� mR.dM������
		}
	}
	return mR; // mR�� ��ȯ
}

const Mtrx Mtrx::operator-(const Mtrx& mA)
{
	int i, j;
	Mtrx mR("mR", n_row, n_col);
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];  // ����� �������Ͽ� mR.dM������
		}
	}
	return mR; // mR�� ��ȯ

}
const Mtrx Mtrx::operator*(const Mtrx& mA)
{
	Mtrx mR("mR", n_row, n_col);
	for (int i = 0; i < n_row; i++) {
		for (int j = 0; j < n_col; j++) 
		{
			for (int k = 0; k < mA.n_col; k++)
				mR.dM[i][j] += dM[i][k] * mA.dM[k][j];  // ����� �����������Ͽ� mR.dM������
		}
	}
	return mR; // mR�� ��ȯ
}

const Mtrx& Mtrx::operator=(const Mtrx& mA)
{
	
	for (int i = 0; i < n_row; i++)
	{
		for (int k = 0; k < n_col; k++)
		{
			dM[i][k] = mA.dM[i][k]; // mA.dM���ҵ��� dM�� ����
		}
	}

	return *this; // �ڽ��� ��ȯ
}

bool Mtrx:: operator==(const Mtrx& mA)
{
	int a = 0;

	if ((n_row == mA.n_row) && (n_col == mA.n_col))
	{
		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				if(dM[i][j]!=mA.dM[i][j]) // mA.dM�� dM�� ��� ���ҵ��� ���Ͽ� �ٸ������� a�� ������Ŵ
					a++;
			}
		}
		if (a == 0)
			return true; // a�� 1�̸� true��ȯ
		else
			return false; // a�� 0�̸� false��ȯ
	}
	else
		return false; // ��� ���� ���������� false��ȯ
}

bool Mtrx:: operator!=(const Mtrx& mA)
{
	int a = 0;

	if ((n_row == mA.n_row) && (n_col == mA.n_col))
	{
		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				if (dM[i][j] != mA.dM[i][j])
					a++; // mA.dM�� dM�� ��� ���ҵ��� ���Ͽ� �ٸ������� a�� ������Ŵ
			}
		}
		if (a == 0)
			return false; // a�� 1�̸� false��ȯ
		else
			return true; // a�� 0�̸� true��ȯ
	}
	else 
		return true; // ��� ���� ���������� true��ȯ
}