#include "Class_Mtrx.h"
#include <iostream>
#include <iomanip>
#define SETW 6
using namespace std;

Mtrx::Mtrx()
{
	name = "string";
	n_row = 0;
	n_col = 0; // 인수가 전달되지않았을때 다음과 같이 데이터멤버초기화

	int i, j;
	dM = new double* [n_row]; // n_row만큼 행을 동적으로 생성
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col]; // n_col만큼 열을 동적으로 생성
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0; // dM의 원소를 0으로초기화
		}
	}
}

Mtrx::Mtrx(string nm, int num_row, int num_col)
	: name(nm), n_row(num_row), n_col(num_col) // 전달된 인수를 다음데이터멤버 초기화
{
	int i, j;
	dM = new double* [n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	} // 동적으로 열과행을 생성
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0; // dM의 원소를 0으로초기화
		}
	}
}
Mtrx::Mtrx(istream& fin)
{
	int i, j, size_row, size_col, num_data, cnt;
	double d;
	fin >> size_row >> size_col; // 파일에서 데이터를 읽어 size_row, size_col에 각각 저장
	n_row = size_row; 
	n_col = size_col; // size_row, size_col를 n_row, n_col에 저장
	dM = new double* [n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	} // 동적으로 열과행을 생성
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			if (fin.eof())
				dM[i][j] = 0.0; // 파일의 끝이 나타나면 dM[i][j]를 0으로 초기화
			else
			{
				fin >> d; // 파일에서 데이터를 읽어 d에저장하고
				dM[i][j] = d; // d를 dM[i][j]에 저장
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
	} // 동적으로 열과행을 생성
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = pA[j]; // dM[i][j] = pA[j]에 저장
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
	}   // 동적으로 열과행을 생성
	for (i = 0; i < num_row; i++) {
		for (j = 0; j < num_col; j++) {
			dM[i][j] = 0.0;
		}
	}
} // 데이터 멤버를 초기화하는 함수
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
	return fout; // fout을 반환
} // 파일에 행렬형태를 출력하는함수
istream& operator>> (istream& fin, Mtrx& mA)
{
	fin >> mA.n_col >> mA.n_row; // 파일에서 데이터를 차례대로 읽어  mA.n_col,  mA.n_row에 순서대로저장
	for (int i = 0; i < mA.n_col; i++)
	{
		for (int j = 0; j < mA.n_row; j++)
		{
			fin >> mA.dM[i][j]; // 파일에서 데이터를 읽어 mA.dM[i][j]에저장
		}
	}
	return fin; // fin을 반환
}
Mtrx Mtrx::operator+(const Mtrx& mA)
{
	int i, j;
	Mtrx mR("mR", n_row, n_col);
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j]; // 행렬의 덧셈을하여 mR.dM에저장
		}
	}
	return mR; // mR을 반환
}

const Mtrx Mtrx::operator-(const Mtrx& mA)
{
	int i, j;
	Mtrx mR("mR", n_row, n_col);
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];  // 행렬의 뺄셈을하여 mR.dM에저장
		}
	}
	return mR; // mR을 반환

}
const Mtrx Mtrx::operator*(const Mtrx& mA)
{
	Mtrx mR("mR", n_row, n_col);
	for (int i = 0; i < n_row; i++) {
		for (int j = 0; j < n_col; j++) 
		{
			for (int k = 0; k < mA.n_col; k++)
				mR.dM[i][j] += dM[i][k] * mA.dM[k][j];  // 행렬의 곱셈연산을하여 mR.dM에저장
		}
	}
	return mR; // mR을 반환
}

const Mtrx& Mtrx::operator=(const Mtrx& mA)
{
	
	for (int i = 0; i < n_row; i++)
	{
		for (int k = 0; k < n_col; k++)
		{
			dM[i][k] = mA.dM[i][k]; // mA.dM원소들을 dM에 대입
		}
	}

	return *this; // 자신을 반환
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
				if(dM[i][j]!=mA.dM[i][j]) // mA.dM과 dM의 모든 원소들을 비교하여 다를때마다 a를 증가시킴
					a++;
			}
		}
		if (a == 0)
			return true; // a가 1이면 true반환
		else
			return false; // a가 0이면 false반환
	}
	else
		return false; // 행과 열이 같지않으면 false반환
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
					a++; // mA.dM과 dM의 모든 원소들을 비교하여 다를때마다 a를 증가시킴
			}
		}
		if (a == 0)
			return false; // a가 1이면 false반환
		else
			return true; // a가 0이면 true반환
	}
	else 
		return true; // 행과 열이 같지않으면 true반환
}