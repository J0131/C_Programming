#ifndef Trie_H
#define Trie_H
#include <iostream>
#include <string>
#include "TrieNode.h"
#include "MyVoca.h"
#define MAX_STR_LEN 50
//#define DEBUG
using namespace std;
typedef list<MyVoca*> List_pVoca;
typedef list<MyVoca*> ::iterator List_pVoca_Iter;
enum SearchMode { FULL_MATCH, PREFIX_MATCH };
template <typename E>
class Trie
{
public:
	Trie(string name); // 생성자
	int size() { return num_keys; } // 크기반환 함수
	string getName() { return trie_name; } // 이름 반환함수
	void insert(string keyStr, E value); // 삽입
	void insertExternalTN(TrieNode<E>* pTN, string keyStr, E value); // 외부노드삽입
	TrieNode<E>* find(string keyWord); // 위치찾는함수
	void findPrefixMatch(string prefix, List_pVoca& predictWords); // 
	void deletekeyWord(string keyWord); // KEYWORD삭제 함수
	void eraseTrie(); // Trie전체 삭제
	void fprintTrie(ostream& fout); // trie 출력함수
protected:
	TrieNode<E>* _find(string keyStr, SearchMode sm = FULL_MATCH);
	void _traverse(TrieNode<E>* pTN, List_pVoca& list_keywords);
private:
	TrieNode<E>* _root; // root노드
	int num_keys; // key의 갯수
	string trie_name; // 이름
};
template<typename E>
Trie<E>::Trie(string name)
{
	trie_name = name;
	_root = new TrieNode<E>('\0', NULL);
	_root->setKey('\0');
	_root->setPrev(NULL);
	_root->setNext(NULL);
	_root->setParent(NULL);
	_root->setChild(NULL);
	num_keys = 0;
} // 생성자
template<typename E>
void Trie<E>::insertExternalTN(TrieNode<E>* pTN, string keyStr, E value)
{
	TrieNode<E>* pTN_New = NULL;
	pTN_New = new TrieNode<E>('\0', value);
	pTN->setChild(pTN_New);
	(pTN->getChild())->setParent(pTN);
	pTN_New->setValue(value);
	//cout << "key (" << keyWord << ") is inserted \n";
} // 외부노드 삽입
template<typename E>
void Trie<E>::insert(string keyWord, E value)
{
	TrieNode<E>* pTN = NULL, * pTN_New = NULL;
	char* keyPtr = (char*)keyWord.c_str();
	if (keyWord.length() == 0)
		return;
	/* Firstly, check any possible duplicated key insertion */
	if (_find(keyWord, FULL_MATCH) != NULL)
	{
		cout << "The given key is already existing; just return !!" << endl;
		return;
	}
	pTN = this->_root;
	while ((pTN != NULL) && (*keyPtr != '\0')) // pTN이 NULL이아니고 *keyPtr이 NULL이아닐때
	{
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0')) // pTN의 key가 *keyPtr보다 작을때
			break; // 반복문나가기
		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL)) // pTN의 key가 *keyPtr보다 작고 pTN의 다음노드가 NULL이아닐동안반복
			pTN = pTN->getNext(); // pTN의 다음노드를 pTN으로 만들어줌
		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0')) // pTN이 NULL이아니고 pTN의 key가 *keyPtr랑 같을동안 반복
		{
			pTN = pTN->getChild(); // pTN의 child를 pTN으로 설정
			keyPtr++; // keyPtr를 1증가
		}
		if ((pTN->getKey() > * keyPtr) && (*keyPtr != '\0')) // pTN의 key가 * keyPtr보다 클때
			break; // 반복문 나가기
	} // end while for positioning
	/* Secondly, the given key string is a sub-string of an existing key */
	/* e.g.) trying to insert "abc" while "abcde" is already exisiting. */
	if ((pTN->getKey() != '\0') && (*keyPtr == '\0')) // pTN의 키가 NULL이아니고 *keyPtr이 NULL이아닐때
	{
		/* there was a longer key string already !! */
		/* break the longer key string, and connected to the separated key strings */
		pTN_New = new TrieNode<E>('\0', value); // 새로운 TrieNode pTN_New를 생성
		pTN_New->setParent(pTN->getParent()); // pTN_New의 부모를 pTN->getParent()로 설정
		(pTN->getParent())->setChild(pTN_New); // pTN->getParent()의 child를 pTN_New로 설정
		pTN_New->setNext(pTN); // pTN_New의 다음노드로 pTN을 설정
		pTN->setPrev(pTN_New); // pTN의 이전노드로 pTN_New을 설정
		//cout << "key (" << keyWord << ") is inserted" << endl;
		this->num_keys++; // key의 갯수를 1증가
		return; // 반환
	}
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0')) // pTN의 키가 *keyPtr보다작고 pTN의 다음노드가 NULL이고 *keyPtr이 NULL이아닐때
	{
		/* at this level, a new substring is inserted as the last nodes */
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); // pTN_New 생성
		pTN_New->setParent(pTN->getParent()); // pTN_New의 부모를 pTN->getParent()로 설정
		pTN_New->setPrev(pTN); // pTN_New의 이전노드로 pTN을 설정
		pTN->setNext(pTN_New); // pTN의 다음노드로 pTN_New를 설정
		pTN = pTN_New; // pTN을 pTN_New로 만들어줌
		keyPtr++; // keyPtr1증가
		while (*keyPtr != '\0') // *keyPtr이 null이 아닐때동안 반복
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); // pTN_New 생성
			pTN->setChild(pTN_New); // pTN의 자식노드로 pTN_New를 설정
			(pTN->getChild())->setParent(pTN); // pTN->getchild()의 부모노드를 pTN으로로 설정
			pTN = pTN->getChild(); // pTN의 자식노드를 pTN으로 설정
			keyPtr++; // keyPtr1증가
		}
		if (*keyPtr == '\0') //  *keyPtr이 null이면
		{
			insertExternalTN(pTN, keyWord, value); // 마지막에 외부노드 추가
			this->num_keys++; // KEY 갯수 1증가
			return;
		}
	}
	else if ((pTN->getKey() > * keyPtr) && (*keyPtr != '\0')) // pTN의 key가  * keyPtr 보다 크고 *keyPtr이 null이 아닐때
	{
		/* insert between two existing trie nodes */
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); // pTN_New 생성
		pTN_New->setNext(pTN); // pTN_New의 다음노드를 pTN으로 설정
		pTN_New->setParent(pTN->getParent()); // pTN_New의 부모노드를 pTN의 부모노드로 설정
		if (pTN->getPrev() == NULL) // pTN의 이전노드가 NULL이면
		{ /* this pTN_new becomes the new first in this level */
			if (pTN->getParent() != NULL) // pTN의 부모노드가 NULL이아니면
				(pTN->getParent())->setChild(pTN_New); // pTN의 부모노드의 자식노드를 pTN_New로 설정
		}
		else {
			(pTN->getPrev())->setNext(pTN_New); // 아니라면 pTN의 이전노드의 다음노드를 pTN_New로 설정
		}
		pTN_New->setPrev(pTN->getPrev()); // pTN_New의 다음노드를 pTN의 다음노드로 설정
		pTN->setPrev(pTN_New); // pTN의 이전노드를 pTN_New로 설정
		pTN = pTN_New; // pTN_New를 pTN으로 설정
		keyPtr++; // keyPtr1증가
		while (*keyPtr != '\0') // *keyPtr이 NULL이 아닐때 동안반복
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); // pTN_New 생성
			pTN->setChild(pTN_New); // pTN의 자식노드를 pTN_New로 설정
			(pTN->getChild())->setParent(pTN);// pTN->getchild()의 부모노드를 pTN으로 설정
			pTN = pTN->getChild(); // pTN의 자식노드를 pTN으로 설정
			keyPtr++; // keyPtr1증가
		}
		if (*keyPtr == '\0') //  *keyPtr이 NULL이면
		{
			insertExternalTN(pTN, keyWord, value); // 마지막에 외부노드를 추가
			this->num_keys++; // key 갯수를 1증가
			return;
		}
	}
}
template<typename E>
TrieNode<E>* Trie<E>::find(string keyWord) // keyword위치찾는 함수
{
	TrieNode<E>* pTN = NULL;
	pTN = _find(keyWord, FULL_MATCH); // keyword를 full_match모드로 찾아 pTN에저장
	return pTN;
}
template<typename E>
TrieNode<E>* Trie<E>::_find(string keyStr, SearchMode sm = FULL_MATCH)
{
	char* keyPtr = (char*)keyStr.c_str(); // string형 ketStr을 char*형으로 변환하여 keyPr에저장
	TrieNode<E>* pTN = NULL; // pTN을 NULL로 초기화
	TrieNode<E>* found = NULL; // found를 NULL로 초기화
	if (keyStr == "") // 전달받은 문자열이 NULL이면
		return NULL; // NULL을 반환
	pTN = this->_root; // root trie_node의 포인터를 pTN에 저장
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{ // pTN이 null이아니고 *keyPtr이 null이 아닐 때 계속 반복
		while ((pTN != NULL) && (pTN->getKey() < *keyPtr)) 
		{ // pTN이 null이아니고 pTN->getKey()가 *keyPtr보다 작을 때 반복
			if (pTN->getNext() == NULL) //pTN의 다음노드가 null이면
				return NULL;  // null을반환
			pTN = pTN->getNext(); // pTN의 다음노드를 pTN으로 만들어줌
		}
		if ((pTN != NULL) && (pTN->getKey() > * keyPtr))
		{  // pTN이 null이아니고 pTN->getKey()가 *keyPtr보다 크면
			// key not found
			return NULL; // NULL을 반환
		}
		else if ((pTN == NULL) && (*keyPtr != '\0'))
		{ // pTN이 null이고  *keyPtr이 ‘\0‘이면 // 더 이상 비교할 노드없음
			// key not found
			return NULL; // NULL 반환
		}
		else if ((pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))
		{  // pTN->getKey()가 *keyPtr와같고 *keyPtr이 ‘\0’이 아니면 
			pTN = pTN->getChild(); // pTN을 pTN의 자식노드의 포인터로 만들어줌
			keyPtr++; // keyPtr을 1증가
			if (*keyPtr == '\0') // 키를 다찾았다면
			{
				/* key or prefix found */
				if (sm == FULL_MATCH) // full match일때
				{
					if (pTN->getKey() == '\0') // full-match로 끝까지 찾았을때
					{
						/* found the key string as a full-match */
						return pTN; // pTN을 반환
					}
					else // (pTN->getKey() != '\0') // 접두어로만 포함
					{
						/* found the key string as a substring of a longer existing string */
						return NULL; // NULL을 반환
					}
				}
				else if (sm == PREFIX_MATCH) // PREFIX_MATCH일때
				{
					/* found the key string as a full-match or as a substring of a longer existing
					string */
					return pTN; // pTN을 반환
				}
			}
			else if ((pTN->getKey() == '\0') && (*keyPtr != '\0'))
			{ // pTN의 key는 NULL이지만 *keyPtr 는 NULL이 아닐때
				if (pTN->getNext() != NULL)
				{ // pTN의 다음노드가 null이아니면
					pTN = pTN->getNext(); // pTN의 다음노드를 pTN이 되게해주고
					continue; // 반복문 처음으로돌아가기
				}
				else  // pTN의 다음노드가 null이면
					return NULL; // null을 반환
			}
			else
			{
				continue; // 반복문 처음으로돌아감
			}
		}
	} // end while
}
template<typename E>
void Trie<E>::_traverse(TrieNode<E>* pTN, List_pVoca& list_keywords)
{
	if (pTN == NULL)  // pTN이 null이면 
		return; // 반환
	if (pTN->getChild() == NULL) // pTN의 자식노드가 NULL이면 
	{
		list_keywords.push_back(pTN->getValue()); // list_keyword에 pTN의 value를 넣기
	}
	else //  pTN의 자식노드가 NULL이아니면 
	{
		_traverse(pTN->getChild(), list_keywords); // pTN의 자식노드에대해 _traverse함수 실행
	}
	if (pTN->getNext() != NULL) // pTN의 다음노드가 NULL이아니면 
	{
		_traverse(pTN->getNext(), list_keywords);  // pTN의 다음노드에대해 _traverse함수 실행
	}
}
template<typename E>
void Trie<E>::findPrefixMatch(string pPrefix, List_pVoca& predictWords)
{ // 찾으려는 pPrefix, 단어를담을 predictWords
	TrieNode<E>* pTN = NULL; // pTN을 null로 초기화
	if (pPrefix == "") // pPrefix가 null이면
		return; // 반환

	pTN = _find(pPrefix, PREFIX_MATCH); // pPrefix의 위치를 PREFIX_MATCH로찾아 pTN에저장
	_traverse(pTN, predictWords); // pTN을 위치를 기반으로 예상단어들을 predict Words에 저장
	//printf("Error in TrieSearch (key: %s) !!\n", keyWord);
}
template<typename E>
void Trie<E>::deletekeyWord(string keyWord) // 키워드 삭제 함수
{
	TrieNode<E>* pTN = NULL, * _root;
	TrieNode<E>* tmp = NULL;
	int trie_val;
	_root = this->_root;
	if (NULL == _root || keyWord.length() == 0)
		return;
	pTN = _find(keyWord, FULL_MATCH);
	if (pTN == NULL)
	{
		cout << "Key [" << keyWord << "] not found in trie" << endl;
		return;
	}
	while (1)
	{
		if (pTN == NULL)
			break;
		if (pTN->getPrev() && pTN->getNext())
		{
			tmp = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			free(tmp);
			break;
		}
		else if (pTN->getPrev() && !(pTN->getNext()))
		{
			tmp = pTN;
			(pTN->getPrev())->setNext(NULL);
			free(tmp);
			break;
		}
		else if (!(pTN->getPrev()) && pTN->getNext())
		{
			tmp = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			pTN = pTN->getNext();
			pTN->setPrev(NULL);
			free(tmp);
			break;
		}
		else
		{
			tmp = pTN;
			pTN = pTN->getParent();
			if (pTN != NULL)
				pTN->setChild(NULL);
			free(tmp);
			if ((pTN == _root) && (pTN->getNext() == NULL) && (pTN->getPrev() == NULL))
			{
				cout << "Now, the trie is empty !!" << endl;
				break;
			}
		}
	}
	this->num_keys--;
}
template<typename E>
void Trie<E>::eraseTrie() // 트라이 삭제 함수
{
	TrieNode<E>* pTN;
	TrieNode<E>* pTN_to_be_deleted = NULL;
	if (this->_root == NULL)
		return;
	pTN = this->_root;
	/* delete the last key word first */
	while (pTN != NULL)
	{
		while ((pTN != NULL) && (pTN->getNext()))
			pTN = pTN->getNext();
		while (pTN->getChild())
		{
			if (pTN->getNext())
				break;
			pTN = pTN->getChild();
		}
		if (pTN->getNext())
			continue;
		if (pTN->getPrev() && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);
		}
		else if (pTN->getPrev() && !(pTN->getNext()))
		{
			pTN_to_be_deleted = pTN;
			(pTN->getPrev())->setNext(NULL);
			pTN = pTN->getPrev();
			free(pTN_to_be_deleted);
		}
		else if (!(pTN->getPrev()) && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			(pTN->getNext())->setPrev(NULL);
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);
		}
		else
		{
			pTN_to_be_deleted = pTN;
			if (pTN == this->_root)
			{
				/* _root */
				this->num_keys = 0;
				return;
			}
			if (pTN->getParent() != NULL)
			{
				pTN = pTN->getParent();
				pTN->setChild(NULL);
			}
			else
			{
				pTN = pTN->getPrev();
			}
			free(pTN_to_be_deleted);
		} // end if - else
	} // end while
}
template<typename E>
void Trie<E>::fprintTrie(ostream& fout) // 트라이 내부데이터 출력함수
{
	TrieNode<E>* pTN;
	int indent = 0;
	fout << "trie ( " << this->trie_name << ") with " << this->num_keys << " trie_nodes\n";
	if (this->num_keys == 0)
	{
		fout << "Empty trie !" << endl;
		return;
	}
	pTN = this->_root;
	pTN->_fprint(fout, pTN, indent);
}
#endif