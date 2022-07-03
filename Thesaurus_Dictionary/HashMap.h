#ifndef HASHMAP_H
#define HASHMAP_H
#include <list>
#include <vector>
#include "Entry.h"
#include "CyclicShiftHashCode.h"
#define DEFAULT_HASH_TABLE_SIZE 101
template <typename K, typename V> // key,value
class HashMap {
public: // public 
	typedef Entry<const K, V> Entry; // a (key, value) pair
	class Iterator;
public:
	HashMap(int capacity = DEFAULT_HASH_TABLE_SIZE); // 생성자
	int size() const { return num_ent; } // entry의 갯수
	bool empty() const { return (num_ent== 0); } // map이 비어있는지 확인
	Iterator find(const K& k); // key의 엔트리를 찾는 함수
	Iterator insert(const K& k, const V& v); // key, value를 가진 엔트리 삽입
	void erase(const K& k); // remove entry with key k
	void erase(const Iterator& p); // erase entry at p
	Iterator begin(); // haspmap의 첫번째 엔트리의 iterator
	Iterator end(); // haspmap의 마지막 엔트리의 iterator

protected: // protected
	Iterator _find(const K& k); // find utility
	Iterator _insert(const Iterator& p, const Entry& e); // insert utility
	void _erase(const Iterator& p); // remove utility
	static bool _endOfBkt(const Iterator& p) // 버켓의 마지막인지 확인 
	{
		return p.ent == p.bkt->end();
	}
	typedef std::list<Entry> Bucket;// 버켓생성
	typedef std::vector<Bucket> BktArray;// 버켓어레이 생성
	typedef typename BktArray::iterator BItor;// 버켓 iterator
	typedef typename Bucket::iterator EItor;// 엔트리 iterator
private:
	int num_ent; // 엔트리으이 갯수
	BktArray B; // bucket array (Hash Table)
public: // public
	void fprintBucketSizes(ostream& fout); // 버켓크기 출력
	void fprintBucket(ostream& fout, BItor bkt); // 버켓출력
	class Iterator { // haspmap의 iterator
	protected:
		const BktArray* ba; // 버킷어레이
		BItor bkt; // bucket의 iterator
		EItor ent; // entry의 iterator
	public:
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor()) // 생성자
			: ba(&a), bkt(b), ent(q) { }
		Iterator() {} // 기본생성자
		V getValue() { Entry& e = *ent; return e.getValue(); }
		K getKey() const { return _key; }
		Entry& operator*() const; // entry를 반환하는 함수
		bool operator==(const Iterator& p) const; // iterator가 같은지
		bool operator!=(const Iterator& p) const; // iterator가 같은지
		Iterator& operator++(); // 다음entry로 증감
		friend class HashMap; // give HashMap access
	}; 
}; 
#endif