/****************************************
* ���ϸ��� : ���ø� Priority����� ť�� ���� �̺�Ʈó�� ���α׷�  
* �ۼ��� : �ֹ���
* final update : 2020.10.29
*****************************************/
#include <iostream>
#include <fstream>
#include "Event.h"
#include "HeapPrioQ.h"
#include <string>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
#define INITIAL_CBT_CAPA 100
#define TEST_HEAP_PRIO_Q_EVENT
#define NUM_EVENTS 15
void main()
{
	LARGE_INTEGER freq,start,end; // 64��Ʈ ������ ��������
	ofstream fout; // ���� ��½�Ʈ��
	string tName = "";
	char tmp[10];
	int priority = -1;
	int current_top_priority;
	int duration = 0;
	int size;
	int* pE;
	QueryPerformanceFrequency(&freq); // ���ļ� ����Ͽ� freq�� ����
	fout.open("output.txt"); // ������� ����
	if (fout.fail())
	{
		cout << "Fail to open output.txt file for results !!" << endl;
		exit;
	}
	Event events[NUM_EVENTS] =
	{
		Event(0, 14, "evt_00", 0), Event(1, 13, "evt_01", 1), Event(2, 12, "evt_02", 2),
		Event(3, 11, "evt_03", 3), Event(4, 10, "evt_04", 4), Event(5, 9, "evt_05", 5),
		Event(6, 8, "evt_06", 6), Event(7, 7, "evt_07", 7), Event(8, 6, "evt_08", 8),
		Event(9, 5, "evt_09", 9), Event(10, 4, "evt_10", 10), Event(11, 3, "evt_11", 11),
		Event(12, 2, "evt_12", 12), Event(13, 1, "evt_13", 13), Event(14, 0, "evt_14", 14)
	}; // �̺�Ʈ �迭 events�� ������ ���� ����
	HeapPrioQueue<int, Event*> HeapPriQ_Event(INITIAL_CBT_CAPA, string("Event_Heap_Priority_Queue")); // HeapPrioQueue<int, Event*>���� HeapPriQ_Event����
	Event* pEv; // Event*���� pEv����
	T_Entry<int, Event*> entry_event, * pEntry_Event; // T_Entry<int, Event*>���� entry_event�� *pEntry_Event����
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		entry_event.setKey(events[i].getEventPri()); // key�� events[i].getEventPri()�� ����
		entry_event.setValue(&events[i]); // value�� &events[i]�� ����
		HeapPriQ_Event.insert(entry_event); // HeapPriQ_Event�� entry_event�� ����
		fout << "Insert " << events[i];
		fout << " ==> Size of Heap Priority Queue : " << setw(3) << HeapPriQ_Event.size() << endl;
	}
	fout << "Final status of insertions : " << endl;
	HeapPriQ_Event.fprintCBT_byLevel(fout); // HeapPriQ_Event�� ������ ���� ���
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		fout << "\nCurrent top priority in Heap Priority Queue : ";
		pEntry_Event = HeapPriQ_Event.getHeapMin(); // HeapPriQ_Event�� ��Ʈ��忡 �ִ� �����͸� pEntry_Event������
		fout << *pEntry_Event << endl;
		QueryPerformanceCounter(&start); // Ŭ������ �����Ͽ� start�� ����
		pEntry_Event = HeapPriQ_Event.removeHeapMin(); // HeapPriQ_Event�� ��Ʈ��忡 �ִ� �����͸� �����Ͽ� pEntry_Event�� ����
		QueryPerformanceCounter(&end); // Ŭ������ �����Ͽ� end�� ����
		__int64 elasped=end.QuadPart-start.QuadPart; // 64��Ʈ ���������� ������ elasped�� end-start���� ����
		double time = (double)elasped / (double)freq.QuadPart; // elasped�� freq�� �������� time�� ����
		fout << "Remove " << *pEntry_Event;
		fout << " ==> " << HeapPriQ_Event.size() << " elements remains." << "  (Processed time : " << time*1000 << " ms )" << endl;
		HeapPriQ_Event.fprintCBT_byLevel(fout); // // HeapPriQ_Event�� ������ ���� ���
		fout << endl;
	}
	fout.close();
} 