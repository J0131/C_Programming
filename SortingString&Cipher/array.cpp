#include "MyString.h"

void selectionSortWords(char** words, int num_words, int max_word_len)
{
	char* temp_word; // 임시로 문자열을 저장할배열로 사용할 포인터선언
	int i, j, min; 
	temp_word = (char*)calloc(max_word_len, sizeof(char)); // char형의 1차원배열을 동적으로 할당
	if (temp_word == NULL)
	{
		printf("Error in dynamic allocation of memory for temp_word !!	\n");
		exit;
	}
	for (i = 0; i < num_words; i++)
	{
		strcpy(temp_word, words[i]); // words[i]의 값을 temp_word에 넣어줌
		min = i;// 초기 최소값의 위치 = i
		for (j = i + 1; j < num_words; j++)
		{
			if (strcmp(temp_word, words[j]) > 0) 
			{
				min = j; // temp_word가 words[j]보다 크다면 최소값의 위치는 j
				strcpy(temp_word, words[j]);// temp_word가 words[j]보다 크다면 temp_word는 words[j]가된다
			}
		}
		if (min != i)
		{ 
			strcpy(words[min], words[i]); // words[i]의 값을 words[min]에 넣어준다
			strcpy(words[i], temp_word); //  temp_word의 값을 words[i]에 넣어준다
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
			fprintf(fout, "\n"); // 10개만큼 출력하고 줄띄움
	}
	fprintf(fout, "\n");
}