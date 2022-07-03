#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H
#include "HashMap.h"
#define HASH_TABLE_SIZE 101
template <typename K, typename V>
class HashDict : public HashMap<K, V>
{
public: // public 
	typedef typename HashMap<K, V>::Iterator Iterator;
	typedef typename HashMap<K, V>::Entry Entry;
	// Range Ŭ����
	class Range { // an iterator range
	private:
		Iterator _begin; // range�� ó��
		Iterator _end; // range�� ������
	public:
		Range() {} // �⺻������
		Range(const Iterator& b, const Iterator& e) // ������
			: _begin(b), _end(e) { }
		Iterator& begin() { return _begin; } // _begin�� ��ȯ�ϴ� �Լ�
		Iterator& end() { return _end; } // _end�� ��ȯ�ϴ� �Լ�
	}; //
public: // public functions
	HashDict(int capacity = HASH_TABLE_SIZE); // constructor
	Range findAll(const K& k); //k�� ��� entry�� ã�� �Լ�
	Iterator insert(const K& k, const V& v); // ����
}; //

template <typename K, typename V> // ������
HashDict<K, V>::HashDict(int capacity) : HashMap<K, V>(capacity) { }

template <typename K, typename V> // ����
typename HashDict<K, V>::Iterator HashDict<K, V>::insert(const K& k, const V& v) 
{
	Iterator p = _find(k); // key�� iterator�� ã��
	Iterator q = _insert(p, Entry(k, v)); // ����
	return q; // q�� ��ȯ
}
template <typename K, typename V> // k�� ��� entry�� ã��
typename HashDict<K, V>::Range HashDict<K, V>::findAll(const K& k)
{
	Iterator b = _find(k); // k�� ����� iterator�� ã�� b������
	Iterator p = b; // b�� p������
	while (p != end() && (*p).getKey() == k)
	{ // find next entry with different key or end of bucket array
		++p;
	}
	return Range(b, p); // return range of positions
}
#endif