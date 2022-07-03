/****************************************
* ���ϸ��� : �ؽ������ ���ڿ� ���� �� ���
* �ۼ��� : �ֹ���
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
	MyVoca* pVoca, voca; // MyVoca�� ��������
	List_Str thesaurus, usages; // List_Str�� �������� 
	int word_count;
	MyVoca mv; // MyVoca�� ��������
	string keyWord;
	HashDict<string, MyVoca*> myVocaDict; //���ڿ��� ������  HashDict<string, MyVoca*> �� ��������
	HashDict<string, MyVoca*>::Iterator itr; // HashDict<string, MyVoca*>�� iterator ����
	HashDict<string, MyVoca*>::Range range; // HashDict<string, MyVoca*>�� Range range ����
	Entry<string, MyVoca*> vocaEntry; // Entry<string, MyVoca*>�� vocaEntry����
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
		pVoca = &myToeicVocaList[i]; // &myToeicVocaList[i]�� pVoca�� ����
		keyWord = myToeicVocaList[i].getKeyWord(); //  myToeicVocaList[i]�� key�� keyword�� ����
		myVocaDict.insert(keyWord, pVoca); // myVocaDict�� key�� value�� ����
	}
	fout << "Total " << myVocaDict.size() << " words in my Voca_Dictionary .."<< endl;

	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = itr.getValue(); // myVocaDict�� begin���� end���� ��� value�� ���
		fout << *pVoca << endl;
	}  // myVocaDict�� begin���� end���� ��� value�� ���
	fout << endl;

	myVocaDict.fprintBucketSizes(fout);
	fout << endl;
	//string testWord = "mean";
	string testWord = "offer"; // offer word test
	range = myVocaDict.findAll(testWord); // ��� testWord�� ã�� ������ range�� ����
	fout << "Thesaurus of [" << testWord << "]: \n";
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = itr.getValue(); // range���� ��� value�� ���
		fout << *pVoca << endl;
	}
	fout << endl;
	fout.close();
}