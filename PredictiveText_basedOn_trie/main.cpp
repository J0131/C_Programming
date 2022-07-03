/***********************************
* 파일목적 : 트라이기반의 문자열 정렬 및 탐색 프로그램
* 작성자 : 최범준
* final update : 2020.11.27
*************************************/
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "MyVoca.h"
#include "MyVocaList.h"
#include "Trie.h"
#include "TrieNode.h"

using namespace std;
#define MAX_WORD_LENGTH 100
#define NUM_TEST_VOCAS 7


void main()
{
	ofstream fout; // 파일 스트림
	fout.open("output.txt"); // 파일열기
	if (fout.fail())
	{
		printf("Error in opening output file! \n");
		exit;
	}

	Trie<MyVoca*> trie_myVoca("Trie_MyVoca"); // Trie<MyVoca*>형의 trie_myVoca생성
	Trie<MyVoca*> *pTN; // Trie<MyVoca*> * 형의 pTN 생성
	MyVoca* pVoca;
	int word_count;
	string keyStr;
	char keyWord[MAX_WORD_LENGTH];
	List_pVoca predictVocas;
	List_pVoca_Iter itr; // 각각의 변수 선언

	MyVoca testVocas[NUM_TEST_VOCAS] =
	{
		MyVoca("xyz",NOUN,{""},{""}),
		MyVoca("ABCD",NOUN,{""},{""}),
		MyVoca("ABC",NOUN,{""},{""}),
		MyVoca("AB",NOUN,{""},{""}),
		MyVoca("A",NOUN,{""},{""}),
		MyVoca("xy",NOUN,{""},{""}),
		MyVoca("x",NOUN,{""},{""}),
	}; // testVocas 다음과 같은 정보로 초기화
	fout << "Testing basic operations of trie inserting ... ... " << endl;
	for (int i = 0; i < NUM_TEST_VOCAS; i++)
	{
		trie_myVoca.insert(testVocas[i].getKeyWord(), &testVocas[i]); // testVocas[i]의 keyword들을 trie_myVoca에 삽입
	}
	trie_myVoca.fprintTrie(fout); // trie_myVoca 출력

	fout << "\n Testing TrieDestroy ... \n";
	trie_myVoca.eraseTrie(); // trie_myVoca삭제 
	trie_myVoca.fprintTrie(fout); // trie_myVoca 출력

	fout << "Inserting My Vocabularies to myVocaDict ... " << endl;
	word_count = 0;
	pVoca = &myToeicVocaList[0]; // &myToeicVocaList[0]를 pVoca로 저장

	while (pVoca->getKeyWord() != "") // pVoca->getKeyWord()가 null이 아닌동안
	{
		keyStr = pVoca->getKeyWord(); // pVoca의 key를 keyStr에저장
		trie_myVoca.insert(keyStr, pVoca); // trie_myVoca에 keyStr를 삽입
		pVoca++;
	}
	fout << "Total" << trie_myVoca.size() << "words in trie_myVoca .. " << endl;
	trie_myVoca.fprintTrie(fout); // trie_myVoca 출력

	while (1) // 무한반복
	{
		cout << "\n Input any prefix to search in trie (. to finish) : "; // 찾고자하는 prefix 입력
		cin >> keyStr; // keyStr로 받기
		if (keyStr == string(".")) //  keyStr이 .이면 반복문 나가기
			break;
		predictVocas.clear();
		trie_myVoca.findPrefixMatch(keyStr, predictVocas); // trie_myVoca에 keyStr의 prefix들을 찾아  predictVocas에 저장
		cout << "list of predictive words with prefix (" << keyStr << ") :" << endl;
		itr = predictVocas.begin(); // predictVocas.begin()를 itr로 저장
		for (int i = 0; i < predictVocas.size(); i++)
		{
			pVoca = *itr; // *itr를 pVoca로 저장
			cout << *pVoca << endl; // *pVoca 차례대로 출력
			++itr;
		}
	}
	cout << "\nErasing trie_myVoca .... " << endl;
	fout << "\nErasing trie_myVoca .... " << endl;
	trie_myVoca.eraseTrie();

	fout.close();
}