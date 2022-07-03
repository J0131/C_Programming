#ifndef T_ENTRY_H
#define T_ENTRY_H
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
template<typename K, typename V>
class Entry
{
	friend ostream& operator<<(ostream& fout, Entry<K, V>& entry)
	{
		fout << "[key:" << setw(2) << entry.getKey() << "] ";
		return fout;
	}
public:
	Entry(const K& key = K(), const V& value = V()) :_key(key),_value(value){  } // ������
	~Entry() {} // �Ҹ���
	void setKey(const K& key) { _key = key; }
	void setValue(const V& value) { _value = value; }
	K getKey() const { return _key; }
	V getValue() const { return _value; }
	bool operator>(const Entry<K, V>& right) { return (_key > right.getKey()); } //
	bool operator>=(Entry<K, V>& right);
	bool operator<(const Entry<K, V>& right) { return (_key < right.getKey()); }
	bool operator<=(Entry<K, V>& right);
	bool operator==(const Entry<K, V>& right)
	{
		return ((_key == right.getKey()) && (_value == right.getValue()));
	} // �񱳿�����
	void operator=(const Entry<K, V>& right)
	{
		_key = right._key;
		_value = right._value;
	} // �񱳿�����
	Entry<K, V>& operator=(Entry<K, V>& right); // ���Կ�����
	void fprint(ostream& fout); // ��¿�����
private:
	K _key;
	V _value;
};

template<typename K, typename V>
void Entry<K, V>::fprint(ostream& fout)
{

	fout << "[key: " << setw(2) << _key << "  ," << *this->getValue() << "]";


} // ��¿����� �����ε�
template<typename K, typename V>
Entry<K, V>& Entry<K, V>::operator=(Entry<K, V>& right)
{
	_value = right._value;
	_key = right._key;

	return *this;
} // ���Կ�����
template<typename K, typename V>
bool Entry<K, V>::operator<=(Entry<K, V>& right)
{
	if (_key <= right._key)
		return 1;
	else
		return 0;
} // �񱳿�����
template<typename K, typename V>
bool Entry<K, V>::operator>=(Entry<K, V>& right)
{
	if (_key >= right._key)
		return 1;
	else
		return 0;
} // �񱳿�����
#endif

