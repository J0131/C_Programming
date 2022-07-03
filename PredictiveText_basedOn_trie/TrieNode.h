#ifndef TRIE_NODE_H
#define TRIE_NODE_H
#include <iostream>
#include <string>
#include <list>
#define VALUE_INTERNAL_NODE NULL

using namespace std;

template <typename E>
class TrieNode
{
public:
	TrieNode() {} // 기본생성자
	TrieNode(char k, E v) : key(k), value(v) // 생성자
	{
		prev = next = parent = child = NULL;
	}
	void setKey(char k) { key = k; } // 키 설정
	void setValue(E v) { value = v; } // VALUE 설정
	void setNext(TrieNode<E>* nxt) { next = nxt; } // next 설정
	void setPrev(TrieNode<E>* pv) { prev = pv; } // prev 설정
	void setParent(TrieNode<E>* pr) { parent = pr; } // parent설정
	void setChild(TrieNode<E>* chld) { child = chld; } // child 설정
	char getKey() { return key; } // key 받아오는 함수
	E getValue() { return value; } // value 받아오는 함수
	TrieNode<E>* getPrev() { return prev; } // prev 받아오는 함수
	TrieNode<E>* getNext() { return next; } // next 받아오는 함수
	TrieNode<E>* getParent() { return parent; } // parent 받아오는 함수
	TrieNode<E>* getChild() { return child; } // child 받아오는 함수
	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent); // 트라이노드의 키값을 출력하는 함수
private:
	char key; // key
	E value; // value
	TrieNode<E>* prev; // 이전노드
	TrieNode<E>* next; // 다음노드
	TrieNode<E>* parent; // 부모노드
	TrieNode<E>* child; // 자식노드
}; // 데이터멤버

template<typename E>
void TrieNode<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent) // trienode의 key 출력 함수
{
	if (pTN == NULL) // pTN이 NULL이면
	{
		fout << endl; // 띄워쓰기
		return;
	}
	else
	{
		fout << pTN->key; // pTN의 key를 출력
		_fprint(fout, pTN->child, indent + 1); // indent를 1만큼 늘리고 pTN의 자식노드의 키를 출력
		if (pTN->next == NULL) // pTN의 다음노드가없다면
		{
			return; // RETURN
		}
		for (int i = 0; i < indent; i++)
		{
			fout << " "; // indent갯수만큼 들여쓰기한후
		}
		_fprint(fout, pTN->next, indent); // pTN의다음노드를 indent만큼 출력
	}
}

#endif