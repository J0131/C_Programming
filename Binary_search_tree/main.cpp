/**************************************
* ���ϸ��� : ���ø������ ����Ž��Ʈ�� ����
* �ۼ��� : �ֹ���
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
	}; // Book���� �迭 books �ʱ�ȭ
	ofstream fout("output.txt"); // ���Ͻ�Ʈ�� ����
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
	T_BSTN<string, Book*>* pRoot, ** ppBBST_BK_root; // ���� �ʱ�ȭ
	ppBBST_BK_root = BBST_BK_keyTitle.getRootAddr(); // BBST_BK_keyTitle�� ��Ʈ������ּҸ� ppBBST_BK_root������ 
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		entry_title_pBK.setKey(books[i].getTitle()); // entry_title_pBK key����
		entry_title_pBK.setValue(&books[i]); // entry_title_pBK value����
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into "<< BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyTitle.insertAndRebalance(entry_title_pBK); // BBST_BK_keyTitle�� entry_title_pBK ���� �� �����ȭ
	}
	fout << "\nEntries in " << BBST_BK_keyTitle.getName() << " (in order of Book Title) : "<< endl;
	
	BBST_BK_keyTitle.fprint_with_Depth(fout); // BBST_BK_keyTitle ���
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-author" << endl;
	T_Entry<string, Book*> entry_Author_pBK;
	T_BST<string, Book*> BBST_BK_keyAuthor("BBST_BK_keyAuthor");
	T_BSTN<string, Book*>** ppRoot_BBST_BK_keyAuthor, * pBBST_BK_keyAuthor;// �����ʱ�ȭ
	ppRoot_BBST_BK_keyAuthor = BBST_BK_keyTitle.getRootAddr(); // BBST_BK_keyTitle �� ��Ʈ������ּҸ� ppRoot_BBST_BK_keyAuthor������ 
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		entry_Author_pBK.setKey(books[i].getAuthor()); // entry_Author_pBK�� key����
		entry_Author_pBK.setValue(&books[i]); // entry_Author_pBK�� value����
		BBST_BK_keyAuthor.insertAndRebalance(entry_Author_pBK); // BBST_BK_keyAuthor �� entry_Author_pBK ���� �� �����ȭ
	}
	fout << "\nEntries in " << BBST_BK_keyAuthor.getName() << " (in order of Book Author) : "	<< endl;

	BBST_BK_keyAuthor.fprint_with_Depth(fout); // BBST_BK_keyAuthor���
	string author = books[0].getAuthor();
	Date d1, d2;
	Book* pBk;
	T_Array<Book*> array_pBook(1, string("Array_Book")); // ���� �ʱ�ȭ
	d1.setDate(2010, 1, 1);
	d2.setDate(2015, 12, 31);
	pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(author); // Ž��
	BBST_BK_keyAuthor.traversal_inOrder(pBBST_BK_keyAuthor, array_pBook);
	fout << "Books of author (" << author << ") published during " << d1 << " ~ " << d2 << ":"<< endl;
	for (int i = 0; i < array_pBook.size(); i++)
	{
		if (array_pBook[i]->getAuthor() == author) // array_pBook[i]->getAuthor() �� author�� ��ġ�Ѵٸ�
		{
			pBk = array_pBook[i]; // array_pBook[i]�� pBk�� ����
			if ((pBk->getPubDate() >= d1) && (pBk->getPubDate() <= d2))
				fout << *(array_pBook[i]) << endl; // pBk->getPubDate()�� d1�� d2���̿��ֵ���  *(array_pBook[i]�� ���
		}
	}
	fout << endl << "Balanced Binary Search Tree (BBST) with key publication-date" << endl;
	T_Entry<Date, Book*> entry_PubDate_pBK;
	T_BST<Date, Book*> BBST_BK_keyPubDate("BBST_BK_keyPubDate");
	T_BSTN<Date, Book*>** ppRoot_BBST_BK_keyPubDate; // ���� �ʱ�ȭ
	ppRoot_BBST_BK_keyPubDate = BBST_BK_keyPubDate.getRootAddr(); //BBST_BK_keyPubDate �� ��Ʈ������ּҸ� ppRoot_BBST_BK_keyAuthor������ 
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		entry_PubDate_pBK.setKey(books[i].getPubDate()); // key����
		entry_PubDate_pBK.setValue(&books[i]); // value ����
		
		BBST_BK_keyPubDate.insertAndRebalance(entry_PubDate_pBK); // ���� �� �����ȭ
	}
	fout << "\nEntries in " << BBST_BK_keyPubDate.getName() << " (in order of Book Publication	Date) : " << endl;
		
	BBST_BK_keyPubDate.fprint_with_Depth(fout); // ���
	fout << "\nRemoving the root entry in sequence ..." << endl;
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		pRoot = BBST_BK_keyTitle.getRoot(); // BBST_BK_keyTitle�� ��Ʈ������ּҸ� pRoot������
		entry_title_pBK = pRoot->getEntry(); //  pRoot�� entry�� entry_title_pBK�� ����
		fout << "\nremove " << entry_title_pBK << endl; // entry_title_pBK�� ���
		BBST_BK_keyTitle.eraseBSTN(&pRoot); // &pRoot�� BBST_BK_keyTitle���� ����
		BBST_BK_keyTitle.fprint_with_Depth(fout); // BBST_BK_keyTitle���
	}
	fout << "\nClearing BBST_BKs . . . " << endl;
	BBST_BK_keyTitle.clear();
	BBST_BK_keyAuthor.clear();
	BBST_BK_keyPubDate.clear();
	fout << "All BBST_BKs cleared !! " << endl;
	fout.close();
}