#ifndef MYSTRING_H
#define MYSTRING_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void selectionSortWords(char** words, int num_words, int max_word_len); // 단어를 선택정렬하는 함수
void fprintWordArray(FILE* fout, char **wordList, int size); // 파일에 단어를 출력해주는 함수

#endif MYSTRING_H