#ifndef T_BSTN_H
#define T_BSTN_H
#include "T_Entry.h"
template<typename K, typename V>
class T_BSTN // ����Ž��Ʈ�� ���
{
public:
	T_BSTN() : entry(), pPr(NULL), pLc(NULL), pRc(NULL) { } // �⺻������
	T_BSTN(T_Entry<K, V> e) : entry(e), pPr(NULL), pLc(NULL), pRc(NULL) { } // ������
	K getKey() { return entry.getKey(); } // key���� ��ȯ
	V getValue() { return entry.getValue(); } // value���� ��ȯ
	T_Entry<K, V>& getEntry() { return entry; } // entry���� ��ȯ
	void setEntry(T_Entry<K, V> e) { entry = e; } // entry�� ����
	T_BSTN<K, V>* getpPr() { return pPr; } // �θ��带 ��ȯ
	T_BSTN<K, V>* getpLc() { return pLc; } // ���� �ڽĳ�带 ��ȯ
	T_BSTN<K, V>* getpRc() { return pRc; } // ������ �ڽĳ�带 ��ȯ
	T_BSTN<K, V>** getppLc() { return &pLc; }  // ���� �ڽĳ�� �ּ�
	T_BSTN<K, V>** getppRc() { return &pRc; } // ������ �ڽĳ�� �ּ�
	void setpPr(T_BSTN<K, V>* pTN) { pPr = pTN; } // �θ��� ����
	void setpLc(T_BSTN<K, V>* pTN) { pLc = pTN; } // ���� �ڽĳ�� ����
	void setpRc(T_BSTN<K, V>* pTN) { pRc = pTN; } // ������ �ڽĳ�� ����
	T_Entry<K, V>& operator*() { return entry; } // ENTRY��ȯ �����ε��Լ�
private:
	T_Entry<K, V> entry; // ��Ʈ��
	T_BSTN<K, V>* pPr; // �θ���
	T_BSTN<K, V>* pLc; // ���� �ڽĳ��
	T_BSTN<K, V>* pRc; // ������ �ڽĳ��
};
#endif
