/****************************************
* 파일목적 : 템플릿 Priority기반의 큐를 통한 이벤트처리 프로그램  
* 작성자 : 최범준
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
	LARGE_INTEGER freq,start,end; // 64비트 정수형 변수선언
	ofstream fout; // 파일 출력스트림
	string tName = "";
	char tmp[10];
	int priority = -1;
	int current_top_priority;
	int duration = 0;
	int size;
	int* pE;
	QueryPerformanceFrequency(&freq); // 주파수 계산하여 freq에 저장
	fout.open("output.txt"); // 출력파일 지정
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
	}; // 이벤트 배열 events를 다음과 같이 선언
	HeapPrioQueue<int, Event*> HeapPriQ_Event(INITIAL_CBT_CAPA, string("Event_Heap_Priority_Queue")); // HeapPrioQueue<int, Event*>형의 HeapPriQ_Event선언
	Event* pEv; // Event*형의 pEv선언
	T_Entry<int, Event*> entry_event, * pEntry_Event; // T_Entry<int, Event*>형의 entry_event와 *pEntry_Event선언
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		entry_event.setKey(events[i].getEventPri()); // key를 events[i].getEventPri()로 설정
		entry_event.setValue(&events[i]); // value를 &events[i]로 설정
		HeapPriQ_Event.insert(entry_event); // HeapPriQ_Event에 entry_event를 삽입
		fout << "Insert " << events[i];
		fout << " ==> Size of Heap Priority Queue : " << setw(3) << HeapPriQ_Event.size() << endl;
	}
	fout << "Final status of insertions : " << endl;
	HeapPriQ_Event.fprintCBT_byLevel(fout); // HeapPriQ_Event를 레벨에 따라 출력
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		fout << "\nCurrent top priority in Heap Priority Queue : ";
		pEntry_Event = HeapPriQ_Event.getHeapMin(); // HeapPriQ_Event의 루트노드에 있는 데이터를 pEntry_Event에저장
		fout << *pEntry_Event << endl;
		QueryPerformanceCounter(&start); // 클럭수를 측정하여 start에 저장
		pEntry_Event = HeapPriQ_Event.removeHeapMin(); // HeapPriQ_Event의 루트노드에 있는 데이터를 제거하여 pEntry_Event에 저장
		QueryPerformanceCounter(&end); // 클럭수를 측정하여 end에 저장
		__int64 elasped=end.QuadPart-start.QuadPart; // 64비트 정수형으로 선언한 elasped에 end-start값을 저장
		double time = (double)elasped / (double)freq.QuadPart; // elasped를 freq로 나눈값을 time에 저장
		fout << "Remove " << *pEntry_Event;
		fout << " ==> " << HeapPriQ_Event.size() << " elements remains." << "  (Processed time : " << time*1000 << " ms )" << endl;
		HeapPriQ_Event.fprintCBT_byLevel(fout); // // HeapPriQ_Event를 레벨에 따라 출력
		fout << endl;
	}
	fout.close();
} 