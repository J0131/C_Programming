#ifndef COMPLETE_BINARY_TREE_H
#define COMPLETE_BINARY_TREE_H
#include "TA_Entry.h"
#include "T_Entry.h"

#define CBT_ROOT 1 // ��Ʈ����� �ε��� = 1
using namespace std;
template<typename K, typename V>
class CompleteBinaryTree : public TA_Entry<K, V> // TA_Entry<K,V>�� ��ӹ���
{
public:
	CompleteBinaryTree(int capa, string nm); // ������
	int add_at_end(T_Entry<K, V>& elem); // ������ ��ġ�� elem�� ����ִ��Լ�
	T_Entry<K, V>& getEndElement() { return this->t_GA[end]; } // ��������ġ�� ���Ҹ� �о�����Լ�
	T_Entry<K, V>& getRootElement() { return this->t_GA[CBT_ROOT]; } // ù��°��ġ�� ���Ҹ� �о���� �Լ�
	int getEndIndex() { return end; } // ������������ �ε����� �о���� �Լ�
	void removeCBTEnd(); // ��������ġ�� ���Ҹ� �����ϴ��Լ�
	void fprintCBT(ostream& fout); // ��������Լ�
	void fprintCBT_byLevel(ostream& fout); // ���Ͽ� �������� ����ϴ��Լ�
protected:
	void _fprintCBT_byLevel(ostream& fout, int p, int level); // ���Ͽ� �������� ����ϴ��Լ� (���)
	int parentIndex(int index) { return index / 2; } // �θ����� �ε���
	int leftChildIndex(int index) { return index * 2; } // �����ڽĳ���� �ε���
	int rightChildIndex(int index) { return (index * 2 + 1); } // �������ڽĳ���� �ε���
	bool hasLeftChild(int index) { return ((index * 2) <= end); } // �����ڽĳ�尡 �ִ��� �Ǻ�
	bool hasRightChild(int index) { return ((index * 2 + 1) <= end); } // �������ڽĳ�尡 �ִ��� �Ǻ�
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
	if (end <= 0) // ����ִٸ�
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
		count++; // count�� 1�� �÷����� ���
	}
}
template<typename K, typename V>
void CompleteBinaryTree<K, V>::_fprintCBT_byLevel(ostream& fout, int index, int level)
{
	int index_child;
	if (hasRightChild(index)) // index����� ������ �ڽĳ�尡�ִٸ�
	{
		index_child = rightChildIndex(index); // index_child�� index�� ������ �ڽĳ���� �ε����μ���
		_fprintCBT_byLevel(fout, index_child, level + 1); // level�� 1��ŭ ������Ű�� �Լ������
	}
	for (int i = 0; i < level; i++)
		fout << "     "; // ������ ���� ĭ���
	this->t_GA[index].fprint(fout);
	fout << endl;
	if (hasLeftChild(index)) // index����� ���� �ڽĳ�尡�ִٸ�
	{
		index_child = leftChildIndex(index); // index_child�� index�� ���� �ڽĳ���� �ε����μ���
		_fprintCBT_byLevel(fout, index_child, level + 1); // level�� 1��ŭ ������Ű�� �Լ������
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
	_fprintCBT_byLevel(fout, CBT_ROOT, 0); // �ʱⰪ
}
template<typename K, typename V>
int CompleteBinaryTree<K, V>::add_at_end(T_Entry<K, V>& elem)
{
	if (end >= TA_Entry<K, V>::capacity) // end�� capacity���� ũ�ų� ���ٸ� 
	{
		cout << this->getName() << " is FULL now !!" << endl;
		return end; // end���� ��ȯ
	}
	end++; // end�� 1��ŭ ��������
	this->t_GA[end] = elem; // elem�� t_GA[end]�� ����
	return end; // end ��ȯ
}
template<typename K, typename V>
void CompleteBinaryTree<K, V>::removeCBTEnd()
{
	end--; // end�� 1��ŭ ����
	TA_Entry<K, V>::num_elements--; // num_elementsfmf 1��ŭ����
}
#endif
