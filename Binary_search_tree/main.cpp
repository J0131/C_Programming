/**************************************
* 파일목적 : 템플릿기반의 이진탐색트리 구현
* 작성자 : 최범준
* final update : 2020.11.13
***************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "T_BST.h"
#include "T_Entry.h"
#include "T_Array.h"
#include "Book.h"
#include "Date.h"
#include "T_BSTN.h"

using namespace std;
#define NUM_BOOKS 15

void main()
{
	Book books[NUM_BOOKS] = 
	{
		Book(string("Book_01"), string("Kim"), Date(2020, 1, 1)),
		Book(string("Book_02"), string("Kim"), Date(2010, 1, 1)),
		Book(string("Book_03"), string("Kim"), Date(2013, 1, 1)),
		Book(string("Book_04"), string("Lee"), Date(2011, 1, 1)),
		Book(string("Book_05"), string("Hwang"), Date(2001, 1, 1)),
		Book(string("Book_06"), string("Choi"), Date(2003, 1, 1)),
		Book(string("Book_07"), string("Park"), Date(2009, 1, 1)),
		Book(string("Book_08"), string("Brown"), Date(2012, 1, 1)),
		Book(string("Book_09"), string("Alpha"), Date(1980, 1, 1)),
		Book(string("Book_10"), string("Chalie"), Date(1970, 1, 1)),
		Book(string("Book_11"), string("Tango"), Date(1985, 1, 1)),
		Book(string("Book_12"), string("Yankee"), Date(1977, 1, 1)),
		Book(string("Book_13"), string("Zulu"), Date(2018, 1, 1)),
		Book(string("Book_14"), string("Foxtrot"), Date(2015, 1, 1)),
		Book(string("Book_15"), string("Delta"), Date(2000, 1, 1)),
	}; // Book형의 배열 books 초기화
	ofstream fout("output.txt"); // 파일스트림 설정
	if (fout.fail())
	{
		cout << "Fail to create output.txt for results !!" << endl;
		exit;
	}
	fout << "Input books[] array : " << endl;
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		fout << books[i] << endl;
	}
	fout << endl;
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-title" << endl;
	T_Entry<string, Book*> entry_title_pBK;
	T_BST<string, Book*> BBST_BK_keyTitle("BBST_BK_keyTitle");
	T_BSTN<string, Book*>* pRoot, ** ppBBST_BK_root; // 변수 초기화
	ppBBST_BK_root = BBST_BK_keyTitle.getRootAddr(); // BBST_BK_keyTitle의 루트노드의주소를 ppBBST_BK_root에저장 
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		entry_title_pBK.setKey(books[i].getTitle()); // entry_title_pBK key설정
		entry_title_pBK.setValue(&books[i]); // entry_title_pBK value설정
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into "<< BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyTitle.insertAndRebalance(entry_title_pBK); // BBST_BK_keyTitle에 entry_title_pBK 삽입 및 재균형화
	}
	fout << "\nEntries in " << BBST_BK_keyTitle.getName() << " (in order of Book Title) : "<< endl;
	
	BBST_BK_keyTitle.fprint_with_Depth(fout); // BBST_BK_keyTitle 출력
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-author" << endl;
	T_Entry<string, Book*> entry_Author_pBK;
	T_BST<string, Book*> BBST_BK_keyAuthor("BBST_BK_keyAuthor");
	T_BSTN<string, Book*>** ppRoot_BBST_BK_keyAuthor, * pBBST_BK_keyAuthor;// 변수초기화
	ppRoot_BBST_BK_keyAuthor = BBST_BK_keyTitle.getRootAddr(); // BBST_BK_keyTitle 의 루트노드의주소를 ppRoot_BBST_BK_keyAuthor에저장 
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		entry_Author_pBK.setKey(books[i].getAuthor()); // entry_Author_pBK의 key설정
		entry_Author_pBK.setValue(&books[i]); // entry_Author_pBK의 value설정
		BBST_BK_keyAuthor.insertAndRebalance(entry_Author_pBK); // BBST_BK_keyAuthor 에 entry_Author_pBK 삽입 및 재균형화
	}
	fout << "\nEntries in " << BBST_BK_keyAuthor.getName() << " (in order of Book Author) : "	<< endl;

	BBST_BK_keyAuthor.fprint_with_Depth(fout); // BBST_BK_keyAuthor출력
	string author = books[0].getAuthor();
	Date d1, d2;
	Book* pBk;
	T_Array<Book*> array_pBook(1, string("Array_Book")); // 변수 초기화
	d1.setDate(2010, 1, 1);
	d2.setDate(2015, 12, 31);
	pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(author); // 탐색
	BBST_BK_keyAuthor.traversal_inOrder(pBBST_BK_keyAuthor, array_pBook);
	fout << "Books of author (" << author << ") published during " << d1 << " ~ " << d2 << ":"<< endl;
	for (int i = 0; i < array_pBook.size(); i++)
	{
		if (array_pBook[i]->getAuthor() == author) // array_pBook[i]->getAuthor() 와 author가 일치한다면
		{
			pBk = array_pBook[i]; // array_pBook[i]을 pBk에 저장
			if ((pBk->getPubDate() >= d1) && (pBk->getPubDate() <= d2))
				fout << *(array_pBook[i]) << endl; // pBk->getPubDate()이 d1과 d2사이에있따면  *(array_pBook[i]를 출력
		}
	}
	fout << endl << "Balanced Binary Search Tree (BBST) with key publication-date" << endl;
	T_Entry<Date, Book*> entry_PubDate_pBK;
	T_BST<Date, Book*> BBST_BK_keyPubDate("BBST_BK_keyPubDate");
	T_BSTN<Date, Book*>** ppRoot_BBST_BK_keyPubDate; // 변수 초기화
	ppRoot_BBST_BK_keyPubDate = BBST_BK_keyPubDate.getRootAddr(); //BBST_BK_keyPubDate 의 루트노드의주소를 ppRoot_BBST_BK_keyAuthor에저장 
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		entry_PubDate_pBK.setKey(books[i].getPubDate()); // key설정
		entry_PubDate_pBK.setValue(&books[i]); // value 설정
		
		BBST_BK_keyPubDate.insertAndRebalance(entry_PubDate_pBK); // 삽입 및 재균형화
	}
	fout << "\nEntries in " << BBST_BK_keyPubDate.getName() << " (in order of Book Publication	Date) : " << endl;
		
	BBST_BK_keyPubDate.fprint_with_Depth(fout); // 출력
	fout << "\nRemoving the root entry in sequence ..." << endl;
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		pRoot = BBST_BK_keyTitle.getRoot(); // BBST_BK_keyTitle의 루트노드의주소를 pRoot에저장
		entry_title_pBK = pRoot->getEntry(); //  pRoot의 entry를 entry_title_pBK에 저장
		fout << "\nremove " << entry_title_pBK << endl; // entry_title_pBK를 출력
		BBST_BK_keyTitle.eraseBSTN(&pRoot); // &pRoot를 BBST_BK_keyTitle에서 제거
		BBST_BK_keyTitle.fprint_with_Depth(fout); // BBST_BK_keyTitle출력
	}
	fout << "\nClearing BBST_BKs . . . " << endl;
	BBST_BK_keyTitle.clear();
	BBST_BK_keyAuthor.clear();
	BBST_BK_keyPubDate.clear();
	fout << "All BBST_BKs cleared !! " << endl;
	fout.close();
}