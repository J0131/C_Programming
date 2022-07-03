#include "BigArray_Algorithms.h"

void genRandArray(int array[], int size) // size값이 1000이하일때 난수생성 하여 배열에 저장하는 함수
{
	int d;
	char flag[MAX_NUM_DATA] = { 0 };
	srand((unsigned)time(NULL)); // 시드초기화
	for (int i = 0; i < size; i++)
	{
		d = rand() % size;
		while (flag[d] == 1) // flag[d]의 값이 1이면 난수 다시생성
			d = rand() % size;
		flag[d] = 1;
		array[i] = d;
	}
}
void genBigRandArray(int* bigRandArray, int size, int base)
{
	char* flag; // flag배열 동적할당
	int count = 0;
	unsigned int u_int32 = 0, bigRand, bigRand_withOffset;
	flag = (char*)calloc(size, sizeof(char));
	while (count < size)
	{
		u_int32 = ((long)rand() << 15); // 큰난수생성
		u_int32 = u_int32 + rand();
		bigRand = u_int32 % size; // 정해진 사이즈보다 작게만들어줌
		if (flag[bigRand] == 1)
		{
			continue;
		} // 이미 생성된적이있으면 난수를 다시생성
		else
		{
			flag[bigRand] = 1; // 난수의 위치에해당하는 flag원소를 1로만듬
			bigRand_withOffset = bigRand + base; // 주어진 범위를 만족하기위해 offset을 더해줌
			bigRandArray[count++] = bigRand_withOffset;
		}
	}
	free(flag); // 동적할당해제
}
void fprintBigArraySample(FILE* fout, int* array, int size, int items_per_line, int num_sample_lines)
{
	for (int k = 0, count = 0; k < num_sample_lines; k++)
	{
		fprintf(fout, "%10d ", array[k]);
		count++;
		if (count % items_per_line == 0)
			fprintf(fout, "\n");
	}
	fprintf(fout, "   . . . . .\n");
	for (int j = num_sample_lines, count = 0; j > 0; j--)
	{
		fprintf(fout, "%10d ", array[size - j]);
		count++;
		if (count % items_per_line == 0)
			fprintf(fout, "\n");
	}
}

void printBigArraySample(int* array, int size, int items_per_line, int num_sample_lines)
{
	for (int k = 0, count = 0; k < num_sample_lines; k++)
	{
		printf("%10d ", array[k]);
		count++;
		if (count % items_per_line == 0)
			printf("\n");
	}
	printf("   . . . . .\n");
	for (int j = num_sample_lines, count = 0; j > 0; j--)
	{
		printf("%10d ", array[size - j]);
		count++;
		if (count % items_per_line == 0)
			printf("\n");
	}
}



void hybridQuickSelectionSort(int* array, int size)// 하이브리드 퀵정렬
{// size가 50보다적으면 주어진 배열을 선택정렬로 정렬하고 50보다크면 퀵정렬로 정렬함
	if (size < QUICK_SELECTION_THRESHOLD)
	{
		int index_min;
		int minElement;
		for (int round = 0; round < size - 1; round++)
		{
			index_min = round;
			minElement = array[round];
			for (int j = round + 1; j < size; j++)
			{
				if (array[j] < minElement)
				{
					index_min = j;
					minElement = array[j];
				}
			}
			if (index_min != round)
			{
				array[index_min] = array[round];
				array[round] = minElement;
			}
		}
	} // 50보다 작으면 선택정렬
	else
	{
		_hybridQuickSelectionSort(array, size, 0, size - 1, 0);
	} // 50보다크면 퀵정렬
}

void _hybridQuickSelectionSort(int array[], int size, int left, int right, int level)
{
	int pI, newPI;
	int pivotValue;
	int temp, i;
	if (left >= right) {
		return;
	}
	else if (left < right)
	{
		pI = (left + right) / 2;
	}
	pivotValue = array[pI];
	temp = array[pI];
	array[pI] = array[right];
	array[right] = temp;
	newPI = left;
	for (i = left; i <= (right - 1); i++) {
		if (array[i] <= pivotValue) {
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;
			newPI = newPI + 1;
		}
	}
	temp = array[newPI];
	array[newPI] = array[right];
	array[right] = temp;
	if (left < (newPI - 1))
	{
		_hybridQuickSelectionSort(array, size, left, newPI - 1, level + 1);
	}
	if ((newPI + 1) < right)
	{
		_hybridQuickSelectionSort(array, size, newPI + 1, right, level + 1);
	}
}

void selectionsort(int array[],int size)
{
	int index_min;
	int minElement;
	for (int round = 0; round < size - 1; round++)
	{
		index_min = round;
		minElement = array[round];
		for (int j = round + 1; j < size; j++)
		{
			if (array[j] < minElement)
			{
				index_min = j;
				minElement = array[j];
			}
		}
		if (index_min != round)
		{
			array[index_min] = array[round];
			array[round] = minElement;
		}
	}
}

void QuickSelectionSort(int array[], int size, int left, int right, int level)
{
	int pI, newPI;
	int pivotValue;
	int temp, i;
	if (left >= right) {
		return;
	}
	else if (left < right)
	{
		pI = (left + right) / 2;
	}
	pivotValue = array[pI];
	temp = array[pI];
	array[pI] = array[right];
	array[right] = temp;
	newPI = left;
	for (i = left; i <= (right - 1); i++) {
		if (array[i] <= pivotValue) {
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;
			newPI = newPI + 1;
		}
	}
	temp = array[newPI];
	array[newPI] = array[right];
	array[right] = temp;
	if (left < (newPI - 1))
	{
		QuickSelectionSort(array, size, left, newPI - 1, level + 1);
	}
	if ((newPI + 1) < right)
	{
		QuickSelectionSort(array, size, newPI + 1, right, level + 1);
	}
}

void suffleArray(int array[], int size)
{
	int i1, i2, d;
	srand((unsigned)time(NULL));
	for (int i = 0; i < size / 2; i++)
	{
		i1 = rand() % size;
		i2 = rand() % size;
		d = array[i1];
		array[i1] = array[i2];
		array[i2] = d; // 배열의 원소를 뒤바꿔줌
	}
}