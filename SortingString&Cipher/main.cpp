/*************************************************
* ���ϸ��� : �ؽ�Ʈ�� ��ȣȭ�ϰ� ��ȣȭ�ϴ� ���α׷� ����
* �ۼ��� : �ֹ���
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

void test_SelectionSortWords(); // �ܾ ���������ϴ� ���
void test_RandomFileAccess_Student(); // �л������� ������ �������� �����ϴ±��
void test_BinaryFileDump(); // ������ ���������ͷ� ����ϴ±��
void test_simple_cipher_text(); // �ؽ�Ʈ�ȿ��ִ� ������ ��ȣȭ,��ȣȭ�ϴ±��
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
        scanf("%d", &menu); // ���ϴ� �޴��� �Է¹���
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
        } // �Է¹��� ���� ���� �Լ�����
    }
}

void test_SelectionSortWords()
{
    FILE* fin, * fout; // ���������� ����
    fin = fopen("words.txt", "r"); // words.txt�� �б���� ����
    fout = fopen("sorted_words.txt", "w"); // sorted_words.txt�� ������� ����
    int num = 0;
    char** word_array; // ���ڿ��迭�� ����� 2���� ������ word_array ����
    char voc[MAX_WORD_LEN]; // ���ڿ��� ����� 1���� �迭 voc ����
    word_array = (char**)calloc(1000, sizeof(char*)); 
    for (int i = 0; i < 1000; i++)
    {
        word_array[i] = (char*)calloc(MAX_WORD_LEN, sizeof(char));
    } // 2���� �����迭�Ҵ�
    while (fscanf(fin, "%s", &voc) != EOF) // words.txt���� ���ڿ��� �Է¹޾� voc������, voc���� ������ ���� �ƴҶ����� �ݺ�
    {
        strcpy(word_array[num], voc); // voc�� word_array[num]�� �־��ش�
        num++;
    }
    selectionSortWords(word_array, num, MAX_WORD_LEN); // ���ڿ��迭 ��������
    fprintWordArray(fout, word_array, num); // ���Ͽ� ���
    
}

void test_RandomFileAccess_Student()
{
    FILE* fin, * fout; // ���������� ����
    STUDENT* pST; // STUDENT����ü�� �����ͼ���
    int record_len;
    char student_record[MAX_STRING_LEN] = { 0 };
    fout = fopen("Sorted_Students.txt", "w"); // Sorted_Students.txt�� �б���� ����
    if (fout == NULL)
    {
        printf("Error in opening Sorted_Students.txt (write mode)!!\n");
        exit;
    }
    printf("Array of students at initialization : \n");
    printStudents(students, NUM_STUDENTS); //students�迭�� �л����� ������ ȭ�鿡 ���
    printf("\n");
    selectionSortStudents_by_ST_ID(students, NUM_STUDENTS); // students�迭�� ������������ ��������
    printf("Storing sorted students by increasing order of student ID into SortedStudent.txt ....\n");
    fprintStudents(fout, students, NUM_STUDENTS); // �л����� ������ ���Ͽ� ���
    printStudents(students, NUM_STUDENTS); // �л����� ������ ȭ�鿡 ���
    fprintf(fout, "\n");
    fclose(fout);
    fin = fopen("Sorted_Students.txt", "r"); // Sorted_Students.txt�� �б���� ����
    if (fin == NULL)
    {
        printf("Error in opening Sorted_Students.txt (read mode)!!\n");
        exit;
    }
    int cur_pos;
    fgets(student_record, MAX_STRING_LEN, fin); //Sorted_Students.txt���Ͽ��� �������о� student_record�迭�� ����
    record_len = strlen(student_record); // ������ ���̸� ����
    rewind(fin); // ������ �����͸� ������ ������ġ�� �̵�
    printf("\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n",record_len);
    for (int i = NUM_STUDENTS - 1; i >= 0; i--)
    {
        fseek(fin, (record_len + 1) * i, SEEK_SET); // ������ ó������ (record_len + 1) * i��ŭ �̵�
        cur_pos = ftell(fin); // ������������ ������ġ�� cur_pos������
        printf("Current file_position : %3d\n", cur_pos);
        fgets(student_record, MAX_STRING_LEN, fin); // //Sorted_Students.txt���Ͽ��� cur_pos��ġ�� �������о� student_record�迭�� ����
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
    } // Sorted_Students.txt ������ �������� �б���� ����
    if ((fout = fopen("Output.txt", "w")) == NULL)
    {
        printf("Error - Output.txt cannot be created !!\n");
        exit;
    } // Output.txt������ ������� ����
    printf("Dumping binary file (%s) ... \n", fname);
    dumpBinaryFile(fin, fout); // Sorted_Students.txt���Ͼ��� �����͸� ���������ͷ� ��ȯ�Ͽ� Output.txt�� ���
    fclose(fin);
    fclose(fout);
}

void test_simple_cipher_text()
{
    FILE* fp_msg, * fp_tx, * fp_rx, * fp_dump_msg, * fout;
    fp_msg = fopen("Message.txt", "r");// Message.txt���� �б���� ����
    if (fp_msg == NULL)
    {
        printf("Error in file open - Message.txt !!\n");
        exit(-1);
    }
    fp_tx = fopen("Ciphered.txt", "w"); // Ciphered.txt���� ������� ����
    if (fp_tx == NULL)
    {
        printf("Error in file open - Ciphered.txt !!\n");
        exit(-1);
    }
    fout = fopen("Output.txt", "w"); // Output.txt���� ������� ����
    if (fout == NULL)
    {
        printf("Error in file open - Output.txt !!\n");
        exit(-1);
    }
    printf("Generating cipher text with cipher-code (%#04x) ..\n", CIPHER_CODE);
    cipherText(fp_msg, fp_tx, CIPHER_CODE); //Message.txt�� ����Ǿ��ִ� �����͸� ��ȣȭ�Ͽ� Ciphered.txt�� ����
    fclose(fp_tx); // Ciphered.txt ���� �ݱ�
    rewind(fp_msg); // ���������� �ʱ�ȭ
    fprintf(fout, "Binary dump of message.txt file: \n");
    dumpBinaryFile(fp_msg, fout); // Message.txt������ ���������ͷ� ��ȯ�Ͽ� Output.txt ���Ͽ����
    fp_tx = fopen("Ciphered.txt", "r"); // Ciphered.txt������ �б���� ����
    if (fp_tx == NULL)
    {
        printf("Error in file open - Ciphered.txt !!\n");
        exit(-1);
    }
    fprintf(fout, "\n=========================================\n");
    fprintf(fout, "Binary dump of ciphered document: \n");
    dumpBinaryFile(fp_tx, fout); //  Ciphered.txt������ �����͸� ���������ͷ� ��ȯ�Ͽ� Output.txt ���Ͽ����
    rewind(fp_msg);// 
    printf("Generating de-ciphered text with cipher-code (%#04x) ..\n", CIPHER_CODE);
    fprintf(fout, "\n=========================================\n");
    fprintf(fout, "Generating de-ciphered text with cipher-code (%#04x) ..\n",CIPHER_CODE);
    fclose(fp_tx);// Ciphered.txt���ϴݱ�
    fp_tx = fopen("Ciphered.txt", "r"); // Ciphered.txt������ �б���� ����
    deCipherText(fp_tx, fout, CIPHER_CODE); // Ciphered.txt������ �����͸� ��ȣȭ�Ͽ� Output.txt���Ͽ� ���
    fclose(fp_msg);
    fclose(fp_tx);
    fclose(fout); // ���ϴݱ�
}


