#ifndef COMPLETE_BINARY_TREE_H
#define COMPLETE_BINARY_TREE_H
#include "TA_Entry.h"
#include "T_Entry.h"

#define CBT_ROOT 1 // 루트노드의 인덱스 = 1
using namespace std;
template<typename K, typename V>
class CompleteBinaryTree : public TA_Entry<K, V> // TA_Entry<K,V>를 상속받음
{
public:
	CompleteBinaryTree(int capa, string nm); // 생성자
	int add_at_end(T_Entry<K, V>& elem); // 마지막 위치에 elem을 집어넣는함수
	T_Entry<K, V>& getEndElement() { return this->t_GA[end]; } // 마지막위치의 원소를 읽어오는함수
	T_Entry<K, V>& getRootElement() { return this->t_GA[CBT_ROOT]; } // 첫번째위치의 원소를 읽어오는 함수
	int getEndIndex() { return end; } // 마지막원소의 인덱스를 읽어오는 함수
	void removeCBTEnd(); // 마지막위치의 원소를 제거하는함수
	void fprintCBT(ostream& fout); // 파일출력함수
	void fprintCBT_byLevel(ostream& fout); // 파일에 레벨별로 출력하는함수
protected:
	void _fprintCBT_byLevel(ostream& fout, int p, int level); // 파일에 레벨별로 출력하는함수 (재귀)
	int parentIndex(int index) { return index / 2; } // 부모노드의 인덱스
	int leftChildIndex(int index) { return index * 2; } // 왼쪽자식노드의 인덱스
	int rightChildIndex(int index) { return (index * 2 + 1); } // 오른쪽자식노드의 인덱스
	bool hasLeftChild(int index) { return ((index * 2) <= end); } // 왼쪽자식노드가 있는지 판별
	bool hasRightChild(int index) { return ((index * 2 + 1) <= end); } // 오른쪽자식노드가 있는지 판별
	int end;
};
template<typename K, typename V>
CompleteBinaryTree<K, V>::CompleteBinaryTree(int capa, string nm)
	:TA_Entry<K, V>(capa, nm)
{
	end = 0; // size = 0
}
template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT(ostream& fout)
{
	if (end <= 0) // 비어있다면
	{
		fout << this->getName() << " is empty now !!" << endl;
		return;
	}
	int count = 0;
	for (int i = 1; i <= end; i++)
	{
		fout << setw(3) << this->t_GA[i];
		if (i % 5 == 0)
			fout << endl <<" ";
		count++; // count를 1씩 늘려가며 출력
	}
}
template<typename K, typename V>
void CompleteBinaryTree<K, V>::_fprintCBT_byLevel(ostream& fout, int index, int level)
{
	int index_child;
	if (hasRightChild(index)) // index노드의 오른쪽 자식노드가있다면
	{
		index_child = rightChildIndex(index); // index_child는 index의 오른쪽 자식노드의 인덱스로설정
		_fprintCBT_byLevel(fout, index_child, level + 1); // level을 1만큼 증가시키고 함수재실행
	}
	for (int i = 0; i < level; i++)
		fout << "     "; // 레벨에 따라 칸띄움
	this->t_GA[index].fprint(fout);
	fout << endl;
	if (hasLeftChild(index)) // index노드의 왼쪽 자식노드가있다면
	{
		index_child = leftChildIndex(index); // index_child는 index의 왼쪽 자식노드의 인덱스로설정
		_fprintCBT_byLevel(fout, index_child, level + 1); // level을 1만큼 증가시키고 함수재실행
	}
}
template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT_byLevel(ostream& fout)
{
	if (end <= 0)
	{
		fout << "CBT is EMPTY now !!" << endl;
		return;
	}
	_fprintCBT_byLevel(fout, CBT_ROOT, 0); // 초기값
}
template<typename K, typename V>
int CompleteBinaryTree<K, V>::add_at_end(T_Entry<K, V>& elem)
{
	if (end >= TA_Entry<K, V>::capacity) // end가 capacity보다 크거나 같다면 
	{
		cout << this->getName() << " is FULL now !!" << endl;
		return end; // end값을 반환
	}
	end++; // end를 1만큼 증가한후
	this->t_GA[end] = elem; // elem을 t_GA[end]로 설정
	return end; // end 반환
}
template<typename K, typename V>
void CompleteBinaryTree<K, V>::removeCBTEnd()
{
	end--; // end를 1만큼 감소
	TA_Entry<K, V>::num_elements--; // num_elementsfmf 1만큼감소
}
#endif
