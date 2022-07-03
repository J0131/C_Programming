#ifndef HEAP_PRIO_QUEUE_H
#define HEAP_PRIO_QUEUE_H
#include "CompleteBinaryTree.h"
#include "TA_Entry.h"
#include "T_Entry.h"
#include <Windows.h>
#include <thread>
#include <process.h>
template<typename K, typename V>
class HeapPrioQueue : public CompleteBinaryTree<K, V> // CompleteBinaryTree<K, V>를 상속
{
public:
	HeapPrioQueue(int capa, string nm); // 생성자
	~HeapPrioQueue(); // 소멸자
	bool isEmpty() { return size() == 0; } // 비어있는지 확인
	bool isFull() { return size() == this->capacity; } // 가득차있는지 확인
	int insert(T_Entry<K, V>& elem); // elem을 큐에 삽입
	T_Entry<K, V>* removeHeapMin(); // 가장우선순위낮은 원소를 제거
	T_Entry<K, V>* getHeapMin(); // 가장 우선순위가 낮은 원소를 읽어오기
	void fprint(ostream& fout); // 파일에 출력
	int size() { return this->end; } // 큐의 size 읽어오기
private:
	CRITICAL_SECTION pCS_PriQ;
};
template<typename K, typename V>
HeapPrioQueue<K, V>::HeapPrioQueue(int capa, string nm)
	:CompleteBinaryTree<K, V>(capa, nm)
{
	InitializeCriticalSection(&pCS_PriQ);
} // 생성자
template<typename K, typename V>
HeapPrioQueue<K, V>::~HeapPrioQueue()
{
	DeleteCriticalSection(&pCS_PriQ);
} // 소멸자
template<typename K, typename V>
void HeapPrioQueue<K, V>::fprint(ostream& fout)
{
	if (size() <= 0) // size가 0보다작다면
	{
		fout << "HeapPriorityQueue is Empty !!" << endl;
		return; // 비어있으므로 return
	}
	else
		CompleteBinaryTree<K, V>::fprintCBT(fout); // 비어있지않다면 출력 fprintCBT 실행
}
template<typename K, typename V>
int HeapPrioQueue<K, V>::insert(T_Entry<K, V>& elem)
{
	int index, parent_index; // 삽입된노드의 위치, 부모노드의 위치를 가리킬 변수 선언  
	T_Entry<K, V> temp; // T_Entry<K,V>형의 데이터를 임시로 저장할변수 temp선언
	EnterCriticalSection(&pCS_PriQ);
	if (isFull()) // 현재 배열이 가득찼다면
	{
		cout << this->getName() << " is Full !!" << endl;
		LeaveCriticalSection(&pCS_PriQ);
		return size(); // 현재 배열의 size를 반환
	}
	
	index = this->add_at_end(elem); // 가득차지않았다면 마지막노드에 elem를 삽입하여 그위치를 index에 저장

	while (index != CBT_ROOT) // index노드가 루트노드가 아닐동안 반복
	{
		parent_index = this->parentIndex(index); // index의 부모노드의 위치를 parent_index 에 저장
		if (CompleteBinaryTree<K, V>::t_GA[index].getKey() > CompleteBinaryTree<K, V>::t_GA[parent_index].getKey())
			break; // index의 key값이 parent_index의 key값보다 더크면 반복문나가기
		else // index의 key값이 parent_index의 key값보다 작다면 정렬을 해야하므로
		{
			temp = CompleteBinaryTree<K, V>::t_GA[index];
			CompleteBinaryTree<K, V>::t_GA[index] = CompleteBinaryTree<K, V>::t_GA[parent_index];
			CompleteBinaryTree<K, V>::t_GA[parent_index] = temp; // parent_index의 노드와 index의 노드를 바꿔줌
			index = parent_index; // 다음 비교를 위해 parent_index를 index에 저장
		}
	}
	LeaveCriticalSection(&pCS_PriQ);
	return size(); // size를 읽어 반환
}
template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::getHeapMin()
{
	T_Entry<K, V>* pMinElem;
	if (size() <= 0)
	{
		return NULL;
	}
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = CompleteBinaryTree<K, V> ::getRootElement(); // getRootElement()의 값을 *pMinElem에 저장
	return pMinElem; // pMinElem를 반환
}
template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::removeHeapMin()
{
	int index_p, index_c, index_rc; // index를 저장할 변수선언
	T_Entry<K, V>* pMinElem; // Minimum element를 저장할 변수를 T_Entry<K, V>*형으로 선언
	T_Entry<K, V> temp, t_p, t_c; // T_Entry<K, V>형의 변수선언
	int HPQ_size = this->size(); // 현재 배열의 크기를 읽어와서 HPQ_size에저장
	if (HPQ_size <= 0)
	{
		return NULL; // 현재배열의 크기가 0보다작다면 NULL반환
	}
	EnterCriticalSection(&pCS_PriQ);
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>; // pMinElem 동적할당
	*pMinElem = this->getRootElement(); // 루트노드의 원소를 *pMinElem에 저장
	if (HPQ_size == 1)
	{
		this->removeCBTEnd(); // 만약 현재배열의 크기가 1이라면 end-- 수행
	}
	else
	{
		index_p = CBT_ROOT; // index_p를 루트노드의 인덱스로 만들어줌
		CompleteBinaryTree<K, V>::t_GA[CBT_ROOT] = CompleteBinaryTree<K, V>::t_GA[this->end]; // 루트노드에 t_GA[end]를 저장
		this->end--; // end를 1만큼 감소시킨다

		while (this->hasLeftChild(index_p)) // index_p의 왼쪽자식이 있는동안 반복
		{
			index_c = this->leftChildIndex(index_p); // index_p의 왼쪽자식노드의 위치를 index_c로 설정
			index_rc = this->rightChildIndex(index_p); // index_p의 오른쪽자식노드의 위치를 index_rc로 설정
			if (this->hasRightChild(index_p) && (CompleteBinaryTree<K, V>::t_GA[index_c] > CompleteBinaryTree<K, V>::t_GA[index_rc]))
				index_c = index_rc; // index_p노드의 왼쪽자식노드가 오른쪽자식노드보다 더크다면 index_rc를 index_c로설정
			t_p = CompleteBinaryTree<K, V>::t_GA[index_p]; // index_p위치의 원소를 t_p
			t_c = CompleteBinaryTree<K, V>::t_GA[index_c]; // index_p위치의 원소를 t_c
			if (t_p > t_c) // t_p의 key가 t_c의 key보다 크다면 swap
			{
				temp = CompleteBinaryTree<K, V>::t_GA[index_p];
				CompleteBinaryTree<K, V>::t_GA[index_p] = CompleteBinaryTree<K, V>::t_GA[index_c];
				CompleteBinaryTree<K, V>::t_GA[index_c] = temp; // index_c와 index_p를 swap해준다
				index_p = index_c; // 계속 비교하기위해 index_c를 index_p로 설정
			}
			else
				break; // t_p의 key가 t_c의 key보다 크지않다면 반복문 나가기
		} // while문 종료
	}
	LeaveCriticalSection(&pCS_PriQ);
	return pMinElem;
}
#endif
