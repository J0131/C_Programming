#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define QUICK_SELECTION_THRESHOLD 50
#define MAX_NUM_DATA 100
#define ITEMS_PER_LINE 10
#define NUM_SAMPLE_LINES 30


void genBigRandArray(int* bigRandArray, int size, int base);
void fprintBigArraySample(FILE* fout, int* array, int size, int items_per_line, int num_sample_lines);
void printBigArraySample(int* array, int size, int items_per_line, int num_sample_lines);
void hybridQuickSelectionSort(int* array, int size);
void _hybridQuickSelectionSort(int array[], int size, int left, int right, int level);
void genRandArray(int array[], int size);
void selectionsort(int array[], int size);
void QuickSelectionSort(int array[], int size, int left, int right, int level);
void suffleArray(int array[], int size);
