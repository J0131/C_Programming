#ifndef TA_ENTRY_H
#define TA_ENTRY_H
#include <fstream>
#include <iostream>
#include <iomanip>
#include "T_Entry.h"
using namespace std;
enum SortingDirection { INCREASING, DECREASING };
template<typename K, typename V>
class TA_Entry
{
public:
	TA_Entry(int new_capacity, string nm);//������
	~TA_Entry(); // �Ҹ���
	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return name; }
	void reserve(int new_capacity);
	void insert(int i, T_Entry<K, V> element);
	void remove(int i);
	T_Entry<K, V>& at(int i);
	void set(int i, T_Entry<K, V>& element);
	T_Entry<K, V>& getMin();
	T_Entry<K, V>& getMax();
	void shuffle();
	int sequential_search(T_Entry<K, V> search_key); // ����Ž��
	int binary_search(T_Entry<K, V> search_key); // ����Ž��
	void selection_sort(SortingDirection sd); // ��������
	void quick_sort(SortingDirection sd); // ������
	int _partition(T_Entry<K, V>* array, int size, int left, int right, int pivotIndex, SortingDirection sortOrder); //
	void _quickSort(T_Entry<K, V>* array, int size, int left, int right, SortingDirection sortOrder);//
	void fprint(ofstream& fout, int elements_per_line); // ���
	void fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines); // �Ϻκ� ���
	bool isValidIndex(int i); // ���� ���� Ȯ��
	T_Entry<K, V>& operator[](int index) { return t_GA[index]; } // �迭�� ���� ��ȯ

protected:
	T_Entry<K, V>* t_GA;
	int num_elements;
	int capacity;
	string name;
};

template<typename K, typename V>
TA_Entry<K, V>::TA_Entry(int new_capacity, string nm) // ������
{
	capacity = new_capacity;
	t_GA = (T_Entry<K, V>*) new T_Entry<K, V>[capacity];
	if (t_GA == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
		exit;
	}
	num_elements = 0;
	name = nm;
}
template<typename K, typename V>
TA_Entry<K, V>::~TA_Entry()
{
	if (t_GA != NULL)
		delete[] t_GA;
}
template<typename K, typename V>
void TA_Entry<K, V>::reserve(int new_capacity) // ũ�� �ø���
{
	if (capacity >= new_capacity)
		return; // capacity�� �� ũ�ٸ� ����
	T_Entry<K, V>* t_newGA = (T_Entry<K, V>*) new T_Entry<K, V>[new_capacity];
	if (t_newGA == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
		exit;
	}
	cout << this->getName() << " expands capacity to " << setw(3)
		<< new_capacity << endl;
	for (int i = 0; i < num_elements; i++)
		t_newGA[i] = t_GA[i];
	delete[] t_GA;
	t_GA = t_newGA;
	capacity = new_capacity; // ���ο� ũ���� �迭�� �������λ����Ͽ� t_array�� ����
}
template<typename K, typename V>
void TA_Entry<K, V> ::insert(int i, T_Entry<K, V> element)
{
	if (num_elements >= capacity) // �������ִ��� Ȯ��
	{
		int new_capa;
		new_capa = ((2 * capacity) > 1) ? 2 * capacity : 1;
		reserve(new_capa);
	}
	if (isValidIndex(i))
	{
		for (int j = num_elements - 1; j >= i; j--)
			t_GA[j + 1] = t_GA[j];
		t_GA[i] = element; // t_array[i]�� element�� ����
		num_elements++;
	}
}
template<typename K, typename V>
void TA_Entry<K, V> ::remove(int i)
{
	if (isValidIndex(i))
	{
		for (int j = i + 1; j < num_elements; j++)
			t_GA[j - 1] = t_GA[j]; // �迭���ҵ��� �ϳ��� ������
		num_elements--;
	}
	if (num_elements < (capacity / 2))
	{
		int new_capacity = capacity / 2;
		T_Entry<K, V>* t_newGA = (T_Entry<K, V>*) new T_Entry<K, V>[new_capacity];
		if (t_newGA == NULL)
		{
			return;
		}
		cout << this->getName()
			<< " reduces capacity to " << setw(3)
			<< new_capacity << endl;
		for (int i = 0; i < num_elements; i++)
			t_newGA[i] = t_GA[i];
		delete[] t_GA;
		t_GA = t_newGA;
		capacity = new_capacity;
	}
}
template<typename K, typename V>
T_Entry<K, V>& TA_Entry<K, V>::at(int i)
{
	if (isValidIndex(i))
	{
		return t_GA[i];
	} // �ش��ε����� ���ҹ�ȯ
}
template<typename K, typename V>
void TA_Entry<K, V> ::set(int i, T_Entry<K, V>& element)
{
	if (isValidIndex(i))
	{
		t_GA[i] = element;
	} // element�� i��° ���ҷ� ����
}
template<typename K, typename V>
void TA_Entry<K, V> ::shuffle()
{
	srand(time(0));
	int index1, index2;
	int rand_1, rand_2;
	T_Entry<K, V> temp;
	for (int i = 0; i < num_elements; i++)
	{
		rand_1 = rand();
		rand_2 = rand();
		index1 = ((rand_1 << 15) | rand_2) % num_elements;
		rand_1 = rand();
		rand_2 = rand();
		index2 = ((rand_1 << 15) | rand_2) % num_elements;
		temp = t_GA[index1];
		t_GA[index1] = t_GA[index2];
		t_GA[index2] = temp;
	}
} // ����
template<typename K, typename V>
bool TA_Entry<K, V> ::isValidIndex(int index)
{
	if ((index < 0) || (index > num_elements))
		return false;
	else
		return true;
} // ������ �´��� Ȯ��
template<typename K, typename V>
int TA_Entry<K, V> ::sequential_search(T_Entry<K, V> search_key)
{
	int index;
	for (int index = 0; index < num_elements; index++)
	{
		if (t_GA[index] == search_key) // ��ġ�Ѵٸ� �ε��� ��ȯ
			return index;
	}
	return -1;
}
template<typename K, typename V>
int TA_Entry<K, V> ::binary_search(T_Entry<K, V> search_key)
{
	int low, mid, high;
	int loop = 1;
	low = 0;
	high = num_elements - 1;
	while (low <= high)
	{
		cout << setw(2) << loop << "-th loop: current search range [" << setw(3)
			<< low << ", " << setw(3) << high << "]" << endl;
		mid = (low + high) / 2;
		if (t_GA[mid] == search_key) // ��ġ�Ѵٸ� mid��ȯ
			return mid;
		else if (t_GA[mid] > search_key) // 
			high = mid - 1;
		else
			low = mid + 1;
		loop++;
	}
	return -1;
}
template<typename K, typename V>
void TA_Entry<K, V> ::selection_sort(SortingDirection sd)
{
	int index_min, index_max;
	T_Entry<K, V> minValue;
	T_Entry<K, V> maxValue;
	for (int i = 0; i < num_elements - 1; i++)
	{
		if (sd == INCREASING) // ��������
		{
			index_min = i;
			minValue = t_GA[i];
			for (int j = i + 1; j < num_elements; j++)
			{
				if (t_GA[j] < minValue) // ��
				{
					index_min = j;
					minValue = t_GA[j];
				}
			}
			if (index_min != i)
			{
				t_GA[index_min] = t_GA[i];
				t_GA[i] = minValue;
			}
		}
		else { // ��������
			index_max = i;
			maxValue = t_GA[i];
			for (int j = i + 1; j < num_elements; j++)
			{
				if (t_GA[j] > maxValue) // ��
				{
					index_max = j;
					maxValue = t_GA[j];
				}
			}
			if (index_max != i) //
			{
				t_GA[index_max] = t_GA[i];
				t_GA[i] = maxValue;
			}
		}
	}
}
template<typename K, typename V>
int TA_Entry<K, V> ::_partition(T_Entry<K, V>* array, int size, int left, int right, int pivotIndex, SortingDirection sortOrder)
{
	T_Entry<K, V> pivotValue, temp;
	int newPI; // ���ο� �Ǻ��ε���
	pivotValue = array[pivotIndex];
	array[pivotIndex] = array[right];
	array[right] = pivotValue; // right��ġ�� pivotValue�� ����
	newPI = left; // 
	for (int i = left; i <= (right - 1); i++)
	{
		if (sortOrder == INCREASING) // ��������
		{
			if (array[i] <= pivotValue) // ��
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;
				newPI = newPI + 1;
				// swap�� newPI+1
			}
		}
		else // ��������
		{
			if (array[i] >= pivotValue) // ��
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;
				newPI = newPI + 1;
				//swap�� newPI+1
			}
		}
	} // 
	temp = array[newPI];
	array[newPI] = array[right];
	array[right] = temp;
	return newPI;// swap
}

template<typename K, typename V>
void TA_Entry<K, V> ::_quickSort(T_Entry<K, V>* array, int size, int left, int right, SortingDirection sortOrder)
{
	int pI, newPI; // �Ǻ��ε���
	if (left >= right)
	{
		return;
	}
	else
	{// �Ǻ��ε����� ��������
		pI = (left + right) / 2;
	}
	newPI = _partition(array, size, left, right, pI, sortOrder);
	if (left < (newPI - 1)) // left < (newPI - 1) �϶�
	{
		_quickSort(array, size, left, newPI - 1, sortOrder);
		// ����Լ�
	}
	if ((newPI + 1) < right) // (newPI + 1) < right �϶�
	{
		_quickSort(array, size, newPI + 1, right, sortOrder);
		// ����Լ�
	}
}

template<typename K, typename V>
void TA_Entry<K, V> ::quick_sort(SortingDirection sd)
{
	int pI, newPI; // 
	_quickSort(this->t_array, num_elements, 0, num_elements - 1, sd);
}

template<typename K, typename V>
void TA_Entry<K, V> ::fprint(ofstream& fout, int elements_per_line)
{
	int count = 0;
	while (count < num_elements)
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			t_GA[count].fprint(fout);
			count++;
			if (count % elements_per_line == 0)
				fout << endl;
		}
	}
	fout << endl;
} // ���
template<typename K, typename V>
void TA_Entry<K, V> ::fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines)
{
	string T_type;
	int last_block_start;
	int count = 0;
	T_type = typeid(T_Entry<K, V>).name();
	for (int i = 0; i < num_sample_lines; i++)
	{
		for (int j = 0; j < elements_per_line; j++)
		{
			if (count >= num_elements)
			{
				fout << endl;
				return;
			}
			if ((T_type == string("int")) || (T_type == string("double")) || (T_type == string("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > ")))
				fout << setw(10) << t_GA[count];
			else
				fout << t_GA[count] << " ";
			count++;
		}
		fout << endl;
	}
} // �Ϻκи� ���
#endif