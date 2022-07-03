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
	T_BST(string nm) : _root(NULL), num_entry(0), name(nm) {} // 생성자
	string getName() { return name; } // 이름을 읽어오는 함수
	int size() const { return num_entry; } // 크기를 읽어오는 함수
	bool empty() const { return (num_entry == 0); } // 비어있는지 확인
	void clear(); // 클리어
	T_BSTN<K, V>* getRoot() { return _root; } // 루트노드 반환하는 함수
	T_BSTN<K, V>** getRootAddr() { return &_root; } // 루트노드의 주소를 반환하는 함수
	T_Entry<K, V>& getRootaEntry() { return _root->getEntry(); } // 루트의 엔트리를 반환하는 함수
	T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp); // 노드를 삭제하는 함수
	void insertInOrder(const T_Entry<K, V> entry); // 순서에 맞게 삽입하는 함수
	void insertAndRebalance(T_Entry<K, V> e); // 삽입 및 재균형화 하는 함수
	void traversal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value); // 순차순회
	void traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	void traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	T_BSTN<K, V>* searchBSTN(K k); // 탐색
	T_Entry<K, V>& minEntry(); // 최소
	T_Entry<K, V>& maxEntry(); // 최대
	void fprint_with_Depth(ostream& fout); // 높이에따른 출력함수
	void fprint_inOrder(ostream& fout);
protected:
	T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot);
	T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot); // 재귀
protected:
	T_BSTN<K, V>*_insertInOrder(T_BSTN<K, V>** p, T_BSTN<K, V>* parenPos, const T_Entry<K, V> e);
	T_BSTN<K, V>*_insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e); // 재귀
	T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot); // 재균형화하는 함수
	int _getHeight(T_BSTN<K, V>* pTN); // 높이를 반환하는 함수
	int _getHeightDiff(T_BSTN<K, V>* pTN); // 높이차이를 반환하는 함수
	T_BSTN<K, V>* _reBalance(T_BSTN<K, V>** ppTN);
	T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k);
	void _fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth);
	void _fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout);
private:
	T_BSTN<K, V>* _root; // 루트노드
	int num_entry; // 노드의 갯수
	string name;
}; // 

template<typename K, typename V>
void T_BST<K, V>::clear()
{
	while (size() > 0) // size가 0보다 크면
	{
		eraseBSTN(&_root); // 루트노드 삭제
	}
}

template<typename K, typename V>
int T_BST<K, V>::_getHeight(T_BSTN<K, V>* pTN)
{
	int height = 0;
	int height_Lc, height_Rc;
	if (pTN != NULL) 
	{
		height_Lc = _getHeight(pTN->getpLc()); // 왼쪽 자식노드의 높이를 height_Lc에 저장
		height_Rc = _getHeight(pTN->getpRc()); // 오른쪽 자식노드의 높이를 height_Rc에 저장
		if (height_Lc > height_Rc)
			height = 1 + height_Lc; // 
		else
			height = 1 + height_Rc; // 더 큰높이에 1더하기
	}
	return height;
}
template<typename K, typename V> int T_BST<K, V>::_getHeightDiff(T_BSTN<K, V>* pTN)
{
	int heightDiff = 0;
	if (pTN == NULL)
		return 0;
	heightDiff = _getHeight(pTN->getpLc()) - _getHeight(pTN->getpRc()); // 왼쪽자식노드의 높이에서 오른쪽 자식노드의 높이의 차이를 heightDiff에저장
	return heightDiff;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBR, * pCurParent; // 변수선언
	pCurParent = pCurSubRoot->getpPr(); // 서브루트노드의 부모노드를 pCurParent로 설정
	pNewSubRoot = pCurSubRoot->getpLc(); // 서브루트노드의 왼쪽 자식노드를 pNewSubRoot로설정
	pBR = pNewSubRoot->getpRc(); // pNewSubRoot의 오른쪽 자식노드를 pBR로설정
	pCurSubRoot->setpLc(pBR); // pCurSubRoot의 왼쪽 자식노드를 pBR로 설정
	if (pBR != NULL)
		pBR->setpPr(pCurSubRoot); // pBR의 부모노드를 pCurSubRoot로 설정
	pNewSubRoot->setpRc(pCurSubRoot); // 새노드의 오른쪽자식노드 설정
	pNewSubRoot->setpPr(pCurParent); // 새노드의 부모노드 설정
	pCurSubRoot->setpPr(pNewSubRoot); // 서부루트노드의 부모노드를 새노드로설정
	return pNewSubRoot;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBL, * pCurParent; // 변수선언
	pCurParent = pCurSubRoot->getpPr(); // 현재서브루트노드의 부모노드를 pCurParent에저장
	pNewSubRoot = pCurSubRoot->getpRc(); // pCurSubRoot의 오른쪽 자식노드를 pNewSubRoot로설정
	pBL = pNewSubRoot->getpLc(); // pNewSubRoot의 왼쪽 자식노드를 pBL로설정
	pCurSubRoot->setpRc(pBL); // pCurSubRoot의 오른쪽 자식노드를 pBL로설정
	if (pBL != NULL)
		pBL->setpPr(pCurSubRoot); // pBL의 부모노드를 pCurSubRoot로설정
	pNewSubRoot->setpLc(pCurSubRoot); // pNewSubRoot의 왼쪽 자식노드를 pCurSubRoot로설정
	pNewSubRoot->setpPr(pCurParent); // pNewSubRoot의 부모노드를 pCurParent로설정
	pCurSubRoot->setpPr(pNewSubRoot);  // 서부루트노드의 부모노드를 새노드로설정
	return pNewSubRoot;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;
	pC = pCurSubRoot; // 현재서브루트노드를 pC로설정
	pCurParent = pCurSubRoot->getpPr(); // 현재 서브루트노드의 부모노드를 읽어 pCurParent에저장
	pA = pC->getpLc(); // 각각의 자식노드 설정
	pB = pA->getpRc(); // 각각의 자식노드 설정
	pBL = pB->getpLc(); // 각각의 자식노드 설정
	pBR = pB->getpRc(); // 각각의 자식노드 설정
	pSubRoot = _rotate_RR(pA); // A를 기준으로 재균형화하여 A의 위치의 노드를 pSubRoot에저장
	pCurSubRoot->setpLc(pSubRoot); // pCurSubRoot의 왼쪽 자식노드를 pSubRoot로 설정
	pNewSubRoot = _rotate_LL(pC); // C를 기준으로 왼쪽을 재균형화여 C의 위치의 노드를 저장
	pNewSubRoot->setpPr(pCurParent); // pNewSubRoot의 부모노드를 pCurParent로설정
	pA->setpPr(pNewSubRoot); // A의 부모노드를 pNewSubRoot로 설정
	pC->setpPr(pNewSubRoot); // A와 C의 부모노드를 새로운 서브루트로설정
	if (pBL != NULL)
		pBL->setpPr(pA); // pBL의 부모노드를 pA로설정
	if (pBR != NULL)
		pBR->setpPr(pC);  // pBR의 부모노드를 pC로설정
	return pNewSubRoot;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent; // 변수선언
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR; // 변수선언
	pA = pCurSubRoot; // 현재서브루트를 A로 설정
	pCurParent = pCurSubRoot->getpPr(); // 현재서브루트의 부모노드를 pCurParent에 저장
	pC = pA->getpRc(); // C와 B의 왼쪽 오른쪽 자식노드 설정
	pB = pC->getpLc(); // C와 B의 왼쪽 오른쪽 자식노드 설정
	pBL = pB->getpLc(); // C와 B의 왼쪽 오른쪽 자식노드 설정
	pBR = pB->getpRc(); // C와 B의 왼쪽 오른쪽 자식노드 설정
	pSubRoot = _rotate_LL(pC); // C를 기준으로 왼쪽 균형화하여 C의 자리의 노드를 pSubRoot에저장
	pCurSubRoot->setpRc(pSubRoot); // pCurSubRoot의 오른쪽 자식노드를 pSubRoot로 설정
	pNewSubRoot = _rotate_RR(pA); // A를 기준으로 오른쪽 균형화하여 A의 자리노드를 pNewSubRoot
	pNewSubRoot->setpPr(pCurParent); // pNewSubRoot의 부모노드를 pCurParent로 저장
	pA->setpPr(pNewSubRoot); // A의 부모노드를 NewSubRoot로 설정
	pC->setpPr(pNewSubRoot); // A와 C의 부모노드를 pNewSubRoot로 설정
	if (pBL != NULL)
		pBL->setpPr(pA); // pBL의 부모노드를 pA로설정
	if (pBR != NULL)
		pBR->setpPr(pC); // pBR의 부모노드를 pC로설정
	return pNewSubRoot;
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_reBalance(T_BSTN<K, V>** ppTN)
{
	int heightDiff = 0;
	heightDiff = _getHeightDiff(*ppTN);
	if (heightDiff > 1) // 왼쪽 서브트리가 더 높다면
	{
		if (_getHeightDiff((*ppTN)->getpLc()) > 0)
			*ppTN = _rotate_LL(*ppTN);
		else
			*ppTN = _rotate_LR(*ppTN);
	}
	else if (heightDiff < -1) // 오른쪽 서브트리가 더높다면
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
		if (pPr != NULL) // 루트가 아니면 
			pTN->setpPr(pPr); // pTN의 부모노드를 pPr로설정
		(*ppTN)->setpLc(NULL); // (*ppTN)의 왼쪽 자식노드를 NULL로설정
		(*ppTN)->setpRc(NULL); // (*ppTN)의 오른쪽 자식노드를 NULL로설정
		num_entry++; //  num_entry의 값을 1증가시키기
		return *ppTN;
	}
	T_Entry<K, V> bstn_entry;
	bstn_entry = (*ppTN)->getEntry(); //  (*ppTN)의 entry를 bstn_entry에 저장
	if (entry < bstn_entry) // entry가 bstn_entry보다 작으면 
	{
		ppLc = (*ppTN)->getppLc(); //  (*ppTN)의 왼쪽자식노드를 ppLc에 저장
		pTN = _insertAndRebalance(ppLc, *ppTN, entry); // entry를 ppLc에 삽입 
		if (ppTN != NULL)
		{
			(*ppTN)->setpLc(pTN);
			*ppTN = _reBalance(ppTN);
		}
	}
	else // entry가 bstn_entry보다 크거나 같으면
	{
		ppRc = (*ppTN)->getppRc(); //   (*ppTN)의 오른쪽자식노드를 ppRc에 저장
		pTN = _insertAndRebalance(ppRc, *ppTN, entry); // entry를 ppRc에 삽입
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
			_root = pos; // _root를 pos로 설정
		}
		pos->setpPr(parenPos); // pos의 부모노드를 parenPos로 설정
		*pp = pos;
		num_entry++; // num_entry를 1만큼 증가
		return pos;
	}
	ent = pos->getEntry(); // pos의 entry를 ent로 설정
	if (entry < ent) // entry가 ent보다 작으면
	{
		pChildPos = pos->getppLc(); // pos의 왼쪽 자식노드를 pChildPos에저장
		newPos = _insertInOrder(pChildPos, pos, entry); // entry를 pChildPos에삽입
		if (newPos != NULL)
			pos->setpLc(newPos);
		return NULL; // only the leaf child is set correctly, while the intermediate node is skipped
	}
	else if (entry >= ent) // entry가 ent보다 같거나 크면
	{
		pChildPos = pos->getppRc(); // pos의 오른쪽 자식노드를 pChildPos에저장
		newPos = _insertInOrder(pChildPos, pos, entry); // entry를 pChildPos에삽입
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
} // 순차순회
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
} // 탐색
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
} // 최소값
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
} // 최대값
template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::minEntry()
{
	T_BSTN<K, V>* pMin;
	pMin = _minBSTN(_root); // 재귀
	return pMin->getEntry();
} // 최소값 
template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::maxEntry()
{
	T_BSTN<K, V>* pMax;
	pMax = _maxBSTN(_root); // 재귀
	return pMax->getEntry();
} // 최대값
template<typename K, typename V>
void T_BST<K, V>::_fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout)
{
	T_BSTN<K, V>* pRc, * pLc;
	if ((pLc = pTN->getpLc()) != NULL)
		_fprint_inOrder(pLc, fout);
	fout << pTN->getEntry() << endl;
	if ((pRc = pTN->getpRc()) != NULL)
		_fprint_inOrder(pRc, fout);
} // 순서대로 출력 재귀
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
} // 순서대로 출력
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
} // 높이에 따른 출력 재귀
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
} // 높이에 따른 출력
template<typename K, typename V>T_BSTN<K, V>* T_BST<K, V>::eraseBSTN(T_BSTN<K, V>** pptoBeErased)
{
	T_BSTN<K, V>* newSubRoot, * temp, * w, * wlc; // 변수선언
	T_BSTN<K, V>* toBeErased; // 삭제노드 선언
	toBeErased = *pptoBeErased; // toBeErased에 *pptoBeErased를 저장
	if (toBeErased == NULL) // toBeErased가 NULL이면
		return NULL; // NULL반환
	if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() == NULL))
		// 삭제하고자하는 노드의 자식노드가없다면
	{
		newSubRoot = NULL;
	}
	else if ((toBeErased->getpLc() != NULL) && (toBeErased->getpRc() == NULL))
		// 삭제하고자하는 노드의 왼쪽 자식 노드만 있을때
	{
		newSubRoot = toBeErased->getpLc(); // 삭제노드의 왼쪽자식노드를 newSubRoot로설정
		newSubRoot->setpPr(toBeErased->getpPr()); // newSubRoot의 주소를 삭제노드의 주소로설정
	}
	else if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() != NULL))
		// 삭제하고자하는 노드의 오른쪽 자식 노드만 있을때
	{
		newSubRoot = toBeErased->getpRc(); // 삭제노드의 오른쪽자식노드를 newSubRoot로설정
		newSubRoot->setpPr(toBeErased->getpPr()); // newSubRoot의 주소를 삭제노드의 주소로설정
	}
	else
	{// 삭제해야하는 노드가 왼쪽 자식노드와 오른쪽 자식노드를 모두 가지고있을때
		int heightDiff = _getHeightDiff(toBeErased); // 삭제노드의 heightdiff를 구하여 heightdiff에저장
		T_BSTN<K, V>* parDel = toBeErased->getpPr(); // 삭제노드의 부모노드를 저장
		T_BSTN<K, V>* lChild = toBeErased->getpLc(); // 삭제노드의 왼쪽자식노드
		T_BSTN<K, V>* rChild = toBeErased->getpRc(); // 삭제노드의 오른쪽자식노드;
		T_BSTN<K, V>* ioSs = NULL, * rcIoSs, * parIoSs; // 변수선언
		T_BSTN<K, V>* ioPd = NULL, * lcIoPd, * parIoPd; // 변수선언
		if (heightDiff > 0)
			// 왼쪽 서브트리의 높이가 더 높은경우
		{
			ioPd = _maxBSTN(lChild); // 왼쪽 자식중 가장 큰값을 ioPd에저장
			lcIoPd = ioPd->getpLc(); // ioPd의 왼쪽자식노드를 lcIoPd로설정
			parIoPd = ioPd->getpPr(); // ioPd의 부모노드를 parIoPd로설정
			newSubRoot = ioPd; // ioPd를 newSubRoot로 저장
			if (ioPd->getpPr() != toBeErased) //ioPd의 부모가 삭제노드가아니라면
			{
				newSubRoot->setpLc(lChild); // newSubRoot의 왼쪽자식노드를 IChild로저장
				parIoPd->setpRc(lcIoPd);  // parIoPd의 오른쪽자식노드를 IcIoPd로 설정
				if (lcIoPd != NULL)
					lcIoPd->setpPr(parIoPd); // lcIoPd의 부모노드를 parIoPd로설정
			}
			newSubRoot->setpRc(rChild); // newnewSubRoot의 오른쪽자식을 rChild로바꾸기
			newSubRoot->setpPr(toBeErased->getpPr()); // newnewSubRoot부모를 toBeErased의부모로바꾸기
		}
		else
			// 오른쪽 서브트리의 높이가 더 높은경우
		{
			ioSs = _minBSTN(rChild); // 삭제노드의 오른쪽 자식트리에서 가장 작은값을 ioSs에저
			rcIoSs = ioSs->getpRc(); // ioSs의 오른쪽 자식노드를 rcloSs로저장
			parIoSs = ioSs->getpPr(); // ioSs의 부모노드를 parloSs로저장
			newSubRoot = ioSs; // ioSs를 newSubRoot로저장
			if (ioSs->getpPr() != toBeErased)
			{
				newSubRoot->setpRc(rChild); // newSubRoot의 오른쪽 자식을 rChild로저장
				parIoSs->setpLc(rcIoSs); // parIoSs의 왼쪽 자식노드를 rcIoSs로 설정
				if (rcIoSs != NULL)
					rcIoSs->setpPr(parIoSs); // rcIoSs의 부모노드를 parIoSs로 설정
			}
			newSubRoot->setpLc(lChild); // newSubRoot의 왼쪽 자식을 lChild로저장
			newSubRoot->setpPr(toBeErased->getpPr()); // newSubRoot의 부모노드를 tobeErased의 부모노드로 설정
		}
		if (lChild != ioPd)
			lChild->setpPr(newSubRoot); // IChild의 부모노드를 newSubRoot로설정
		if (rChild != ioSs)
			rChild->setpPr(newSubRoot); // rChild의 부모노드를 newSubRoot로 설정
	}
	if (toBeErased == _root) // 삭제하고자하는 노드가 루트노드라면
		_root = newSubRoot; // newSubRoot를 루트노드로만든다
	num_entry--; // num_entry를 1만큼 감소시킨다
	free(toBeErased);// toBeErased 동적할당해제
	*pptoBeErased = newSubRoot; // *pptoBeErased에 newSubRoot를 저장
	return newSubRoot; // newSubRoot를 반환한다
}
#endif