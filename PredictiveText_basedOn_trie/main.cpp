/***********************************
* ���ϸ��� : Ʈ���̱���� ���ڿ� ���� �� Ž�� ���α׷�
* �ۼ��� : �ֹ���
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
	ofstream fout; // ���� ��Ʈ��
	fout.open("output.txt"); // ���Ͽ���
	if (fout.fail())
	{
		printf("Error in opening output file! \n");
		exit;
	}

	Trie<MyVoca*> trie_myVoca("Trie_MyVoca"); // Trie<MyVoca*>���� trie_myVoca����
	Trie<MyVoca*> *pTN; // Trie<MyVoca*> * ���� pTN ����
	MyVoca* pVoca;
	int word_count;
	string keyStr;
	char keyWord[MAX_WORD_LENGTH];
	List_pVoca predictVocas;
	List_pVoca_Iter itr; // ������ ���� ����

	MyVoca testVocas[NUM_TEST_VOCAS] =
	{
		MyVoca("xyz",NOUN,{""},{""}),
		MyVoca("ABCD",NOUN,{""},{""}),
		MyVoca("ABC",NOUN,{""},{""}),
		MyVoca("AB",NOUN,{""},{""}),
		MyVoca("A",NOUN,{""},{""}),
		MyVoca("xy",NOUN,{""},{""}),
		MyVoca("x",NOUN,{""},{""}),
	}; // testVocas ������ ���� ������ �ʱ�ȭ
	fout << "Testing basic operations of trie inserting ... ... " << endl;
	for (int i = 0; i < NUM_TEST_VOCAS; i++)
	{
		trie_myVoca.insert(testVocas[i].getKeyWord(), &testVocas[i]); // testVocas[i]�� keyword���� trie_myVoca�� ����
	}
	trie_myVoca.fprintTrie(fout); // trie_myVoca ���

	fout << "\n Testing TrieDestroy ... \n";
	trie_myVoca.eraseTrie(); // trie_myVoca���� 
	trie_myVoca.fprintTrie(fout); // trie_myVoca ���

	fout << "Inserting My Vocabularies to myVocaDict ... " << endl;
	word_count = 0;
	pVoca = &myToeicVocaList[0]; // &myToeicVocaList[0]�� pVoca�� ����

	while (pVoca->getKeyWord() != "") // pVoca->getKeyWord()�� null�� �ƴѵ���
	{
		keyStr = pVoca->getKeyWord(); // pVoca�� key�� keyStr������
		trie_myVoca.insert(keyStr, pVoca); // trie_myVoca�� keyStr�� ����
		pVoca++;
	}
	fout << "Total" << trie_myVoca.size() << "words in trie_myVoca .. " << endl;
	trie_myVoca.fprintTrie(fout); // trie_myVoca ���

	while (1) // ���ѹݺ�
	{
		cout << "\n Input any prefix to search in trie (. to finish) : "; // ã�����ϴ� prefix �Է�
		cin >> keyStr; // keyStr�� �ޱ�
		if (keyStr == string(".")) //  keyStr�� .�̸� �ݺ��� ������
			break;
		predictVocas.clear();
		trie_myVoca.findPrefixMatch(keyStr, predictVocas); // trie_myVoca�� keyStr�� prefix���� ã��  predictVocas�� ����
		cout << "list of predictive words with prefix (" << keyStr << ") :" << endl;
		itr = predictVocas.begin(); // predictVocas.begin()�� itr�� ����
		for (int i = 0; i < predictVocas.size(); i++)
		{
			pVoca = *itr; // *itr�� pVoca�� ����
			cout << *pVoca << endl; // *pVoca ���ʴ�� ���
			++itr;
		}
	}
	cout << "\nErasing trie_myVoca .... " << endl;
	fout << "\nErasing trie_myVoca .... " << endl;
	trie_myVoca.eraseTrie();

	fout.close();
}