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
		fout << "[" << entry.getKey() << ", " << *(entry.getValue()) << "]";
		return fout;
	}
public:
	T_Entry(K key, V value) { _key = key; _value = value; } // 생성자
	T_Entry() { _key = 999; } // 기본생성자
	~T_Entry() {} // 소멸자
	void setKey(const K& key) { _key = key; }
	void setValue(const V& value) { _value = value; }
	K getKey() const { return _key; }
	V getValue() const { return _value; }
	bool operator>(const T_Entry<K, V>& right) { return (_key > right.getKey()); } //
	bool operator>=(T_Entry<K, V>& right);
	bool operator<(const T_Entry<K, V>& right) { return (_key < right.getKey()); }
	bool operator<=(T_Entry<K, V>& right);
	bool operator==(const T_Entry<K, V>& right)
	{
		return ((_key == right.getKey()) && (_value == right.getValue()));
	} // 비교연산자
	T_Entry<K, V>& operator=(T_Entry<K, V>& right); // 대입연산자
	void fprint(ostream& fout); // 출력연산자
private:
	K _key;
	V _value;
};

template<typename K, typename V>
void T_Entry<K, V>::fprint(ostream& fout)
{

	fout << "[key: " << setw(2) << _key << "  ," << *this->getValue() << "]";


} // 출력연산자 오버로딩
template<typename K, typename V>
T_Entry<K, V>& T_Entry<K, V>::operator=(T_Entry<K, V>& right)
{
	_value = right._value;
	_key = right._key;

	return *this;
} // 대입연산자
template<typename K, typename V>
bool T_Entry<K, V>::operator<=(T_Entry<K, V>& right)
{
	if (_key <= right._key)
		return 1;
	else
		return 0;
} // 비교연산자
template<typename K, typename V>
bool T_Entry<K, V>::operator>=(T_Entry<K, V>& right)
{
	if (_key >= right._key)
		return 1;
	else
		return 0;
} // 비교연산자
#endif