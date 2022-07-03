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
	TrieNode() {} // �⺻������
	TrieNode(char k, E v) : key(k), value(v) // ������
	{
		prev = next = parent = child = NULL;
	}
	void setKey(char k) { key = k; } // Ű ����
	void setValue(E v) { value = v; } // VALUE ����
	void setNext(TrieNode<E>* nxt) { next = nxt; } // next ����
	void setPrev(TrieNode<E>* pv) { prev = pv; } // prev ����
	void setParent(TrieNode<E>* pr) { parent = pr; } // parent����
	void setChild(TrieNode<E>* chld) { child = chld; } // child ����
	char getKey() { return key; } // key �޾ƿ��� �Լ�
	E getValue() { return value; } // value �޾ƿ��� �Լ�
	TrieNode<E>* getPrev() { return prev; } // prev �޾ƿ��� �Լ�
	TrieNode<E>* getNext() { return next; } // next �޾ƿ��� �Լ�
	TrieNode<E>* getParent() { return parent; } // parent �޾ƿ��� �Լ�
	TrieNode<E>* getChild() { return child; } // child �޾ƿ��� �Լ�
	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent); // Ʈ���̳���� Ű���� ����ϴ� �Լ�
private:
	char key; // key
	E value; // value
	TrieNode<E>* prev; // �������
	TrieNode<E>* next; // �������
	TrieNode<E>* parent; // �θ���
	TrieNode<E>* child; // �ڽĳ��
}; // �����͸��

template<typename E>
void TrieNode<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent) // trienode�� key ��� �Լ�
{
	if (pTN == NULL) // pTN�� NULL�̸�
	{
		fout << endl; // �������
		return;
	}
	else
	{
		fout << pTN->key; // pTN�� key�� ���
		_fprint(fout, pTN->child, indent + 1); // indent�� 1��ŭ �ø��� pTN�� �ڽĳ���� Ű�� ���
		if (pTN->next == NULL) // pTN�� ������尡���ٸ�
		{
			return; // RETURN
		}
		for (int i = 0; i < indent; i++)
		{
			fout << " "; // indent������ŭ �鿩��������
		}
		_fprint(fout, pTN->next, indent); // pTN�Ǵ�����带 indent��ŭ ���
	}
}

#endif