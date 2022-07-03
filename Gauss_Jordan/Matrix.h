#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.000001

double** create2DimDoubleArray(int row_size, int col_size); // 2차원 동적배열을 생성하는 함수
void fget2DimDoubleArray(FILE* fin, double** mA, int row, int col); // 2차원 배열에 파일에서 값을 읽어와 저장하는 함수
double getTotal_Avg(double** dM, int size_row, int size_col); // 2차원 배열의 평균을 구해주는 함수
void print2DimDoubleArray(double** dM, int size_row, int size_col); // 2차원 배열을 화면에 출력함수
void fprint2DimDoubleArray(FILE* fout, double** mA, int size_row, int size_col); // 2차원 배열을 파일에 출력하는 함수
void printMtrx(double** M, int size_row, int size_col); // 행렬을 화면에 출력하는 함수
void fprintMtrx(FILE* fout, double** M, int size_row, int size_col); // 행렬을 파일에 출력하는 함수
void addMatrix(double** mR, double** mA, double** mB, int size_row, int size_col); // 행렬의 덧셈연산을 하는 함수
void subtractMatrix(double** mR, double** mA, double** mB, int size_row, int size_col); // 행렬의 뺄셈 연산을 하는 함수
void multiplyMatrix(double** mR, double** mA, double** mB, int size_row, int size_k, int size_col); // 행렬의 곱셈 연산을 하는 함수
void fgetAugmentedMatrixData(FILE* fin, double** mA, int size); // 파일에서 값을 읽어와 첨가행렬에 저장하는 함수
double** createDynamicDoubleMatrix(int row_size, int col_size); // 행렬 생성하는 함수
void fgetDoubleMatrixData(FILE* fin, double** mA, int row, int col); // 파일에서 값을 읽어와 행렬에 저장하는 함수
void deleteDynamicDoubleMatrix(double** dM, int row_size, int col_size); // 만들어진 행렬을 삭제하는 함수
void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist); // 행렬을대각화하는 함수
void pivoting(double** augMtrx, int size_N, int p, int* piv_found); // 행렬에서 열 자리 바꿈을 해주는 함수
void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** inv_A, int size_N); // 어떤 행렬의 역행렬을 구해주는 함수