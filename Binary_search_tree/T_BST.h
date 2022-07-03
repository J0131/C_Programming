#ifndef T_BST_H
#define T_BST_H
#include <iostream>
#include <fstream>
#include "T_BSTN.h"
#include "T_Array.h"
#include "T_Entry.h"

template<typename K, typename V>
class T_BST
{
public:
	T_BST(string nm) : _root(NULL), num_entry(0), name(nm) {} // ������
	string getName() { return name; } // �̸��� �о���� �Լ�
	int size() const { return num_entry; } // ũ�⸦ �о���� �Լ�
	bool empty() const { return (num_entry == 0); } // ����ִ��� Ȯ��
	void clear(); // Ŭ����
	T_BSTN<K, V>* getRoot() { return _root; } // ��Ʈ��� ��ȯ�ϴ� �Լ�
	T_BSTN<K, V>** getRootAddr() { return &_root; } // ��Ʈ����� �ּҸ� ��ȯ�ϴ� �Լ�
	T_Entry<K, V>& getRootaEntry() { return _root->getEntry(); } // ��Ʈ�� ��Ʈ���� ��ȯ�ϴ� �Լ�
	T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp); // ��带 �����ϴ� �Լ�
	void insertInOrder(const T_Entry<K, V> entry); // ������ �°� �����ϴ� �Լ�
	void insertAndRebalance(T_Entry<K, V> e); // ���� �� �����ȭ �ϴ� �Լ�
	void traversal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value); // ������ȸ
	void traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	void traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	T_BSTN<K, V>* searchBSTN(K k); // Ž��
	T_Entry<K, V>& minEntry(); // �ּ�
	T_Entry<K, V>& maxEntry(); // �ִ�
	void fprint_with_Depth(ostream& fout); // ���̿����� ����Լ�
	void fprint_inOrder(ostream& fout);
protected:
	T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot);
	T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot); // ���
protected:
	T_BSTN<K, V>*_insertInOrder(T_BSTN<K, V>** p, T_BSTN<K, V>* parenPos, const T_Entry<K, V> e);
	T_BSTN<K, V>*_insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e); // ���
	T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot); // �����ȭ�ϴ� �Լ�
	int _getHeight(T_BSTN<K, V>* pTN); // ���̸� ��ȯ�ϴ� �Լ�
	int _getHeightDiff(T_BSTN<K, V>* pTN); // �������̸� ��ȯ�ϴ� �Լ�
	T_BSTN<K, V>* _reBalance(T_BSTN<K, V>** ppTN);
	T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k);
	void _fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth);
	void _fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout);
private:
	T_BSTN<K, V>* _root; // ��Ʈ���
	int num_entry; // ����� ����
	string name;
}; // 

template<typename K, typename V>
void T_BST<K, V>::clear()
{
	while (size() > 0) // size�� 0���� ũ��
	{
		eraseBSTN(&_root); // ��Ʈ��� ����
	}
}

template<typename K, typename V>
int T_BST<K, V>::_getHeight(T_BSTN<K, V>* pTN)
{
	int height = 0;
	int height_Lc, height_Rc;
	if (pTN != NULL) 
	{
		height_Lc = _getHeight(pTN->getpLc()); // ���� �ڽĳ���� ���̸� height_Lc�� ����
		height_Rc = _getHeight(pTN->getpRc()); // ������ �ڽĳ���� ���̸� height_Rc�� ����
		if (height_Lc > height_Rc)
			height = 1 + height_Lc; // 
		else
			height = 1 + height_Rc; // �� ū���̿� 1���ϱ�
	}
	return height;
}
template<typename K, typename V> int T_BST<K, V>::_getHeightDiff(T_BSTN<K, V>* pTN)
{
	int heightDiff = 0;
	if (pTN == NULL)
		return 0;
	heightDiff = _getHeight(pTN->getpLc()) - _getHeight(pTN->getpRc()); // �����ڽĳ���� ���̿��� ������ �ڽĳ���� ������ ���̸� heightDiff������
	return heightDiff;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBR, * pCurParent; // ��������
	pCurParent = pCurSubRoot->getpPr(); // �����Ʈ����� �θ��带 pCurParent�� ����
	pNewSubRoot = pCurSubRoot->getpLc(); // �����Ʈ����� ���� �ڽĳ�带 pNewSubRoot�μ���
	pBR = pNewSubRoot->getpRc(); // pNewSubRoot�� ������ �ڽĳ�带 pBR�μ���
	pCurSubRoot->setpLc(pBR); // pCurSubRoot�� ���� �ڽĳ�带 pBR�� ����
	if (pBR != NULL)
		pBR->setpPr(pCurSubRoot); // pBR�� �θ��带 pCurSubRoot�� ����
	pNewSubRoot->setpRc(pCurSubRoot); // ������� �������ڽĳ�� ����
	pNewSubRoot->setpPr(pCurParent); // ������� �θ��� ����
	pCurSubRoot->setpPr(pNewSubRoot); // ���η�Ʈ����� �θ��带 �����μ���
	return pNewSubRoot;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBL, * pCurParent; // ��������
	pCurParent = pCurSubRoot->getpPr(); // ���缭���Ʈ����� �θ��带 pCurParent������
	pNewSubRoot = pCurSubRoot->getpRc(); // pCurSubRoot�� ������ �ڽĳ�带 pNewSubRoot�μ���
	pBL = pNewSubRoot->getpLc(); // pNewSubRoot�� ���� �ڽĳ�带 pBL�μ���
	pCurSubRoot->setpRc(pBL); // pCurSubRoot�� ������ �ڽĳ�带 pBL�μ���
	if (pBL != NULL)
		pBL->setpPr(pCurSubRoot); // pBL�� �θ��带 pCurSubRoot�μ���
	pNewSubRoot->setpLc(pCurSubRoot); // pNewSubRoot�� ���� �ڽĳ�带 pCurSubRoot�μ���
	pNewSubRoot->setpPr(pCurParent); // pNewSubRoot�� �θ��带 pCurParent�μ���
	pCurSubRoot->setpPr(pNewSubRoot);  // ���η�Ʈ����� �θ��带 �����μ���
	return pNewSubRoot;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;
	pC = pCurSubRoot; // ���缭���Ʈ��带 pC�μ���
	pCurParent = pCurSubRoot->getpPr(); // ���� �����Ʈ����� �θ��带 �о� pCurParent������
	pA = pC->getpLc(); // ������ �ڽĳ�� ����
	pB = pA->getpRc(); // ������ �ڽĳ�� ����
	pBL = pB->getpLc(); // ������ �ڽĳ�� ����
	pBR = pB->getpRc(); // ������ �ڽĳ�� ����
	pSubRoot = _rotate_RR(pA); // A�� �������� �����ȭ�Ͽ� A�� ��ġ�� ��带 pSubRoot������
	pCurSubRoot->setpLc(pSubRoot); // pCurSubRoot�� ���� �ڽĳ�带 pSubRoot�� ����
	pNewSubRoot = _rotate_LL(pC); // C�� �������� ������ �����ȭ�� C�� ��ġ�� ��带 ����
	pNewSubRoot->setpPr(pCurParent); // pNewSubRoot�� �θ��带 pCurParent�μ���
	pA->setpPr(pNewSubRoot); // A�� �θ��带 pNewSubRoot�� ����
	pC->setpPr(pNewSubRoot); // A�� C�� �θ��带 ���ο� �����Ʈ�μ���
	if (pBL != NULL)
		pBL->setpPr(pA); // pBL�� �θ��带 pA�μ���
	if (pBR != NULL)
		pBR->setpPr(pC);  // pBR�� �θ��带 pC�μ���
	return pNewSubRoot;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent; // ��������
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR; // ��������
	pA = pCurSubRoot; // ���缭���Ʈ�� A�� ����
	pCurParent = pCurSubRoot->getpPr(); // ���缭���Ʈ�� �θ��带 pCurParent�� ����
	pC = pA->getpRc(); // C�� B�� ���� ������ �ڽĳ�� ����
	pB = pC->getpLc(); // C�� B�� ���� ������ �ڽĳ�� ����
	pBL = pB->getpLc(); // C�� B�� ���� ������ �ڽĳ�� ����
	pBR = pB->getpRc(); // C�� B�� ���� ������ �ڽĳ�� ����
	pSubRoot = _rotate_LL(pC); // C�� �������� ���� ����ȭ�Ͽ� C�� �ڸ��� ��带 pSubRoot������
	pCurSubRoot->setpRc(pSubRoot); // pCurSubRoot�� ������ �ڽĳ�带 pSubRoot�� ����
	pNewSubRoot = _rotate_RR(pA); // A�� �������� ������ ����ȭ�Ͽ� A�� �ڸ���带 pNewSubRoot
	pNewSubRoot->setpPr(pCurParent); // pNewSubRoot�� �θ��带 pCurParent�� ����
	pA->setpPr(pNewSubRoot); // A�� �θ��带 NewSubRoot�� ����
	pC->setpPr(pNewSubRoot); // A�� C�� �θ��带 pNewSubRoot�� ����
	if (pBL != NULL)
		pBL->setpPr(pA); // pBL�� �θ��带 pA�μ���
	if (pBR != NULL)
		pBR->setpPr(pC); // pBR�� �θ��带 pC�μ���
	return pNewSubRoot;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_reBalance(T_BSTN<K, V>** ppTN)
{
	int heightDiff = 0;
	heightDiff = _getHeightDiff(*ppTN);
	if (heightDiff > 1) // ���� ����Ʈ���� �� ���ٸ�
	{
		if (_getHeightDiff((*ppTN)->getpLc()) > 0)
			*ppTN = _rotate_LL(*ppTN);
		else
			*ppTN = _rotate_LR(*ppTN);
	}
	else if (heightDiff < -1) // ������ ����Ʈ���� �����ٸ�
	{
		if (_getHeightDiff((*ppTN)->getpRc()) < 0)
			*ppTN = _rotate_RR(*ppTN);
		else
			*ppTN = _rotate_RL(*ppTN);
	}
	return *ppTN;
}
template<typename K, typename V>
void T_BST<K, V>::insertAndRebalance(T_Entry<K, V> entry)
{
	_insertAndRebalance(&_root, NULL, entry);
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> entry)
{
	T_BSTN<K, V>* pTN, ** ppLc, ** ppRc;
	if (*ppTN == NULL) // attach a new tree node at the currently external node
	{
		pTN = new T_BSTN<K, V>(entry);
		*ppTN = pTN;
		if (pPr != NULL) // ��Ʈ�� �ƴϸ� 
			pTN->setpPr(pPr); // pTN�� �θ��带 pPr�μ���
		(*ppTN)->setpLc(NULL); // (*ppTN)�� ���� �ڽĳ�带 NULL�μ���
		(*ppTN)->setpRc(NULL); // (*ppTN)�� ������ �ڽĳ�带 NULL�μ���
		num_entry++; //  num_entry�� ���� 1������Ű��
		return *ppTN;
	}
	T_Entry<K, V> bstn_entry;
	bstn_entry = (*ppTN)->getEntry(); //  (*ppTN)�� entry�� bstn_entry�� ����
	if (entry < bstn_entry) // entry�� bstn_entry���� ������ 
	{
		ppLc = (*ppTN)->getppLc(); //  (*ppTN)�� �����ڽĳ�带 ppLc�� ����
		pTN = _insertAndRebalance(ppLc, *ppTN, entry); // entry�� ppLc�� ���� 
		if (ppTN != NULL)
		{
			(*ppTN)->setpLc(pTN);
			*ppTN = _reBalance(ppTN);
		}
	}
	else // entry�� bstn_entry���� ũ�ų� ������
	{
		ppRc = (*ppTN)->getppRc(); //   (*ppTN)�� �������ڽĳ�带 ppRc�� ����
		pTN = _insertAndRebalance(ppRc, *ppTN, entry); // entry�� ppRc�� ����
		if (ppTN != NULL)
		{
			(*ppTN)->setpRc(pTN);
			*ppTN = _reBalance(ppTN);
		}
	}
	return *ppTN;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertInOrder(T_BSTN<K, V>** pp,T_BSTN<K, V>* parenPos, const T_Entry<K, V> entry)
{
	T_BSTN<K, V>* newPos, ** pChildPos;
	T_BSTN<K, V>* pos;
	T_Entry<K, V> ent;
	if (pp == NULL)
	{
		cout << "Error in creation of BinarySearchTree :";
		cout << " address of the pointer to the Root Node is NULL !!\n";
		exit;
	}
	pos = *pp;
	if (pos == NULL)
	{
		pos = new T_BSTN<K, V>(entry);
		if (parenPos == NULL)
		{
			_root = pos; // _root�� pos�� ����
		}
		pos->setpPr(parenPos); // pos�� �θ��带 parenPos�� ����
		*pp = pos;
		num_entry++; // num_entry�� 1��ŭ ����
		return pos;
	}
	ent = pos->getEntry(); // pos�� entry�� ent�� ����
	if (entry < ent) // entry�� ent���� ������
	{
		pChildPos = pos->getppLc(); // pos�� ���� �ڽĳ�带 pChildPos������
		newPos = _insertInOrder(pChildPos, pos, entry); // entry�� pChildPos������
		if (newPos != NULL)
			pos->setpLc(newPos);
		return NULL; // only the leaf child is set correctly, while the intermediate node is skipped
	}
	else if (entry >= ent) // entry�� ent���� ���ų� ũ��
	{
		pChildPos = pos->getppRc(); // pos�� ������ �ڽĳ�带 pChildPos������
		newPos = _insertInOrder(pChildPos, pos, entry); // entry�� pChildPos������
		if (newPos != NULL)
			pos->setpRc(newPos);
		return NULL; // only the leaf child is set correctly, while the intermediate node is skipped
	}
}
template<typename K, typename V>
void T_BST<K, V>::insertInOrder(const T_Entry<K, V> entry)
{
	_insertInOrder(&_root, NULL, entry);
}
template<typename K, typename V>
void T_BST<K, V>::traversal_inOrder(T_BSTN<K, V>* pos,T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();
	pRc = pos->getpRc();
	traversal_inOrder(pLc, array_value);
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insert(array_value.size(),value);
	traversal_inOrder(pRc, array_value);
} // ������ȸ
template<typename K, typename V>void T_BST<K, V>::traversal_preOrder(T_BSTN<K, V>* pos,T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();
	pRc = pos->getpRc();
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);
	traversal_preOrder(pLc, array_value);
	traversal_preOrder(pRc, array_value);
}
template<typename K, typename V> void T_BST<K, V>::traversal_postOrder(T_BSTN<K, V>* pos,T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();
	pRc = pos->getpRc();
	traversal_postOrder(pLc, array_value);
	traversal_postOrder(pRc, array_value);
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K,V>::_searchBSTN(T_BSTN<K, V>* pos, K k)
{
	K ent_k;
	T_BSTN<K, V>* pos_result = NULL;
	if (pos == NULL)
		return NULL;
	ent_k = pos->getKey();
	if (ent_k == k)
		pos_result = pos;
	// given entry was found here !!
	else if (ent_k > k)
		pos_result = _searchBSTN(pos->getpLc(), k);
	else if (ent_k < k)
		pos_result = _searchBSTN(pos->getpRc(), k);
	return pos_result;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::searchBSTN(K key)
{
	T_BSTN<K, V>* pEntry;
	pEntry = _searchBSTN(_root, key);
	return pEntry;
} // Ž��
template<typename K, typename V>T_BSTN<K, V>* T_BST<K, V>::_minBSTN(T_BSTN<K, V>* subRoot)
{
	T_BSTN<K, V>* pos, * pLc;
	if ((subRoot == NULL) ||
		(NULL == subRoot->getpLc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpLc()) != NULL)
		pos = pos->getpLc();
	return pos;
} // �ּҰ�
template<typename K, typename V>T_BSTN<K, V>* T_BST<K, V>::_maxBSTN(T_BSTN<K, V>* subRoot)
{
	T_BSTN<K, V>* pos, * pLc;
	if ((subRoot == NULL) ||
		(NULL == subRoot->getpRc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpRc()) != NULL)
		pos = pos->getpRc();
	return pos;
} // �ִ밪
template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::minEntry()
{
	T_BSTN<K, V>* pMin;
	pMin = _minBSTN(_root); // ���
	return pMin->getEntry();
} // �ּҰ� 
template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::maxEntry()
{
	T_BSTN<K, V>* pMax;
	pMax = _maxBSTN(_root); // ���
	return pMax->getEntry();
} // �ִ밪
template<typename K, typename V>
void T_BST<K, V>::_fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout)
{
	T_BSTN<K, V>* pRc, * pLc;
	if ((pLc = pTN->getpLc()) != NULL)
		_fprint_inOrder(pLc, fout);
	fout << pTN->getEntry() << endl;
	if ((pRc = pTN->getpRc()) != NULL)
		_fprint_inOrder(pRc, fout);
} // ������� ��� ���
template<typename K, typename V>
void T_BST<K, V>::fprint_inOrder(ostream& fout)
{
	T_BSTN<K, V>* root = getRoot();
	if (num_entry == 0)
	{
		fout << getName() << " is empty now !!" << endl;
		return;
	}
	_fprint_inOrder(root, fout);
} // ������� ���
template<typename K, typename V>
void T_BST<K, V>::_fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth)
{
	T_BSTN<K, V>* pRc, * pLc;
	T_Entry<K, V>* pEntry;
	if ((pRc = pTN->getpRc()) != NULL)
		_fprint_with_Depth(pRc, fout, depth + 1);
	for (int i = 0; i < depth; i++)
	{
		fout << "    ";
	}
	fout << pTN->getEntry() << endl;
	if ((pLc = pTN->getpLc()) != NULL)
		_fprint_with_Depth(pLc, fout, depth + 1);
} // ���̿� ���� ��� ���
template<typename K, typename V>
void T_BST<K, V>::fprint_with_Depth(ostream& fout)
{
	T_BSTN<K, V>* root = getRoot();
	if (num_entry == 0)
	{
		fout << getName() << " is empty now !!" << endl;
		return;
	}
	fout << name << " : current size ( " << num_entry << " )" << endl;
	_fprint_with_Depth(root, fout, 0);
} // ���̿� ���� ���
template<typename K, typename V>T_BSTN<K, V>* T_BST<K, V>::eraseBSTN(T_BSTN<K, V>** pptoBeErased)
{
	T_BSTN<K, V>* newSubRoot, * temp, * w, * wlc; // ��������
	T_BSTN<K, V>* toBeErased; // ������� ����
	toBeErased = *pptoBeErased; // toBeErased�� *pptoBeErased�� ����
	if (toBeErased == NULL) // toBeErased�� NULL�̸�
		return NULL; // NULL��ȯ
	if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() == NULL))
		// �����ϰ����ϴ� ����� �ڽĳ�尡���ٸ�
	{
		newSubRoot = NULL;
	}
	else if ((toBeErased->getpLc() != NULL) && (toBeErased->getpRc() == NULL))
		// �����ϰ����ϴ� ����� ���� �ڽ� ��常 ������
	{
		newSubRoot = toBeErased->getpLc(); // ��������� �����ڽĳ�带 newSubRoot�μ���
		newSubRoot->setpPr(toBeErased->getpPr()); // newSubRoot�� �ּҸ� ��������� �ּҷμ���
	}
	else if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() != NULL))
		// �����ϰ����ϴ� ����� ������ �ڽ� ��常 ������
	{
		newSubRoot = toBeErased->getpRc(); // ��������� �������ڽĳ�带 newSubRoot�μ���
		newSubRoot->setpPr(toBeErased->getpPr()); // newSubRoot�� �ּҸ� ��������� �ּҷμ���
	}
	else
	{// �����ؾ��ϴ� ��尡 ���� �ڽĳ��� ������ �ڽĳ�带 ��� ������������
		int heightDiff = _getHeightDiff(toBeErased); // ��������� heightdiff�� ���Ͽ� heightdiff������
		T_BSTN<K, V>* parDel = toBeErased->getpPr(); // ��������� �θ��带 ����
		T_BSTN<K, V>* lChild = toBeErased->getpLc(); // ��������� �����ڽĳ��
		T_BSTN<K, V>* rChild = toBeErased->getpRc(); // ��������� �������ڽĳ��;
		T_BSTN<K, V>* ioSs = NULL, * rcIoSs, * parIoSs; // ��������
		T_BSTN<K, V>* ioPd = NULL, * lcIoPd, * parIoPd; // ��������
		if (heightDiff > 0)
			// ���� ����Ʈ���� ���̰� �� �������
		{
			ioPd = _maxBSTN(lChild); // ���� �ڽ��� ���� ū���� ioPd������
			lcIoPd = ioPd->getpLc(); // ioPd�� �����ڽĳ�带 lcIoPd�μ���
			parIoPd = ioPd->getpPr(); // ioPd�� �θ��带 parIoPd�μ���
			newSubRoot = ioPd; // ioPd�� newSubRoot�� ����
			if (ioPd->getpPr() != toBeErased) //ioPd�� �θ� ������尡�ƴ϶��
			{
				newSubRoot->setpLc(lChild); // newSubRoot�� �����ڽĳ�带 IChild������
				parIoPd->setpRc(lcIoPd);  // parIoPd�� �������ڽĳ�带 IcIoPd�� ����
				if (lcIoPd != NULL)
					lcIoPd->setpPr(parIoPd); // lcIoPd�� �θ��带 parIoPd�μ���
			}
			newSubRoot->setpRc(rChild); // newnewSubRoot�� �������ڽ��� rChild�ιٲٱ�
			newSubRoot->setpPr(toBeErased->getpPr()); // newnewSubRoot�θ� toBeErased�Ǻθ�ιٲٱ�
		}
		else
			// ������ ����Ʈ���� ���̰� �� �������
		{
			ioSs = _minBSTN(rChild); // ��������� ������ �ڽ�Ʈ������ ���� �������� ioSs����
			rcIoSs = ioSs->getpRc(); // ioSs�� ������ �ڽĳ�带 rcloSs������
			parIoSs = ioSs->getpPr(); // ioSs�� �θ��带 parloSs������
			newSubRoot = ioSs; // ioSs�� newSubRoot������
			if (ioSs->getpPr() != toBeErased)
			{
				newSubRoot->setpRc(rChild); // newSubRoot�� ������ �ڽ��� rChild������
				parIoSs->setpLc(rcIoSs); // parIoSs�� ���� �ڽĳ�带 rcIoSs�� ����
				if (rcIoSs != NULL)
					rcIoSs->setpPr(parIoSs); // rcIoSs�� �θ��带 parIoSs�� ����
			}
			newSubRoot->setpLc(lChild); // newSubRoot�� ���� �ڽ��� lChild������
			newSubRoot->setpPr(toBeErased->getpPr()); // newSubRoot�� �θ��带 tobeErased�� �θ���� ����
		}
		if (lChild != ioPd)
			lChild->setpPr(newSubRoot); // IChild�� �θ��带 newSubRoot�μ���
		if (rChild != ioSs)
			rChild->setpPr(newSubRoot); // rChild�� �θ��带 newSubRoot�� ����
	}
	if (toBeErased == _root) // �����ϰ����ϴ� ��尡 ��Ʈ�����
		_root = newSubRoot; // newSubRoot�� ��Ʈ���θ����
	num_entry--; // num_entry�� 1��ŭ ���ҽ�Ų��
	free(toBeErased);// toBeErased �����Ҵ�����
	*pptoBeErased = newSubRoot; // *pptoBeErased�� newSubRoot�� ����
	return newSubRoot; // newSubRoot�� ��ȯ�Ѵ�
}
#endif