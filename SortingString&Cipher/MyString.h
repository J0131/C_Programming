#ifndef MYSTRING_H
#define MYSTRING_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void selectionSortWords(char** words, int num_words, int max_word_len); // �ܾ ���������ϴ� �Լ�
void fprintWordArray(FILE* fout, char **wordList, int size); // ���Ͽ� �ܾ ������ִ� �Լ�

#endif MYSTRING_H