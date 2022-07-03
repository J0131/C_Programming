#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "BigArray_Algorithms.h"


#define MAX_NUM_DATA 100
#define ESC 0x1B
void Compare_Sorting_Algorithms_SmallIntArray(FILE* fout);
void testBigRandArray(FILE* fout);
void PM_Hybrid_QS_SS_IntArray(FILE* fout);

int main()
{
    FILE* fout;
    int * bigRandArray;
    int key_to_search;
    int pos;
    int num_data = 0;
    int menu;

    fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Error in creation of array_output.txt !!\n");
        return -1;
    }
    srand(time(0));
    while (1)
    {
        printf("\nTest Array Algorithms :\n");
        printf(" 1: Performance Comparison of Selection Sort and Quick Sort for Small Integer Array\n");
        printf(" 2: Test Big Rand Array (Array Size: 1,000,000 ~ 10,000,000)\n");
        printf(" 3: Performance Measurements of hybrid_QS_SS for IntegerArray\n");
        printf("Input menu (-1 to terminate) : ");
        scanf("%d", &menu);
        //printf("\n");
        if (menu == -1)
            break;
        switch (menu)
        {
        case 1:
            Compare_Sorting_Algorithms_SmallIntArray(fout);
            break;
        case 2:
            testBigRandArray(fout);
            break;
        case 3:
            PM_Hybrid_QS_SS_IntArray(fout);
            break;

        default:
            break;
        }
        fflush(fout);
    }
    fclose(fout);
    return 0;
}
// 다양한 시험을 위한 함수는 이곳에 구현할 것.
void Compare_Sorting_Algorithms_SmallIntArray(FILE* fout)
{ 
    int data_array[MAX_NUM_DATA];
    LARGE_INTEGER freq, t_before_sel, t_after_sel;
    LARGE_INTEGER t_before_qck, t_after_qck;
    LONGLONG t_diff_sel, t_diff_qck;
    double elapsed_time_sel,elapsed_time_qck;
    QueryPerformanceFrequency(&freq);
    for (int array_size = 5; array_size <= 100; array_size += 5)
    {
        genRandArray(data_array, array_size);
        printf("Sorting of an tnteger array (size:%4d) :", array_size);
        fprintf(fout,"Sorting of an tnteger array (size:%4d) :", array_size);
        QueryPerformanceCounter(&t_before_qck);
        QuickSelectionSort(data_array, array_size, 0, array_size - 1, 0);
        QueryPerformanceCounter(&t_after_qck);
        t_diff_qck = t_after_qck.QuadPart - t_before_qck.QuadPart;
        elapsed_time_qck = ((double)t_diff_qck / freq.QuadPart);
        printf("Quick_Sort took %8.2lf[micro-seconds],", elapsed_time_qck*1000000.0);
        fprintf(fout,"Quick_Sort took %8.2lf[micro-seconds],", elapsed_time_qck*1000000.0);
        suffleArray(data_array,array_size);
        QueryPerformanceCounter(&t_before_sel);
        selectionsort(data_array, array_size);
        QueryPerformanceCounter(&t_after_sel);
        t_diff_sel = t_after_sel.QuadPart - t_before_sel.QuadPart;
        elapsed_time_sel = ((double)t_diff_sel / freq.QuadPart);
        printf("Selection_Sort took %8.2lf[micro-seconds],\n", elapsed_time_sel * 1000000.0);
        fprintf(fout,"Selection_Sort took %8.2lf[micro-seconds],\n", elapsed_time_sel * 1000000.0);

    }
    
}
void testBigRandArray(FILE* fout)
{
    int* bigRandArray;
    for (int array_size = 5000000; array_size <= 10000000; array_size += 5000000)
    {
        bigRandArray = (int*)calloc(sizeof(int), array_size); // array_size만큼 동적할당
        genBigRandArray(bigRandArray, array_size, -array_size / 2);
        printf("Generated big random number array (size: %d):\n", array_size);
        printBigArraySample(bigRandArray, array_size, ITEMS_PER_LINE, NUM_SAMPLE_LINES);
        fprintf(fout, "Generated big random number array (size: %d):\n", array_size);
        fprintBigArraySample(fout, bigRandArray, array_size, ITEMS_PER_LINE, NUM_SAMPLE_LINES);
        hybridQuickSelectionSort(bigRandArray, array_size);
        printf("Sorting Big integer Array (size: %d):\n", array_size);
        printBigArraySample(bigRandArray, array_size, ITEMS_PER_LINE, NUM_SAMPLE_LINES);
        fprintf(fout, "Sorting Big integer Array (size: %d):\n", array_size);
        fprintBigArraySample(fout, bigRandArray, array_size, ITEMS_PER_LINE, NUM_SAMPLE_LINES);
        free(bigRandArray);
    }
}
void PM_Hybrid_QS_SS_IntArray(FILE* fout)
{
    LARGE_INTEGER freq, t_before, t_after;
    LONGLONG t_diff;
    double elapsed_time;
    QueryPerformanceFrequency(&freq);
    int* bigRandArray;
    for (int array_size = 1000000; array_size <= 10000000; array_size += 1000000)
    {
        bigRandArray = (int*)calloc(sizeof(int), array_size); // array_size만큼 동적할당
        genBigRandArray(bigRandArray, array_size, -array_size / 2); // -array_size / 2 ~ array_size / 2만큼의 범위를갖는 난수배열생성
        QueryPerformanceCounter(&t_before);
        hybridQuickSelectionSort(bigRandArray, array_size);
        QueryPerformanceCounter(&t_after);
        t_diff = t_after.QuadPart - t_before.QuadPart; // 시간차이계산
        elapsed_time = ((double)t_diff / freq.QuadPart);
        printf("Hybrid_QS_SS Sorting of an integer array (size : %10d) : ",array_size);
        fprintf(fout,"Hybrid_QS_SS Sorting of an integer array (size : %10d) : ", array_size);
        printf("Hybrid_QS_SS Sorting took % 8.2f[millisecond]\n", elapsed_time * 1000.0);
        fprintf(fout,"Hybrid_QS_SS Sorting took % 8.2f[millisecond]\n", elapsed_time * 1000.0);
        free(bigRandArray); // 동적할당해제
    }
}