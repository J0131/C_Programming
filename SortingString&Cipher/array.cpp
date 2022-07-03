#include "MyString.h"

void selectionSortWords(char** words, int num_words, int max_word_len)
{
	char* temp_word; // �ӽ÷� ���ڿ��� �����ҹ迭�� ����� �����ͼ���
	int i, j, min; 
	temp_word = (char*)calloc(max_word_len, sizeof(char)); // char���� 1�����迭�� �������� �Ҵ�
	if (temp_word == NULL)
	{
		printf("Error in dynamic allocation of memory for temp_word !!	\n");
		exit;
	}
	for (i = 0; i < num_words; i++)
	{
		strcpy(temp_word, words[i]); // words[i]�� ���� temp_word�� �־���
		min = i;// �ʱ� �ּҰ��� ��ġ = i
		for (j = i + 1; j < num_words; j++)
		{
			if (strcmp(temp_word, words[j]) > 0) 
			{
				min = j; // temp_word�� words[j]���� ũ�ٸ� �ּҰ��� ��ġ�� j
				strcpy(temp_word, words[j]);// temp_word�� words[j]���� ũ�ٸ� temp_word�� words[j]���ȴ�
			}
		}
		if (min != i)
		{ 
			strcpy(words[min], words[i]); // words[i]�� ���� words[min]�� �־��ش�
			strcpy(words[i], temp_word); //  temp_word�� ���� words[i]�� �־��ش�
		}
	}
}

void fprintWordArray(FILE* fout, char **wordList, int size)
{
	for (int i = 0, count = 0; i < size; i++)
	{
		fprintf(fout, "%-15s", wordList[i]);
		count++;
		if (count % 10 == 0)
			fprintf(fout, "\n"); // 10����ŭ ����ϰ� �ٶ��
	}
	fprintf(fout, "\n");
}