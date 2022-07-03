#ifndef T_ARRAY_H
#define T_ARRAY_H
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
enum SortingDirection { INCREASING, DECREASING };
template<typename K>
class T_Array
{
public:
	T_Array(int new_capacity, string nm);//생성자
	~T_Array(); // 소멸자
	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return name; }
	void reserve(int new_capacity);
	void insert(int i, K element);
	void remove(int i);
	K& at(int i);
	void set(int i, K& element);
	void shuffle();
	int sequential_search(K search_key); // 순차탐색
	int binary_search(K search_key); // 이진탐색
	void fprint(ofstream& fout, int elements_per_line); // 출력
	void fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines); // 일부분 출력
	bool isValidIndex(int i); // 값의 범위 확인
	K& operator[](int index) { return t_GA[index]; } // 배열의 원소 반환

protected:
	K* t_GA;
	int num_elements;
	int capacity;
	string name;
};

template<typename K>
T_Array<K>::T_Array(int new_capacity, string nm) // 생성자
{
	capacity = new_capacity;
	t_GA = (K*) new K[capacity];
	if (t_GA == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
		exit;
	}
	num_elements = 0;
	name = nm;
}
template<typename K>
T_Array<K>::~T_Array()
{
	if (t_GA != NULL)
		delete[] t_GA;
}
template<typename K>
void T_Array<K>::reserve(int new_capacity) // 크기 늘리기
{
	if (capacity >= new_capacity)
		return; // capacity가 더 크다면 종료
	K* t_newGA = (K*) new K[new_capacity];
	if (t_newGA == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
		exit;
	}
	cout << this->getName() << " expands capacity to " << setw(3) << new_capacity << endl;
	for (int i = 0; i < num_elements; i++)
		t_newGA[i] = t_GA[i];
	delete[] t_GA;
	t_GA = t_newGA;
	capacity = new_capacity; // 새로운 크기의 배열을 동적으로생성하여 t_array로 저장
}
template<typename K>
void T_Array<K> ::insert(int i, K element)
{
	if (num_elements >= capacity) // 가득차있는지 확인
	{
		int new_capa;
		new_capa = ((2 * capacity) > 1) ? 2 * capacity : 1;
		reserve(new_capa);
	}
	if (isValidIndex(i))
	{
		for (int j = num_elements - 1; j >= i; j--)
			t_GA[j + 1] = t_GA[j];
		t_GA[i] = element; // t_array[i]에 element을 삽입
		num_elements++;
	}
}
template<typename K>
void T_Array<K> ::remove(int i)
{
	if (isValidIndex(i))
	{
		for (int j = i + 1; j < num_elements; j++)
			t_GA[j - 1] = t_GA[j]; // 배열원소들을 하나씩 내리기
		num_elements--;
	}
	if (num_elements < (capacity / 2))
	{
		int new_capacity = capacity / 2;
		K* t_newGA = (K*) new K[new_capacity];
		if (t_newGA == NULL)
		{
			return;
		}
		cout << this->getName() << " reduces capacity to " << setw(3) << new_capacity << endl;
		for (int i = 0; i < num_elements; i++)
			t_newGA[i] = t_GA[i];
		delete[] t_GA;
		t_GA = t_newGA;
		capacity = new_capacity;
	}
}
template<typename K>
K& T_Array<K>::at(int i)
{
	if (isValidIndex(i))
	{
		return t_GA[i];
	} // 해당인덱스의 원소반환
}
template<typename K>
void T_Array<K> ::set(int i, K& element)
{
	if (isValidIndex(i))
	{
		t_GA[i] = element;
	} // element를 i번째 원소로 삽입
}
template<typename K>
void T_Array<K> ::shuffle()
{
	srand(time(0));
	int index1, index2;
	int rand_1, rand_2;
	K temp;
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
} // 섞기
template<typename K>
bool T_Array<K> ::isValidIndex(int index)
{
	if ((index < 0) || (index > num_elements))
		return false;
	else
		return true;
} // 범위가 맞는지 확인
template<typename K>
int T_Array<K> ::sequential_search(K search_key)
{
	int index;
	for (int index = 0; index < num_elements; index++)
	{
		if (t_GA[index] == search_key) // 일치한다면 인덱스 반환
			return index;
	}
	return -1;
}
template<typename K>
int T_Array<K> ::binary_search(K search_key)
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
		if (t_GA[mid] == search_key) // 일치한다면 mid반환
			return mid;
		else if (t_GA[mid] > search_key) // 
			high = mid - 1;
		else
			low = mid + 1;
		loop++;
	}
	return -1;
}

template<typename K>
void T_Array<K> ::fprint(ofstream& fout, int elements_per_line)
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
} // 출력
template<typename K>
void T_Array<K> ::fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines)
{
	string T_type;
	int last_block_start;
	int count = 0;
	T_type = typeid(K).name();
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
} // 일부분만 출력
#endif

