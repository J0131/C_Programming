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
	// Range 클래스
	class Range { // an iterator range
	private:
		Iterator _begin; // range의 처음
		Iterator _end; // range의 마지막
	public:
		Range() {} // 기본생성자
		Range(const Iterator& b, const Iterator& e) // 생성자
			: _begin(b), _end(e) { }
		Iterator& begin() { return _begin; } // _begin을 반환하는 함수
		Iterator& end() { return _end; } // _end를 반환하는 함수
	}; //
public: // public functions
	HashDict(int capacity = HASH_TABLE_SIZE); // constructor
	Range findAll(const K& k); //k의 모든 entry를 찾은 함수
	Iterator insert(const K& k, const V& v); // 삽입
}; //

template <typename K, typename V> // 생성자
HashDict<K, V>::HashDict(int capacity) : HashMap<K, V>(capacity) { }

template <typename K, typename V> // 삽입
typename HashDict<K, V>::Iterator HashDict<K, V>::insert(const K& k, const V& v) 
{
	Iterator p = _find(k); // key의 iterator를 찾기
	Iterator q = _insert(p, Entry(k, v)); // 삽입
	return q; // q를 반환
}
template <typename K, typename V> // k의 모든 entry를 찾기
typename HashDict<K, V>::Range HashDict<K, V>::findAll(const K& k)
{
	Iterator b = _find(k); // k가 저장된 iterator를 찾아 b에저장
	Iterator p = b; // b를 p에저장
	while (p != end() && (*p).getKey() == k)
	{ // find next entry with different key or end of bucket array
		++p;
	}
	return Range(b, p); // return range of positions
}
#endif