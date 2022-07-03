#ifndef HEAP_PRIO_QUEUE_H
#define HEAP_PRIO_QUEUE_H
#include "CompleteBinaryTree.h"
#include "TA_Entry.h"
#include "T_Entry.h"
#include <Windows.h>
#include <thread>
#include <process.h>
template<typename K, typename V>
class HeapPrioQueue : public CompleteBinaryTree<K, V> // CompleteBinaryTree<K, V>�� ���
{
public:
	HeapPrioQueue(int capa, string nm); // ������
	~HeapPrioQueue(); // �Ҹ���
	bool isEmpty() { return size() == 0; } // ����ִ��� Ȯ��
	bool isFull() { return size() == this->capacity; } // �������ִ��� Ȯ��
	int insert(T_Entry<K, V>& elem); // elem�� ť�� ����
	T_Entry<K, V>* removeHeapMin(); // ����켱�������� ���Ҹ� ����
	T_Entry<K, V>* getHeapMin(); // ���� �켱������ ���� ���Ҹ� �о����
	void fprint(ostream& fout); // ���Ͽ� ���
	int size() { return this->end; } // ť�� size �о����
private:
	CRITICAL_SECTION pCS_PriQ;
};
template<typename K, typename V>
HeapPrioQueue<K, V>::HeapPrioQueue(int capa, string nm)
	:CompleteBinaryTree<K, V>(capa, nm)
{
	InitializeCriticalSection(&pCS_PriQ);
} // ������
template<typename K, typename V>
HeapPrioQueue<K, V>::~HeapPrioQueue()
{
	DeleteCriticalSection(&pCS_PriQ);
} // �Ҹ���
template<typename K, typename V>
void HeapPrioQueue<K, V>::fprint(ostream& fout)
{
	if (size() <= 0) // size�� 0�����۴ٸ�
	{
		fout << "HeapPriorityQueue is Empty !!" << endl;
		return; // ��������Ƿ� return
	}
	else
		CompleteBinaryTree<K, V>::fprintCBT(fout); // ��������ʴٸ� ��� fprintCBT ����
}
template<typename K, typename V>
int HeapPrioQueue<K, V>::insert(T_Entry<K, V>& elem)
{
	int index, parent_index; // ���Եȳ���� ��ġ, �θ����� ��ġ�� ����ų ���� ����  
	T_Entry<K, V> temp; // T_Entry<K,V>���� �����͸� �ӽ÷� �����Һ��� temp����
	EnterCriticalSection(&pCS_PriQ);
	if (isFull()) // ���� �迭�� ����á�ٸ�
	{
		cout << this->getName() << " is Full !!" << endl;
		LeaveCriticalSection(&pCS_PriQ);
		return size(); // ���� �迭�� size�� ��ȯ
	}
	
	index = this->add_at_end(elem); // ���������ʾҴٸ� ��������忡 elem�� �����Ͽ� ����ġ�� index�� ����

	while (index != CBT_ROOT) // index��尡 ��Ʈ��尡 �ƴҵ��� �ݺ�
	{
		parent_index = this->parentIndex(index); // index�� �θ����� ��ġ�� parent_index �� ����
		if (CompleteBinaryTree<K, V>::t_GA[index].getKey() > CompleteBinaryTree<K, V>::t_GA[parent_index].getKey())
			break; // index�� key���� parent_index�� key������ ��ũ�� �ݺ���������
		else // index�� key���� parent_index�� key������ �۴ٸ� ������ �ؾ��ϹǷ�
		{
			temp = CompleteBinaryTree<K, V>::t_GA[index];
			CompleteBinaryTree<K, V>::t_GA[index] = CompleteBinaryTree<K, V>::t_GA[parent_index];
			CompleteBinaryTree<K, V>::t_GA[parent_index] = temp; // parent_index�� ���� index�� ��带 �ٲ���
			index = parent_index; // ���� �񱳸� ���� parent_index�� index�� ����
		}
	}
	LeaveCriticalSection(&pCS_PriQ);
	return size(); // size�� �о� ��ȯ
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
	*pMinElem = CompleteBinaryTree<K, V> ::getRootElement(); // getRootElement()�� ���� *pMinElem�� ����
	return pMinElem; // pMinElem�� ��ȯ
}
template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::removeHeapMin()
{
	int index_p, index_c, index_rc; // index�� ������ ��������
	T_Entry<K, V>* pMinElem; // Minimum element�� ������ ������ T_Entry<K, V>*������ ����
	T_Entry<K, V> temp, t_p, t_c; // T_Entry<K, V>���� ��������
	int HPQ_size = this->size(); // ���� �迭�� ũ�⸦ �о�ͼ� HPQ_size������
	if (HPQ_size <= 0)
	{
		return NULL; // ����迭�� ũ�Ⱑ 0�����۴ٸ� NULL��ȯ
	}
	EnterCriticalSection(&pCS_PriQ);
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>; // pMinElem �����Ҵ�
	*pMinElem = this->getRootElement(); // ��Ʈ����� ���Ҹ� *pMinElem�� ����
	if (HPQ_size == 1)
	{
		this->removeCBTEnd(); // ���� ����迭�� ũ�Ⱑ 1�̶�� end-- ����
	}
	else
	{
		index_p = CBT_ROOT; // index_p�� ��Ʈ����� �ε����� �������
		CompleteBinaryTree<K, V>::t_GA[CBT_ROOT] = CompleteBinaryTree<K, V>::t_GA[this->end]; // ��Ʈ��忡 t_GA[end]�� ����
		this->end--; // end�� 1��ŭ ���ҽ�Ų��

		while (this->hasLeftChild(index_p)) // index_p�� �����ڽ��� �ִµ��� �ݺ�
		{
			index_c = this->leftChildIndex(index_p); // index_p�� �����ڽĳ���� ��ġ�� index_c�� ����
			index_rc = this->rightChildIndex(index_p); // index_p�� �������ڽĳ���� ��ġ�� index_rc�� ����
			if (this->hasRightChild(index_p) && (CompleteBinaryTree<K, V>::t_GA[index_c] > CompleteBinaryTree<K, V>::t_GA[index_rc]))
				index_c = index_rc; // index_p����� �����ڽĳ�尡 �������ڽĳ�庸�� ��ũ�ٸ� index_rc�� index_c�μ���
			t_p = CompleteBinaryTree<K, V>::t_GA[index_p]; // index_p��ġ�� ���Ҹ� t_p
			t_c = CompleteBinaryTree<K, V>::t_GA[index_c]; // index_p��ġ�� ���Ҹ� t_c
			if (t_p > t_c) // t_p�� key�� t_c�� key���� ũ�ٸ� swap
			{
				temp = CompleteBinaryTree<K, V>::t_GA[index_p];
				CompleteBinaryTree<K, V>::t_GA[index_p] = CompleteBinaryTree<K, V>::t_GA[index_c];
				CompleteBinaryTree<K, V>::t_GA[index_c] = temp; // index_c�� index_p�� swap���ش�
				index_p = index_c; // ��� ���ϱ����� index_c�� index_p�� ����
			}
			else
				break; // t_p�� key�� t_c�� key���� ũ���ʴٸ� �ݺ��� ������
		} // while�� ����
	}
	LeaveCriticalSection(&pCS_PriQ);
	return pMinElem;
}
#endif
