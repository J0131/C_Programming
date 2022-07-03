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
	T_Entry(K key, V value) { _key = key; _value = value; } // ������
	T_Entry() { _key = 999; } // �⺻������
	~T_Entry() {} // �Ҹ���
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
	} // �񱳿�����
	T_Entry<K, V>& operator=(T_Entry<K, V>& right); // ���Կ�����
	void fprint(ostream& fout); // ��¿�����
private:
	K _key;
	V _value;
};

template<typename K, typename V>
void T_Entry<K, V>::fprint(ostream& fout)
{

	fout << "[key: " << setw(2) << _key << "  ," << *this->getValue() << "]";


} // ��¿����� �����ε�
template<typename K, typename V>
T_Entry<K, V>& T_Entry<K, V>::operator=(T_Entry<K, V>& right)
{
	_value = right._value;
	_key = right._key;

	return *this;
} // ���Կ�����
template<typename K, typename V>
bool T_Entry<K, V>::operator<=(T_Entry<K, V>& right)
{
	if (_key <= right._key)
		return 1;
	else
		return 0;
} // �񱳿�����
template<typename K, typename V>
bool T_Entry<K, V>::operator>=(T_Entry<K, V>& right)
{
	if (_key >= right._key)
		return 1;
	else
		return 0;
} // �񱳿�����
#endif