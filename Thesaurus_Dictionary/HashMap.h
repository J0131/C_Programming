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
	HashMap(int capacity = DEFAULT_HASH_TABLE_SIZE); // ������
	int size() const { return num_ent; } // entry�� ����
	bool empty() const { return (num_ent== 0); } // map�� ����ִ��� Ȯ��
	Iterator find(const K& k); // key�� ��Ʈ���� ã�� �Լ�
	Iterator insert(const K& k, const V& v); // key, value�� ���� ��Ʈ�� ����
	void erase(const K& k); // remove entry with key k
	void erase(const Iterator& p); // erase entry at p
	Iterator begin(); // haspmap�� ù��° ��Ʈ���� iterator
	Iterator end(); // haspmap�� ������ ��Ʈ���� iterator

protected: // protected
	Iterator _find(const K& k); // find utility
	Iterator _insert(const Iterator& p, const Entry& e); // insert utility
	void _erase(const Iterator& p); // remove utility
	static bool _endOfBkt(const Iterator& p) // ������ ���������� Ȯ�� 
	{
		return p.ent == p.bkt->end();
	}
	typedef std::list<Entry> Bucket;// ���ϻ���
	typedef std::vector<Bucket> BktArray;// ���Ͼ�� ����
	typedef typename BktArray::iterator BItor;// ���� iterator
	typedef typename Bucket::iterator EItor;// ��Ʈ�� iterator
private:
	int num_ent; // ��Ʈ������ ����
	BktArray B; // bucket array (Hash Table)
public: // public
	void fprintBucketSizes(ostream& fout); // ����ũ�� ���
	void fprintBucket(ostream& fout, BItor bkt); // �������
	class Iterator { // haspmap�� iterator
	protected:
		const BktArray* ba; // ��Ŷ���
		BItor bkt; // bucket�� iterator
		EItor ent; // entry�� iterator
	public:
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor()) // ������
			: ba(&a), bkt(b), ent(q) { }
		Iterator() {} // �⺻������
		V getValue() { Entry& e = *ent; return e.getValue(); }
		K getKey() const { return _key; }
		Entry& operator*() const; // entry�� ��ȯ�ϴ� �Լ�
		bool operator==(const Iterator& p) const; // iterator�� ������
		bool operator!=(const Iterator& p) const; // iterator�� ������
		Iterator& operator++(); // ����entry�� ����
		friend class HashMap; // give HashMap access
	}; 
}; 
#endif