#ifndef T_ENTRY_H
#define T_ENTRY_H
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
template<typename K, typename V>
class T_Entry
{
	friend ostream& operator<<(ostream& fout, T_Entry<K, V>& entry)
	{
		fout << "(" << entry.getKey() << ": " << *(entry.getValue()) << ")";
		return fout;
	}
public:
	T_Entry(K key, V value) : _key(key), _value(value) {} // constructor
	T_Entry() { } // default constructor
	~T_Entry() {}
	void setKey(const K& key) { _key = key; }
	void setValue(const V& value) { _value = value; }
	K getKey() const { return _key; }
	V getValue() const { return _value; }
	bool operator>(const T_Entry<K, V>& right) const { return (_key > right.getKey()); }
	bool operator>=(const T_Entry<K, V>& right) const { return (_key >= right.getKey()); }
	bool operator<( T_Entry<K, V>& right)  { return (_key < right.getKey()); }
	bool operator<=(const T_Entry<K, V>& right) const { return (_key <= right.getKey()); }
	bool operator==(const T_Entry<K, V>& right) const
	{
		return ((_key == right.getKey()) && (_value == right.getValue()));
	}
	T_Entry<K, V>& operator=(T_Entry<K, V>& right)
	{
		_key = right.getKey();
		_value = right.getValue();

		return *this;
	}
	void fprint(ostream fout)
	{
		fout << "[key: " << setw(2) << _key << "  ," << *this->getValue() << "]";
	}
private:
	K _key;
	V _value;
};

#endif