#ifndef T_BSTN_H
#define T_BSTN_H
#include "T_Entry.h"
template<typename K, typename V>
class T_BSTN // 이진탐색트리 노드
{
public:
	T_BSTN() : entry(), pPr(NULL), pLc(NULL), pRc(NULL) { } // 기본생성자
	T_BSTN(T_Entry<K, V> e) : entry(e), pPr(NULL), pLc(NULL), pRc(NULL) { } // 생성자
	K getKey() { return entry.getKey(); } // key값을 반환
	V getValue() { return entry.getValue(); } // value값을 반환
	T_Entry<K, V>& getEntry() { return entry; } // entry값을 반환
	void setEntry(T_Entry<K, V> e) { entry = e; } // entry를 설정
	T_BSTN<K, V>* getpPr() { return pPr; } // 부모노드를 반환
	T_BSTN<K, V>* getpLc() { return pLc; } // 왼쪽 자식노드를 반환
	T_BSTN<K, V>* getpRc() { return pRc; } // 오른쪽 자식노드를 반환
	T_BSTN<K, V>** getppLc() { return &pLc; }  // 왼쪽 자식노드 주소
	T_BSTN<K, V>** getppRc() { return &pRc; } // 오른쪽 자식노드 주소
	void setpPr(T_BSTN<K, V>* pTN) { pPr = pTN; } // 부모노드 설정
	void setpLc(T_BSTN<K, V>* pTN) { pLc = pTN; } // 왼쪽 자식노드 설정
	void setpRc(T_BSTN<K, V>* pTN) { pRc = pTN; } // 오른쪽 자식노드 설정
	T_Entry<K, V>& operator*() { return entry; } // ENTRY반환 오버로딩함수
private:
	T_Entry<K, V> entry; // 엔트리
	T_BSTN<K, V>* pPr; // 부모노드
	T_BSTN<K, V>* pLc; // 왼쪽 자식노드
	T_BSTN<K, V>* pRc; // 오른쪽 자식노드
};
#endif
