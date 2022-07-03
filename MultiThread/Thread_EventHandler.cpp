#include <Windows.h>
#include "Multi_thread.h"
#include "HeapPrioQ.h"
#include "Event.h"

#define myExitCode 0

unsigned __stdcall Thread_EventHandler(LPVOID pParam)
{
	ThreadParam_Event* pThrdParam; //
	HeapPrioQueue<int, Event>* pPriQ_Event;
	int myRole, myAddr, maxRound;
	THREAD_FLAG* pFlagThreadTerminate;
	T_Entry<int, Event>* pEntry;
	Event event, * pEvent, * pEventProc;
	int event_no = 0;
	int eventPriority = 0;
	int event_gen_count = 0;
	int num_pkt_processed = 0;
	int targetEventGen;
	LARGE_INTEGER QP_freq, t_gen, t_proc;
	LONGLONG t_diff;
	double elapsed_time;
	ThreadStatusMonitor* pThrdMon; // 변수선언 및 초기화

	pThrdParam = (ThreadParam_Event*)pParam; // pParam구조체의 데이터를 pThrdParam에 저장
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	QP_freq = pThrdParam->QP_freq;
	targetEventGen = pThrdParam->targetEventGen; // pThrdParam구조체멤버의 값들을 선언했던 변수에 저장

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break; // *pThrdMon->pFlagThreadTerminate가 TERMINATE이면 반복문 나가기
		if (!pPriQ_Event->isEmpty()) // pPriQ_Event안에 이벤트가 있다면 
		{
			pEntry = pPriQ_Event->removeHeapMin(); // 루트노드의 데이터를 제거하여 pEntry에 저장
			event = pEntry->getValue(); // pEntry의 value를 event로 저장
			EnterCriticalSection(pThrdParam->pCS_thrd_mon); // 모니터링 임계구역 진입
			event.setEventHandlerAddr(myAddr); // event의 주소를 설정
			QueryPerformanceCounter(&t_proc); // 현재 clock을 측정하여 t_proc에 저장
			event.setEventProcTime(t_proc); // event의 처리된시간을 t_proc으로 설정
			t_gen = event.getEventGenTime(); // event의 생성된시간을 불러와 t_gen에 저장
			t_diff = t_proc.QuadPart - t_gen.QuadPart; // 처리됬을때의 clock에서 생성됬을때의 clock의 차이를 t_diff에 저장
			elapsed_time = ((double)t_diff / QP_freq.QuadPart); // t_diff를 주파수로 나누어 elapsed time에 저장
			event.setEventElaspsedTime(elapsed_time * 1000); // ms단위로 설정하기위해 elapsed time*1000을 이벤트처리 경과시간으로 설정
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event; //
			pThrdMon->numEventProcessed++; // numEventProcessed 1만큼 증가
			pThrdMon->totalEventProcessed++; // totalEventProcessed 1만큼 증가
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon); // 임계구역 벗어나기
		}
		Sleep(500);
	}
	_endthreadex(myExitCode); // 스레드 종료

	return 0;
}