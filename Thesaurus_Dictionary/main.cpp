/****************************************
* 파일목적 : 해쉬기반의 문자열 정렬 및 출력
* 작성자 : 최범준
* final update : 2020.11.19
*****************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.h"
#include "HashMap.cpp"
#include "CyclicShiftHashCode.h"
#include "Entry.h"
#include "HashDictionary.h"
#include "MyVoca.h"
#include "MyVocaList.h"
void main()
{
	ofstream fout;
	MyVoca* pVoca, voca; // MyVoca형 변수선언
	List_Str thesaurus, usages; // List_Str형 변수선언 
	int word_count;
	MyVoca mv; // MyVoca형 변수선언
	string keyWord;
	HashDict<string, MyVoca*> myVocaDict; //문자열을 저장할  HashDict<string, MyVoca*> 형 변수선언
	HashDict<string, MyVoca*>::Iterator itr; // HashDict<string, MyVoca*>의 iterator 선언
	HashDict<string, MyVoca*>::Range range; // HashDict<string, MyVoca*>의 Range range 선언
	Entry<string, MyVoca*> vocaEntry; // Entry<string, MyVoca*>형 vocaEntry선언
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt !!" << endl;
		exit;
	}
	fout << "Inserting My Vocabularies to myVocaDict . . . " << endl;
	word_count = 0;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++) 
	{ 
		pVoca = &myToeicVocaList[i]; // &myToeicVocaList[i]를 pVoca에 저장
		keyWord = myToeicVocaList[i].getKeyWord(); //  myToeicVocaList[i]의 key를 keyword에 저장
		myVocaDict.insert(keyWord, pVoca); // myVocaDict에 key와 value를 삽입
	}
	fout << "Total " << myVocaDict.size() << " words in my Voca_Dictionary .."<< endl;

	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = itr.getValue(); // myVocaDict의 begin부터 end까지 모든 value를 출력
		fout << *pVoca << endl;
	}  // myVocaDict의 begin부터 end까지 모든 value를 출력
	fout << endl;

	myVocaDict.fprintBucketSizes(fout);
	fout << endl;
	//string testWord = "mean";
	string testWord = "offer"; // offer word test
	range = myVocaDict.findAll(testWord); // 모든 testWord를 찾아 구역을 range로 설정
	fout << "Thesaurus of [" << testWord << "]: \n";
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = itr.getValue(); // range내의 모든 value를 출력
		fout << *pVoca << endl;
	}
	fout << endl;
	fout.close();
}