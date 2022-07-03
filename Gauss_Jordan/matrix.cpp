#include "Matrix.h"

double** create2DimDoubleArray(int row_size, int col_size)
{
	double** mA;
	mA = (double**)calloc(row_size, sizeof(double*));
	for (int m = 0; m < row_size; m++)
	{
		mA[m] = (double*)calloc(col_size, sizeof(double));
	}
	return mA;
} // 2차원 동적배열 생성

void fget2DimDoubleArray(FILE* fin, double** mA, int row,int col)
{
	double d = 0.0;
	if (fin == NULL)
	{
		printf("Error in getDoubleMatrixData() - file pointer is NULL !!?n");
		exit(-1);
	} // 예외처리
	for (int m = 0; m < row; m++)
	{
		for (int n = 0; n < col; n++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)
				mA[m][n] = d;
		}
	} // 파일에있는 값을 배열에저장
}

double getTotal_Avg(double** dM, int size_row, int size_col)
{
	double d = 0.0;
	double x;
	double avg;

	for (int m = 0; m < size_row; m++)
	{
		for (int n = 0; n < size_col; n++)
		{
			d += dM[m][n];
		}
	}
	x = size_row * size_col; // 2차원 배열의 모든 원수 갯수
	avg = d / x; // 총합을 총갯수로 나눠주면 평균이 나온다
	return avg;
}

void print2DimDoubleArray(double** mA, int size_r, int size_c)
{
	for (int m = 0; m < size_r; m++)
	{
		for (int n = 0; n < size_c; n++)
		{
			printf("%8.2lf", mA[m][n]); // 소숫점 두자리
		}
		printf("\n");
	}
} // 2차원배열 화면에 출력
void fprint2DimDoubleArray(FILE* fout, double** mA, int size_r, int size_c)
{
	for (int m = 0; m < size_r; m++)
	{
		for (int n = 0; n < size_c; n++)
		{
			fprintf(fout,"%8.2lf ", mA[m][n]); // 소숫점 두자리
		}
		fprintf(fout,"\n");
	}
} // 2차원배열 파일에 출력

void printMtrx(double** mA, int size_r, int size_c)
{
	unsigned char a6 = 0xa6, a1 = 0xa1, a2 = 0xa2;
	unsigned char a3 = 0xa3, a4 = 0xa4, a5 = 0xa5;
	for (int m = 0; m < size_r; m++)
	{
		for (int n = 0; n < size_c; n++)
		{
			if ((m == 0) && (n == 0))
			{
				if (size_r == 1)
					printf("[ %8.2lf", mA[m][n]);
				else
					printf("%c%c%8.2lf", a6, a3, mA[m][n]);
				if (size_c == 1)
					printf(" %c%c", a6, a4);
			}
			else if ((m == 0) && n == (size_c - 1))
			{
				if (size_r == 1)
					printf("%8.2lf ]", mA[m][n]);
				else
					printf("%8.2lf %c%c", mA[m][n], a6, a4);
			}
			else if ((m > 0) && (m < size_r - 1) && (n == 0))
			{
				printf("%c%c%8.2lf", a6, a2, mA[m][n]);
				if (size_c == 1)
					printf(" %c%c", a6, a2);
			}
			else if ((m > 0) && (m < size_r - 1) && (n == (size_c - 1)))
				printf("%8.2lf %c%c", mA[m][n], a6, a2);
			else if ((m == (size_r - 1)) && (n == 0))
			{
				printf("%c%c%8.2lf", a6, a6, mA[m][n]);
				if (size_c == 1)
					printf(" %c%c", a6, a5);
			}
			else if ((m == (size_r - 1)) && (n == (size_c - 1)))
			{
				printf("%8.2lf %c%c", mA[m][n], a6, a5);
			}
			else
			{
				printf("%8.2lf", mA[m][n]);
			}

		}
		printf("\n");
	}
} // 행렬을 화면에 출력
void fprintMtrx(FILE* fout, double** mA, int size_r, int size_c)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	for (int m = 0; m < size_r; m++) {
		for (int n = 0; n < size_c; n++)
		{
			if ((m == 0) && (n == 0))
			{
				if (size_r == 1)
					fprintf(fout, "[ %10.4lf", mA[m][n]);
				else
					fprintf(fout, "%c%c%10.4lf", a6, a3, mA[m][n]);
				if (size_c == 1)
					fprintf(fout, " %c%c", a6, a4);
			}
			else if ((m == 0) && n == (size_c - 1))
			{
				if (size_r == 1)
					fprintf(fout, "%10.4lf ]", mA[m][n]);
				else
					fprintf(fout, "%10.4lf %c%c", mA[m][n], a6, a4);
			}
			else if ((m > 0) && (m < size_r - 1) && (n == 0))
			{
				fprintf(fout, "%c%c%10.4lf", a6, a2, mA[m][n]);
				if (size_c == 1)
					fprintf(fout, " %c%c", a6, a2);
			}
			else if ((m > 0) && (m < size_r - 1) && (n == (size_c - 1)))
				fprintf(fout, "%10.4lf %c%c", mA[m][n], a6, a2);
			else if ((m == (size_r - 1)) && (n == 0))
			{
				fprintf(fout, "%c%c%10.4lf", a6, a6, mA[m][n]);
				if (size_c == 1)
					fprintf(fout, " %c%c", a6, a5);
			}
			else if ((m == (size_r - 1)) && (n == (size_c - 1)))
			{
				fprintf(fout, "%10.4lf %c%c", mA[m][n], a6, a5);
			}
			else
				fprintf(fout, "%10.4lf", mA[m][n]);
		}
		fprintf(fout, "\n");
	}
} // 행렬을 파일에 출력

void addMatrix(double** mR, double** mA, double** mB, int size_row, int size_col)
{
	for (int m = 0; m < size_row; m++) 
	{
		for (int n = 0; n < size_col; n++)
		{
			mR[m][n] = mA[m][n] + mB[m][n]; // 행렬의덧셈
		}
	}
}
void subtractMatrix(double** mR, double** mA, double** mB, int size_row, int size_col)
{
	for (int m = 0; m < size_row; m++)
	{
		for (int n = 0; n < size_col; n++)
		{
			mR[m][n] = mA[m][n] - mB[m][n]; // 행렬의 뺄셈
		}
	}
}
void multiplyMatrix(double** mR, double** mA, double** mB, int size_row, int size_k, int size_col)
{
	for (int m = 0; m < size_row; m++)
	{
		for (int n = 0; n < size_col; n++)
		{
			mR[m][n] = 0;
			for (int k = 0; k < size_k; k++)
				mR[m][n] += mA[m][k] * mB[k][n]; // 행렬의 곱셈
		}
	}
}

void fgetAugmentedMatrixData(FILE* fin, double** mA, int size)
{
	double d = 0.0;
	if (fin == NULL)
	{
		printf("Error in getDoubleMatrixData() - file pointer is NULL !!?n");
		exit(-1);
	} // 예외처리
	for (int m = 0; m < size; m++)
	{
		for (int n = 0; n <= size; n++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)
				mA[m][n] = d;
		}
	} // 파일에있는 값을 첨가행렬에저장
}

double** createDynamicDoubleMatrix(int row_size, int col_size)
{
	double** mA;
	mA = (double**)calloc(row_size, sizeof(double*));
	for (int m = 0; m < row_size; m++)
	{
		mA[m] = (double*)calloc(col_size, sizeof(double));
	}
	return mA;
} // 2차원 동적배열(행렬) 생성

void fgetDoubleMatrixData(FILE* fin, double** mA, int row, int col)
{
	double d = 0.0;
	if (fin == NULL)
	{
		printf("Error in getDoubleMatrixData() - file pointer is NULL !!?n");
		exit(-1);
	} // 예외처리
	for (int m = 0; m < row; m++)
	{
		for (int n = 0; n < col; n++)
		{
			if (fscanf(fin, "%lf", &d) != EOF)
				mA[m][n] = d;
		}
	} // 파일에있는 값을 행렬에저장
}

void deleteDynamicDoubleMatrix(double** dM, int row_size, int col_size)
{
	for (int r = 0; r < row_size; r++)
	{
		free(dM[r]);
	}
	free(dM); // 2차원 배열 동적할당해제
}// 행렬을 삭제

void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist)
{
	int j, k, p = 0;
	double pivWeight, w;
	for (p = 0; (*solExist) && (p < size_N); p++) {
		fprintf(fout, "\nPivoting at p = %d\n", p);
		pivoting(mtrxAug, size_N, p, solExist); // 열을 바꿔주는함수
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
		if (*solExist)
		{
			if (mtrxAug[p][p] != 1.0)
			{
				pivWeight = mtrxAug[p][p];
				mtrxAug[p][p] = 1.0;
				for (k = p + 1; k <= size_N; k++)
				{
					mtrxAug[p][k] /= pivWeight;
				}
			} // 해당하는 값을 1로 만들어주기위해 해당하는 열의 나머지위치를 모두 pivWeight로 나눠준다
		}// 스케일링
		else
		{
			break;
		}
		fprintf(fout, "\nAfter scaling at p = %d\n", p);
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
		for (j = 0; j < size_N; j++)
		{
			if ((j != p) && (mtrxAug[j][p] != 0.0)) {
				w = mtrxAug[j][p];
				mtrxAug[j][p] = 0.0;
				for (k = p + 1; k <= size_N; k++) {
					mtrxAug[j][k] =
						mtrxAug[j][k] - w * mtrxAug[p][k];
				}
			}
		}  // 해당하는 행의 나머지열의 값을 모두 0으로만들기위해 빼주는 작업을 한다.
		// diagonalizing
		fprintf(fout, "\nAfter diagonalizing at p = %d\n", p);
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
	}
}

void pivoting(double** augMtrx, int size_N, int p, int* piv_found)
{
	double xmax = 0.0, xtemp;
	int j, k, max_row;
	xmax = fabs(augMtrx[p][p]); //배열에서 가장큰값을 찾는다
	max_row = p;
	for (j = p + 1; j < size_N; j++)
	{
		if (fabs(augMtrx[j][p]) > xmax) {
			xmax = fabs(augMtrx[j][p]);
			max_row = j;
		}
	}
	// 0이아닌 값을 발견하면 열을 바꾸어준다
	if (fabs(xmax) < EPSILON)
	{
		*piv_found = 0;
	}
	else {
		*piv_found = 1; // 피봇이 1일때 다음을동작
		if (max_row != p) // 해당행에서 최대값이 p가아니라면 다음을 동작
		{
			for (k = p; k <= size_N; k++)
			{
				xtemp = augMtrx[p][k];
				augMtrx[p][k] = augMtrx[max_row][k];
				augMtrx[max_row][k] = xtemp;
			} // 열을 바꿔준다
		}
	}
}

void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** inv_A, int size_N)
{
	int j, k, p = 0;
	double pivWeight, w;
	double** mAUG;
	mAUG = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++)
		mAUG[i] = (double*)calloc(size_N * 2, sizeof(double));
	for (j = 0; j < size_N; j++)
	{
		for (k = 0; k < size_N; k++)
			mAUG[j][k] = mA[j][k];
		for (k = size_N; k < size_N * 2; k++)
			mAUG[j][k] = (k == (j + size_N)) ? 1.0 : 0.0;
	} // size x size*2의 행렬을 만든다
	for (p = 0; p < size_N; p++)
	{
		if (mAUG[p][p] != 1.0)
		{
			pivWeight = mAUG[p][p];
			mAUG[p][p] = 1.0;
			for (k = p + 1; k < size_N * 2; k++)
			{
				mAUG[p][k] /= pivWeight; // 특정열의 해당하는 원소를 1로만들기위해 그원소를 제외한 모든 원소를 pivWeight로 나누어준다
			} // 스케일링
		}
		fprintf(fout, "After pivoting at p = %d\n", p);
		fprintMtrx(fout, mAUG, size_N, size_N * 2);
		for (j = 0; j < size_N; j++)
		{
			if ((j != p) && (mAUG[j][p] != 0.0))
			{
				w = mAUG[j][p];
				mAUG[j][p] = 0.0;
				for (k = p + 1; k < 2 * size_N; k++)
				{
					mAUG[j][k] -= w * mAUG[p][k];
				}
			} // 해당하는 행의 특정열의 원소만 빼고 모두 0으로만들어주기 위해 빼주는 작업을 한다
		}
		fprintf(fout, "After diagonalizing at p = %d\n", p);
		fprintMtrx(fout, mAUG, size_N, size_N * 2);
	}
	for (j = 0; j < size_N; j++)
	{
		for (k = 0; k < size_N; k++)
		{
			inv_A[j][k] = mAUG[j][k + size_N];
		}
	}  // 역행렬에 옮겨준다
}