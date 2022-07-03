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
	Trie(string name); // ������
	int size() { return num_keys; } // ũ���ȯ �Լ�
	string getName() { return trie_name; } // �̸� ��ȯ�Լ�
	void insert(string keyStr, E value); // ����
	void insertExternalTN(TrieNode<E>* pTN, string keyStr, E value); // �ܺγ�����
	TrieNode<E>* find(string keyWord); // ��ġã���Լ�
	void findPrefixMatch(string prefix, List_pVoca& predictWords); // 
	void deletekeyWord(string keyWord); // KEYWORD���� �Լ�
	void eraseTrie(); // Trie��ü ����
	void fprintTrie(ostream& fout); // trie ����Լ�
protected:
	TrieNode<E>* _find(string keyStr, SearchMode sm = FULL_MATCH);
	void _traverse(TrieNode<E>* pTN, List_pVoca& list_keywords);
private:
	TrieNode<E>* _root; // root���
	int num_keys; // key�� ����
	string trie_name; // �̸�
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
} // ������
template<typename E>
void Trie<E>::insertExternalTN(TrieNode<E>* pTN, string keyStr, E value)
{
	TrieNode<E>* pTN_New = NULL;
	pTN_New = new TrieNode<E>('\0', value);
	pTN->setChild(pTN_New);
	(pTN->getChild())->setParent(pTN);
	pTN_New->setValue(value);
	//cout << "key (" << keyWord << ") is inserted \n";
} // �ܺγ�� ����
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
	while ((pTN != NULL) && (*keyPtr != '\0')) // pTN�� NULL�̾ƴϰ� *keyPtr�� NULL�̾ƴҶ�
	{
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0')) // pTN�� key�� *keyPtr���� ������
			break; // �ݺ���������
		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL)) // pTN�� key�� *keyPtr���� �۰� pTN�� ������尡 NULL�̾ƴҵ��ȹݺ�
			pTN = pTN->getNext(); // pTN�� ������带 pTN���� �������
		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0')) // pTN�� NULL�̾ƴϰ� pTN�� key�� *keyPtr�� �������� �ݺ�
		{
			pTN = pTN->getChild(); // pTN�� child�� pTN���� ����
			keyPtr++; // keyPtr�� 1����
		}
		if ((pTN->getKey() > * keyPtr) && (*keyPtr != '\0')) // pTN�� key�� * keyPtr���� Ŭ��
			break; // �ݺ��� ������
	} // end while for positioning
	/* Secondly, the given key string is a sub-string of an existing key */
	/* e.g.) trying to insert "abc" while "abcde" is already exisiting. */
	if ((pTN->getKey() != '\0') && (*keyPtr == '\0')) // pTN�� Ű�� NULL�̾ƴϰ� *keyPtr�� NULL�̾ƴҶ�
	{
		/* there was a longer key string already !! */
		/* break the longer key string, and connected to the separated key strings */
		pTN_New = new TrieNode<E>('\0', value); // ���ο� TrieNode pTN_New�� ����
		pTN_New->setParent(pTN->getParent()); // pTN_New�� �θ� pTN->getParent()�� ����
		(pTN->getParent())->setChild(pTN_New); // pTN->getParent()�� child�� pTN_New�� ����
		pTN_New->setNext(pTN); // pTN_New�� �������� pTN�� ����
		pTN->setPrev(pTN_New); // pTN�� �������� pTN_New�� ����
		//cout << "key (" << keyWord << ") is inserted" << endl;
		this->num_keys++; // key�� ������ 1����
		return; // ��ȯ
	}
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0')) // pTN�� Ű�� *keyPtr�����۰� pTN�� ������尡 NULL�̰� *keyPtr�� NULL�̾ƴҶ�
	{
		/* at this level, a new substring is inserted as the last nodes */
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); // pTN_New ����
		pTN_New->setParent(pTN->getParent()); // pTN_New�� �θ� pTN->getParent()�� ����
		pTN_New->setPrev(pTN); // pTN_New�� �������� pTN�� ����
		pTN->setNext(pTN_New); // pTN�� �������� pTN_New�� ����
		pTN = pTN_New; // pTN�� pTN_New�� �������
		keyPtr++; // keyPtr1����
		while (*keyPtr != '\0') // *keyPtr�� null�� �ƴҶ����� �ݺ�
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); // pTN_New ����
			pTN->setChild(pTN_New); // pTN�� �ڽĳ��� pTN_New�� ����
			(pTN->getChild())->setParent(pTN); // pTN->getchild()�� �θ��带 pTN���η� ����
			pTN = pTN->getChild(); // pTN�� �ڽĳ�带 pTN���� ����
			keyPtr++; // keyPtr1����
		}
		if (*keyPtr == '\0') //  *keyPtr�� null�̸�
		{
			insertExternalTN(pTN, keyWord, value); // �������� �ܺγ�� �߰�
			this->num_keys++; // KEY ���� 1����
			return;
		}
	}
	else if ((pTN->getKey() > * keyPtr) && (*keyPtr != '\0')) // pTN�� key��  * keyPtr ���� ũ�� *keyPtr�� null�� �ƴҶ�
	{
		/* insert between two existing trie nodes */
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); // pTN_New ����
		pTN_New->setNext(pTN); // pTN_New�� ������带 pTN���� ����
		pTN_New->setParent(pTN->getParent()); // pTN_New�� �θ��带 pTN�� �θ���� ����
		if (pTN->getPrev() == NULL) // pTN�� ������尡 NULL�̸�
		{ /* this pTN_new becomes the new first in this level */
			if (pTN->getParent() != NULL) // pTN�� �θ��尡 NULL�̾ƴϸ�
				(pTN->getParent())->setChild(pTN_New); // pTN�� �θ����� �ڽĳ�带 pTN_New�� ����
		}
		else {
			(pTN->getPrev())->setNext(pTN_New); // �ƴ϶�� pTN�� ��������� ������带 pTN_New�� ����
		}
		pTN_New->setPrev(pTN->getPrev()); // pTN_New�� ������带 pTN�� �������� ����
		pTN->setPrev(pTN_New); // pTN�� ������带 pTN_New�� ����
		pTN = pTN_New; // pTN_New�� pTN���� ����
		keyPtr++; // keyPtr1����
		while (*keyPtr != '\0') // *keyPtr�� NULL�� �ƴҶ� ���ȹݺ�
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); // pTN_New ����
			pTN->setChild(pTN_New); // pTN�� �ڽĳ�带 pTN_New�� ����
			(pTN->getChild())->setParent(pTN);// pTN->getchild()�� �θ��带 pTN���� ����
			pTN = pTN->getChild(); // pTN�� �ڽĳ�带 pTN���� ����
			keyPtr++; // keyPtr1����
		}
		if (*keyPtr == '\0') //  *keyPtr�� NULL�̸�
		{
			insertExternalTN(pTN, keyWord, value); // �������� �ܺγ�带 �߰�
			this->num_keys++; // key ������ 1����
			return;
		}
	}
}
template<typename E>
TrieNode<E>* Trie<E>::find(string keyWord) // keyword��ġã�� �Լ�
{
	TrieNode<E>* pTN = NULL;
	pTN = _find(keyWord, FULL_MATCH); // keyword�� full_match���� ã�� pTN������
	return pTN;
}
template<typename E>
TrieNode<E>* Trie<E>::_find(string keyStr, SearchMode sm = FULL_MATCH)
{
	char* keyPtr = (char*)keyStr.c_str(); // string�� ketStr�� char*������ ��ȯ�Ͽ� keyPr������
	TrieNode<E>* pTN = NULL; // pTN�� NULL�� �ʱ�ȭ
	TrieNode<E>* found = NULL; // found�� NULL�� �ʱ�ȭ
	if (keyStr == "") // ���޹��� ���ڿ��� NULL�̸�
		return NULL; // NULL�� ��ȯ
	pTN = this->_root; // root trie_node�� �����͸� pTN�� ����
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{ // pTN�� null�̾ƴϰ� *keyPtr�� null�� �ƴ� �� ��� �ݺ�
		while ((pTN != NULL) && (pTN->getKey() < *keyPtr)) 
		{ // pTN�� null�̾ƴϰ� pTN->getKey()�� *keyPtr���� ���� �� �ݺ�
			if (pTN->getNext() == NULL) //pTN�� ������尡 null�̸�
				return NULL;  // null����ȯ
			pTN = pTN->getNext(); // pTN�� ������带 pTN���� �������
		}
		if ((pTN != NULL) && (pTN->getKey() > * keyPtr))
		{  // pTN�� null�̾ƴϰ� pTN->getKey()�� *keyPtr���� ũ��
			// key not found
			return NULL; // NULL�� ��ȯ
		}
		else if ((pTN == NULL) && (*keyPtr != '\0'))
		{ // pTN�� null�̰�  *keyPtr�� ��\0���̸� // �� �̻� ���� ������
			// key not found
			return NULL; // NULL ��ȯ
		}
		else if ((pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))
		{  // pTN->getKey()�� *keyPtr�Ͱ��� *keyPtr�� ��\0���� �ƴϸ� 
			pTN = pTN->getChild(); // pTN�� pTN�� �ڽĳ���� �����ͷ� �������
			keyPtr++; // keyPtr�� 1����
			if (*keyPtr == '\0') // Ű�� ��ã�Ҵٸ�
			{
				/* key or prefix found */
				if (sm == FULL_MATCH) // full match�϶�
				{
					if (pTN->getKey() == '\0') // full-match�� ������ ã������
					{
						/* found the key string as a full-match */
						return pTN; // pTN�� ��ȯ
					}
					else // (pTN->getKey() != '\0') // ���ξ�θ� ����
					{
						/* found the key string as a substring of a longer existing string */
						return NULL; // NULL�� ��ȯ
					}
				}
				else if (sm == PREFIX_MATCH) // PREFIX_MATCH�϶�
				{
					/* found the key string as a full-match or as a substring of a longer existing
					string */
					return pTN; // pTN�� ��ȯ
				}
			}
			else if ((pTN->getKey() == '\0') && (*keyPtr != '\0'))
			{ // pTN�� key�� NULL������ *keyPtr �� NULL�� �ƴҶ�
				if (pTN->getNext() != NULL)
				{ // pTN�� ������尡 null�̾ƴϸ�
					pTN = pTN->getNext(); // pTN�� ������带 pTN�� �ǰ����ְ�
					continue; // �ݺ��� ó�����ε��ư���
				}
				else  // pTN�� ������尡 null�̸�
					return NULL; // null�� ��ȯ
			}
			else
			{
				continue; // �ݺ��� ó�����ε��ư�
			}
		}
	} // end while
}
template<typename E>
void Trie<E>::_traverse(TrieNode<E>* pTN, List_pVoca& list_keywords)
{
	if (pTN == NULL)  // pTN�� null�̸� 
		return; // ��ȯ
	if (pTN->getChild() == NULL) // pTN�� �ڽĳ�尡 NULL�̸� 
	{
		list_keywords.push_back(pTN->getValue()); // list_keyword�� pTN�� value�� �ֱ�
	}
	else //  pTN�� �ڽĳ�尡 NULL�̾ƴϸ� 
	{
		_traverse(pTN->getChild(), list_keywords); // pTN�� �ڽĳ�忡���� _traverse�Լ� ����
	}
	if (pTN->getNext() != NULL) // pTN�� ������尡 NULL�̾ƴϸ� 
	{
		_traverse(pTN->getNext(), list_keywords);  // pTN�� ������忡���� _traverse�Լ� ����
	}
}
template<typename E>
void Trie<E>::findPrefixMatch(string pPrefix, List_pVoca& predictWords)
{ // ã������ pPrefix, �ܾ���� predictWords
	TrieNode<E>* pTN = NULL; // pTN�� null�� �ʱ�ȭ
	if (pPrefix == "") // pPrefix�� null�̸�
		return; // ��ȯ

	pTN = _find(pPrefix, PREFIX_MATCH); // pPrefix�� ��ġ�� PREFIX_MATCH��ã�� pTN������
	_traverse(pTN, predictWords); // pTN�� ��ġ�� ������� ����ܾ���� predict Words�� ����
	//printf("Error in TrieSearch (key: %s) !!\n", keyWord);
}
template<typename E>
void Trie<E>::deletekeyWord(string keyWord) // Ű���� ���� �Լ�
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
void Trie<E>::eraseTrie() // Ʈ���� ���� �Լ�
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
void Trie<E>::fprintTrie(ostream& fout) // Ʈ���� ���ε����� ����Լ�
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