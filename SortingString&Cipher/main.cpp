/*************************************************
* 파일목적 : 텍스트를 암호화하고 복호화하는 프로그램 구현
* 작성자 : 최범준
* final update : 2020-06-04
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MyString.h"
#include "Student.h"
#include "HandlingBinaryFile.h"
#include "CipherMessage.h"
#define MAX_WORD_LEN 20

void test_SelectionSortWords(); // 단어를 선택정렬하는 기능
void test_RandomFileAccess_Student(); // 학생에대한 정보에 랜덤으로 접근하는기능
void test_BinaryFileDump(); // 파일을 이진데이터로 출력하는기능
void test_simple_cipher_text(); // 텍스트안에있는 내용을 암호화,복호화하는기능
void main()
{
    int menu;
    while (1)
    {
        printf(" 1. Test selection sort for words\n");
        printf(" 2. Test random access file for students records\n");
        printf(" 3. Test binary file dump\n");
        printf(" 4. Test cipher text\n");
        printf("-1. Quit\n");
        printf("Input menu : ");
        scanf("%d", &menu); // 원하는 메뉴를 입력받음
        if (menu == -1)
            break;
        switch (menu)
        {
        case 1:
            test_SelectionSortWords();
            break;
        case 2:
            test_RandomFileAccess_Student();
            break;
        case 3:
            test_BinaryFileDump();
            break;
        case 4:
            test_simple_cipher_text();
            break;
        default:
            break;
        } // 입력받은 수에 따른 함수실행
    }
}

void test_SelectionSortWords()
{
    FILE* fin, * fout; // 파일포인터 선언
    fin = fopen("words.txt", "r"); // words.txt를 읽기모드로 열기
    fout = fopen("sorted_words.txt", "w"); // sorted_words.txt를 쓰기모드로 열기
    int num = 0;
    char** word_array; // 문자열배열로 사용할 2차원 포인터 word_array 선언
    char voc[MAX_WORD_LEN]; // 문자열로 사용할 1차원 배열 voc 선언
    word_array = (char**)calloc(1000, sizeof(char*)); 
    for (int i = 0; i < 1000; i++)
    {
        word_array[i] = (char*)calloc(MAX_WORD_LEN, sizeof(char));
    } // 2차원 동적배열할당
    while (fscanf(fin, "%s", &voc) != EOF) // words.txt안의 문자열을 입력받아 voc에저장, voc값이 파일의 끝이 아닐때까지 반복
    {
        strcpy(word_array[num], voc); // voc를 word_array[num]에 넣어준다
        num++;
    }
    selectionSortWords(word_array, num, MAX_WORD_LEN); // 문자열배열 선택정렬
    fprintWordArray(fout, word_array, num); // 파일에 출력
    
}

void test_RandomFileAccess_Student()
{
    FILE* fin, * fout; // 파일포인터 선언
    STUDENT* pST; // STUDENT구조체형 포인터선언
    int record_len;
    char student_record[MAX_STRING_LEN] = { 0 };
    fout = fopen("Sorted_Students.txt", "w"); // Sorted_Students.txt을 읽기모드로 열기
    if (fout == NULL)
    {
        printf("Error in opening Sorted_Students.txt (write mode)!!\n");
        exit;
    }
    printf("Array of students at initialization : \n");
    printStudents(students, NUM_STUDENTS); //students배열내 학생들의 정보를 화면에 출력
    printf("\n");
    selectionSortStudents_by_ST_ID(students, NUM_STUDENTS); // students배열을 오름차순으로 선택정렬
    printf("Storing sorted students by increasing order of student ID into SortedStudent.txt ....\n");
    fprintStudents(fout, students, NUM_STUDENTS); // 학생들의 정보를 파일에 출력
    printStudents(students, NUM_STUDENTS); // 학생들의 정보를 화면에 출력
    fprintf(fout, "\n");
    fclose(fout);
    fin = fopen("Sorted_Students.txt", "r"); // Sorted_Students.txt을 읽기모드로 열기
    if (fin == NULL)
    {
        printf("Error in opening Sorted_Students.txt (read mode)!!\n");
        exit;
    }
    int cur_pos;
    fgets(student_record, MAX_STRING_LEN, fin); //Sorted_Students.txt파일에서 한줄을읽어 student_record배열에 저장
    record_len = strlen(student_record); // 한줄의 길이를 저장
    rewind(fin); // 파일의 포인터를 파일의 시작위치로 이동
    printf("\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n",record_len);
    for (int i = NUM_STUDENTS - 1; i >= 0; i--)
    {
        fseek(fin, (record_len + 1) * i, SEEK_SET); // 파일의 처음부터 (record_len + 1) * i만큼 이동
        cur_pos = ftell(fin); // 파일포인터의 현재위치를 cur_pos에저장
        printf("Current file_position : %3d\n", cur_pos);
        fgets(student_record, MAX_STRING_LEN, fin); // //Sorted_Students.txt파일에서 cur_pos위치의 한줄을읽어 student_record배열에 저장
        printf("Student (%2d): %s", i, student_record);
    }
    fclose(fin);
}

void test_BinaryFileDump()
{
    FILE* fin, * fout;
    const char* fname = "Sorted_Students.txt"; 

    if ((fin = fopen(fname, "rb")) == NULL)
    {
        printf("Error - binary input file (%s) cannot be openned !!\n", fname);
        exit;
    } // Sorted_Students.txt 파일을 이진파일 읽기모드로 연다
    if ((fout = fopen("Output.txt", "w")) == NULL)
    {
        printf("Error - Output.txt cannot be created !!\n");
        exit;
    } // Output.txt파일을 쓰기모드로 연다
    printf("Dumping binary file (%s) ... \n", fname);
    dumpBinaryFile(fin, fout); // Sorted_Students.txt파일안의 데이터를 이진데이터로 변환하여 Output.txt에 출력
    fclose(fin);
    fclose(fout);
}

void test_simple_cipher_text()
{
    FILE* fp_msg, * fp_tx, * fp_rx, * fp_dump_msg, * fout;
    fp_msg = fopen("Message.txt", "r");// Message.txt파일 읽기모드로 열기
    if (fp_msg == NULL)
    {
        printf("Error in file open - Message.txt !!\n");
        exit(-1);
    }
    fp_tx = fopen("Ciphered.txt", "w"); // Ciphered.txt파일 쓰기모드로 열기
    if (fp_tx == NULL)
    {
        printf("Error in file open - Ciphered.txt !!\n");
        exit(-1);
    }
    fout = fopen("Output.txt", "w"); // Output.txt파일 쓰기모드로 열기
    if (fout == NULL)
    {
        printf("Error in file open - Output.txt !!\n");
        exit(-1);
    }
    printf("Generating cipher text with cipher-code (%#04x) ..\n", CIPHER_CODE);
    cipherText(fp_msg, fp_tx, CIPHER_CODE); //Message.txt에 저장되어있는 데이터를 암호화하여 Ciphered.txt에 저장
    fclose(fp_tx); // Ciphered.txt 파일 닫기
    rewind(fp_msg); // 파일포인터 초기화
    fprintf(fout, "Binary dump of message.txt file: \n");
    dumpBinaryFile(fp_msg, fout); // Message.txt파일을 이진데이터로 변환하여 Output.txt 파일에출력
    fp_tx = fopen("Ciphered.txt", "r"); // Ciphered.txt파일을 읽기모드로 열기
    if (fp_tx == NULL)
    {
        printf("Error in file open - Ciphered.txt !!\n");
        exit(-1);
    }
    fprintf(fout, "\n=========================================\n");
    fprintf(fout, "Binary dump of ciphered document: \n");
    dumpBinaryFile(fp_tx, fout); //  Ciphered.txt파일의 데이터를 이진데이터로 변환하여 Output.txt 파일에출력
    rewind(fp_msg);// 
    printf("Generating de-ciphered text with cipher-code (%#04x) ..\n", CIPHER_CODE);
    fprintf(fout, "\n=========================================\n");
    fprintf(fout, "Generating de-ciphered text with cipher-code (%#04x) ..\n",CIPHER_CODE);
    fclose(fp_tx);// Ciphered.txt파일닫기
    fp_tx = fopen("Ciphered.txt", "r"); // Ciphered.txt파일을 읽기모드로 열기
    deCipherText(fp_tx, fout, CIPHER_CODE); // Ciphered.txt파일의 데이터를 복호화하여 Output.txt파일에 출력
    fclose(fp_msg);
    fclose(fp_tx);
    fclose(fout); // 파일닫기
}


