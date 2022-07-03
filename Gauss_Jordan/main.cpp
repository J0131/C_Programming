/************************************
* ���ϸ��� : ����� C���󿡼� �پ��� ������ �ϴ� ���α׷�
* �ۼ���  : �ֹ���
* Final update : 2020-05-23
*************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Matrix.h"

const char* outputFile = "OutputResult.txt";

void checkAddress_2DimArray_for_Matrix(FILE* fout); // 2���� �迭�� �ּҸ� Ȯ���ϴ� �Լ�
void getTotal_Avg_of_2DimArray(FILE* fout); // 2���� �迭�� ����� ���ϴ� �Լ�
void test_2D_DynamicArray_FileIO(FILE* fout); // ���Ͽ������ ���� �о�� 2���� �迭�� �����ϴ� �Լ�
void test_MatrixAdditionSubtraction(FILE* fout); // ����� �������������� �ϴ� �Լ�
void test_MatrixMultiplication(FILE* fout); // ������� ������ �ϴ� �Լ�
void test_GaussJordanElimination_LinearSystem(FILE* fout); // ���콺������ �ҰŹ��� �̿��� ����� �ظ� ���ϴ� �Լ�
void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout); // ������� �̿��� ����� �ظ� ã�� �Լ�

int main(void)
{
	FILE* fin, * fout;
	int menu;
	fout = fopen(outputFile, "w"); // "OutputResult.txt"���� ������� ����
	if (fout == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	while (1)
	{
		printf("Testing Matrix Operations with 2-Dimensional Dynamic Array\n");
		printf(" 1: Check addresses of 2-Dim array for Matrix\n");
		printf(" 2: Calculate total average of 2-Dim array\n");
		printf(" 3: Test 2-D Dynamic Array Creation for Matrix with File I/O\n");
		printf(" 4: Test Matrix Addition, Subtraction\n");
		printf(" 5: Test Matrix Multiplication\n");
		printf(" 6: Test Gauss-Jordan Elimination for Linear System\n");
		printf(" 7: Test InvMtrx_Gauss-Jordan Elimination for Linear System\n");
		printf("-1: Quit\n");
		printf("Input menu (-1 to quit) : ");
		scanf("%d", &menu);
		if (menu == -1)
			break;
		printf("\n");
		switch (menu)
		{
		case 1:
			checkAddress_2DimArray_for_Matrix(fout);
			break;
		case 2:
			getTotal_Avg_of_2DimArray(fout);
			break;
		case 3:
			test_2D_DynamicArray_FileIO(fout);
			break;
		case 4:
			test_MatrixAdditionSubtraction(fout);
			break;
		case 5:
			test_MatrixMultiplication(fout);
			break;
		case 6:
			test_GaussJordanElimination_LinearSystem(fout);
			break;
		case 7:
			test_InvMtrx_GaussJordanElimination_LinearSystem(fout);
			break;
		default:
			break;
		}
	} // ���ϴ� �޴��� �ش��ϴ� ���� �Է��ϸ� �ش��ϴ� ���� �Լ��� ����
	// ����o
	fclose(fout);
}

void checkAddress_2DimArray_for_Matrix(FILE* fout)
{
	int m[3][3] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
	printf("m        = %p\n", m);
	printf("m[0]     = %p\n", m[0]);
	printf("m[1]     = %p\n", m[1]);
	printf("m[2]     = %p\n", m[2]);
	printf("&m[0][0] = %p\n", &m[0][0]);
	printf("&m[1][0] = %p\n", &m[1][0]);
	printf("&m[2][0] = %p\n", &m[2][0]);
	printf("\n");
} //�迭���� ������ �ش��ϴ� �ּҰ��� ���

void getTotal_Avg_of_2DimArray(FILE* fout)
{
	const char* matrixDataFile = "mtrxInputData.txt";
	FILE* fin;
	int a_row_size, a_col_size;
	double** dMA;
	double avg;
	fin = fopen(matrixDataFile, "r"); // "mtrxInputData.txt" �б� ���� ����
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	fscanf(fin, "%d %d", &a_row_size, &a_col_size); // ���Ͽ��� ���� ���� ���� �о�� ����
	dMA = create2DimDoubleArray(a_row_size, a_col_size); // 2���� ���� �迭 ����
	fget2DimDoubleArray(fin, dMA, a_row_size, a_col_size); // 2���� ���� �迭�� ���Ͽ��� �о�°� ����
	printf("Input 2_D Array ( %d x %d) : \n", a_row_size, a_col_size);
	print2DimDoubleArray(dMA, a_row_size, a_col_size);
	avg = getTotal_Avg(dMA, a_row_size, a_col_size); // ��ձ��ϱ�
	printf("Total average of two_dim array : %8.2lf\n\n", avg);
} 

void test_2D_DynamicArray_FileIO(FILE* fout)
{
	const char* matrixDataFile = "mtrxInputData.txt";
	FILE* fin;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	double** dMA, ** dMB;
	fin = fopen(matrixDataFile, "r"); // "mtrxInputData.txt" �б� ���� ����
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	fscanf(fin, "%d %d", &a_row_size, &a_col_size); // ���Ͽ��� ���� ���� ���� �о�� ����
	dMA = createDynamicDoubleMatrix(a_row_size, a_col_size); // 2���� ���� �迭 ����
	fgetDoubleMatrixData(fin, dMA, a_row_size, a_col_size);// 2���� ���� �迭�� ���Ͽ��� �о�°� ����
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(dMA, a_row_size, a_col_size);
	printf("\n");
	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dMB = createDynamicDoubleMatrix(b_row_size, b_col_size);
	fgetDoubleMatrixData(fin, dMB, b_row_size, b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(dMB, b_row_size, b_col_size);
	printf("\n");
	fclose(fin);
} 

void test_MatrixAdditionSubtraction(FILE* fout)
{
	const char* matrixDataFile = "mtrx_nxn_InputData.txt";
	FILE* fin;
	double** dMA, ** dMB, ** dMC, ** dMD;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	int d_row_size, d_col_size;
	fin = fopen(matrixDataFile, "r"); //"mtrx_nxn_InputData.txt" �б� ���� ����
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	fscanf(fin, "%d %d", &a_row_size, &a_col_size); // ���Ͽ��� ���� ���� ���� �о�� ����
	dMA = createDynamicDoubleMatrix(a_row_size, a_col_size); // 2���� ���� �迭 ����
	fgetDoubleMatrixData(fin, dMA, a_row_size, a_col_size);// 2���� ���� �迭�� ���Ͽ��� �о�°� ����
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(dMA, a_row_size, a_col_size);
	printf("\n");
	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dMB = createDynamicDoubleMatrix(b_row_size, b_col_size);
	fgetDoubleMatrixData(fin, dMB, b_row_size, b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(dMB, b_row_size, b_col_size);
	printf("\n");
	if ((a_row_size != b_row_size) || (a_col_size != b_col_size))
	{
		printf("Error in input matrix dimension: row_size and/or col_size are not equal !!\n");
		fclose(fin);
		return;
	}
	c_row_size = a_row_size;
	c_col_size = b_col_size;
	dMC = createDynamicDoubleMatrix(c_row_size, c_col_size);
	addMatrix(dMC, dMA, dMB, a_row_size, a_col_size); // ����� ��������
	printf("Matrix_C (%d + %d) = Matrix_A + Matrix_B : \n", c_row_size, c_col_size);
	printMtrx(dMC, c_row_size, c_col_size);
	printf("\n");
	d_row_size = a_row_size;
	d_col_size = b_col_size;
	dMD = createDynamicDoubleMatrix(d_row_size, d_col_size);
	subtractMatrix(dMD, dMA, dMB, a_row_size, a_col_size); // ����� ���� ����
	printf("Matrix_D (%d - %d) = Matrix_A - Matrix_B : \n", d_row_size, d_col_size);
	printMtrx(dMD, d_row_size, d_col_size);
	printf("\n");
	deleteDynamicDoubleMatrix(dMA, a_row_size, a_col_size);
	deleteDynamicDoubleMatrix(dMB, b_row_size, b_col_size);
	deleteDynamicDoubleMatrix(dMC, c_row_size, c_col_size);
	deleteDynamicDoubleMatrix(dMD, d_row_size, d_col_size); // �����Ҵ�����
	fclose(fin);
}

void test_MatrixMultiplication(FILE* fout)
{
	const char* matrixDataFile = "mtrxInputData.txt";
	FILE* fin;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	double** dMA, ** dMB, ** dMC;
	fin = fopen(matrixDataFile, "r"); // "mtrxInputData.txt" �б� ���� ����
	if (fin == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	fscanf(fin, "%d %d", &a_row_size, &a_col_size); // ���Ͽ��� ���� ���� ���� �о�� ����
	dMA = createDynamicDoubleMatrix(a_row_size, a_col_size); // 2���� ���� �迭 ����
	fgetDoubleMatrixData(fin, dMA, a_row_size, a_col_size); // 2���� ���� �迭�� ���Ͽ��� �о�°� ����
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx(dMA, a_row_size, a_col_size);
	printf("\n");
	fscanf(fin, "%d %d", &b_row_size, &b_col_size);
	dMB = createDynamicDoubleMatrix(b_row_size, b_col_size);
	fgetDoubleMatrixData(fin, dMB, b_row_size, b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx(dMB, b_row_size, b_col_size);
	printf("\n");
	c_row_size = a_row_size;
	c_col_size = b_col_size;
	dMC = createDynamicDoubleMatrix(c_row_size, c_col_size);
	multiplyMatrix(dMC, dMA, dMB, a_row_size, a_col_size, b_col_size); //����� ���� ����
	printf("Matrix_C (%d x %d) = Matrix_A x Matrix_B : \n", c_row_size, c_col_size);
	printMtrx(dMC, c_row_size, c_col_size);
	printf("\n");
	deleteDynamicDoubleMatrix(dMA, a_row_size, a_col_size);
	deleteDynamicDoubleMatrix(dMB, b_row_size, b_col_size);
	deleteDynamicDoubleMatrix(dMC, c_row_size, c_col_size);
	fclose(fin);
}

void test_GaussJordanElimination_LinearSystem(FILE* fout)
{
	const char* augMatrix_inputFile = "AugMtrx_ElectronicCircuit_B_5x5.txt";
	FILE* fin;
	int size_N, row_size, col_size;
	double* solution;
	double** augMtrx = NULL;
	int i, j, solExist = 1, error = 0;
	double d;
	fin = fopen(augMatrix_inputFile, "r"); // "AugMtrx_ElectronicCircuit_B_5x5.txt"������ �б� ���� ����
	if (fin == NULL)
	{
		printf("Error in opening input.txt file (%s)!!\n", augMatrix_inputFile);
		exit(-1);
	}
	fscanf(fin, "%d", &size_N); // ���Ͽ� ����Ǿ��ִ°��� size�� �о����
	augMtrx = createDynamicDoubleMatrix(size_N, size_N + 1); // size_N x size_N+1 �� ÷����� ����
	solution = (double*)calloc(size_N, sizeof(double));
	fprintf(fout, "Augmented Matrix size_N : %d\n", size_N);
	fgetAugmentedMatrixData(fin, augMtrx, size_N); // ÷����Ŀ� ���Ͽ��� �о�� �� ����
	fprintf(fout, "Augmented Matrix : \n");
	fprintMtrx(fout, augMtrx, size_N, size_N + 1);
	printf("Augmented Matrix : \n");
	printMtrx(augMtrx, size_N, size_N + 1);
	diagonalize_FileOut(fout, (double**)augMtrx, size_N, &solExist); //����� �밢ȭ
	if (solExist) {
		fprintf(fout, "\nThe solution of the given linear system:\n");
		printf("\nThe solution of the given linear system:\n");
		for (i = 0; i < size_N; i++) {
			solution[i] = augMtrx[i][size_N];
			fprintf(fout, " x[%d] : %4f\n", i, solution[i]);
			printf(" x[%d] : %4f\n", i, solution[i]);
		}
	}
	else {
		fprintf(fout, "No unique solution\n");
		printf("No unique solution\n");
	}
	printf("\n");
	for (int i = 0; i < size_N; i++)
		free(augMtrx[i]);
	free(augMtrx);
	free(solution);
	fclose(fin);
}

void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout) 
{
	const char* linearSystem_inputFile = "ElectronicCircuit_B_5x5.txt";
	FILE* fin;
	double** mA, ** inv_A, ** res, ** mE;
	int size_N;
	double data;
	fin = fopen(linearSystem_inputFile, "r"); // "ElectronicCircuit_B_5x5.txt"������ �б���� ����
	if (fin == NULL)
	{
		printf("Error in openning %s input file !!\n", linearSystem_inputFile);
		exit(-1);
	}
	fscanf(fin, "%d", &size_N); // ���Ͽ� ����Ǿ��ִ°��� size�� �о����
	mA = (double**)calloc(size_N, sizeof(double*));
	inv_A = (double**)calloc(size_N, sizeof(double*));
	mE = (double**)calloc(size_N, sizeof(double*));
	res = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++)
	{
		mA[i] = (double*)calloc(size_N, sizeof(double));
		mE[i] = (double*)calloc(size_N, sizeof(double));
		inv_A[i] = (double*)calloc(size_N, sizeof(double));
		res[i] = (double*)calloc(size_N, sizeof(double));
	} // 2���� �����迭�� �Ҵ�
	for (int r = 0; r < size_N; r++)
	{
		for (int c = 0; c < size_N; c++)
		{
			fscanf(fin, "%lf", &data);
			mA[r][c] = data;
		}
	} // ������ ���� 2���� �迭�� ���� �о�� ����ֱ�
	for (int i = 0; i < size_N; i++)
	{
		fscanf(fin, "%lf", &data);
		mE[i][0] = data;
	} // ������ ���� 2���� �迭�� ���� �о�� ����ֱ�
	fprintf(fout, "Matrix A: \n");
	fprintMtrx(fout, mA, size_N, size_N);
	printf("Matrix A: \n");
	printMtrx(mA, size_N, size_N);
	invMtrxGaussJordanElim_FileOut(fout, mA, inv_A, size_N); // ����ı��ϱ�
	fprintf(fout, " Inverse A: \n");
	fprintMtrx(fout, inv_A, size_N, size_N);
	printf(" Inverse A: \n");
	printMtrx(inv_A, size_N, size_N);
	fprintf(fout, " mE: \n");
	fprintMtrx(fout, mE, size_N, 1);
	printf(" mE: \n");
	printMtrx(mE, size_N, 1);
	multiplyMatrix(res, inv_A, mE, size_N, size_N, 1); // ����İ� ������� ���ϱ�
	fprintf(fout, " Res = Inv_A x mE: \n");
	fprintMtrx(fout, res, size_N, 1);
	printf(" Res = Inv_A x mE: \n");
	printMtrx(res, size_N, 1);
	fprintf(fout, "\n");
	for (int i = 0; i < size_N; i++)
	{
		free(mA[i]);
		free(mE[i]);
		free(inv_A[i]);
		free(res[i]);
	}
	free(mA);
	free(mE);
	free(inv_A);
	free(res);
	fclose(fin);
}