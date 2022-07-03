#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.000001

double** create2DimDoubleArray(int row_size, int col_size); // 2���� �����迭�� �����ϴ� �Լ�
void fget2DimDoubleArray(FILE* fin, double** mA, int row, int col); // 2���� �迭�� ���Ͽ��� ���� �о�� �����ϴ� �Լ�
double getTotal_Avg(double** dM, int size_row, int size_col); // 2���� �迭�� ����� �����ִ� �Լ�
void print2DimDoubleArray(double** dM, int size_row, int size_col); // 2���� �迭�� ȭ�鿡 ����Լ�
void fprint2DimDoubleArray(FILE* fout, double** mA, int size_row, int size_col); // 2���� �迭�� ���Ͽ� ����ϴ� �Լ�
void printMtrx(double** M, int size_row, int size_col); // ����� ȭ�鿡 ����ϴ� �Լ�
void fprintMtrx(FILE* fout, double** M, int size_row, int size_col); // ����� ���Ͽ� ����ϴ� �Լ�
void addMatrix(double** mR, double** mA, double** mB, int size_row, int size_col); // ����� ���������� �ϴ� �Լ�
void subtractMatrix(double** mR, double** mA, double** mB, int size_row, int size_col); // ����� ���� ������ �ϴ� �Լ�
void multiplyMatrix(double** mR, double** mA, double** mB, int size_row, int size_k, int size_col); // ����� ���� ������ �ϴ� �Լ�
void fgetAugmentedMatrixData(FILE* fin, double** mA, int size); // ���Ͽ��� ���� �о�� ÷����Ŀ� �����ϴ� �Լ�
double** createDynamicDoubleMatrix(int row_size, int col_size); // ��� �����ϴ� �Լ�
void fgetDoubleMatrixData(FILE* fin, double** mA, int row, int col); // ���Ͽ��� ���� �о�� ��Ŀ� �����ϴ� �Լ�
void deleteDynamicDoubleMatrix(double** dM, int row_size, int col_size); // ������� ����� �����ϴ� �Լ�
void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist); // ������밢ȭ�ϴ� �Լ�
void pivoting(double** augMtrx, int size_N, int p, int* piv_found); // ��Ŀ��� �� �ڸ� �ٲ��� ���ִ� �Լ�
void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** inv_A, int size_N); // � ����� ������� �����ִ� �Լ�