#include <Windows.h>
#include "Multi_thread.h"
#include "HeapPrioQ.h"
#include "Event.h"
#include "SimParam.h"

#define myExitCode 0

unsigned __stdcall Thread_EventGenerator(LPVOID pParam)
{
	ThreadParam_Event* pThrdParam; //
	HeapPrioQueue<int, Event>* pPriQ_Event;
	int myRole;
	THREAD_FLAG* pFlagThreadTerminate;
	int maxRound;
	T_Entry <int, Event>* pEntry, entry_event;
	Event event, * pEvent;
	int event_no = 0;
	int event_priority = 0;
	int event_gen_count = 0;
	int targetEventGen;
	int myAddr = -1;
	int event_handler_addr;
	LARGE_INTEGER QP_freq, t_gen;
	ThreadStatusMonitor* pThrdMon; // 변수선언 및 초기화

	pThrdParam = (ThreadParam_Event*)pParam; // pParam구조체의 데이터를 pThrdParam에 저장
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	targetEventGen = pThrdParam->targetEventGen; // pThrdParam구조체멤버의 값들을 선언했던 변수에 저장

	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen) // event_gen_count가 targetEventGen와 같아지면 
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break; // *pThrdMon->pFlagThreadTerminate가 TERMINATE이면 반복문 나가기
			else
			{ // 그렇지 않다면 SLEEP 후 반복문 처음으로 돌아가기
				Sleep(500);
				continue;
			}
		}
		event_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr; // 이벤트 no 설정
		event_priority = targetEventGen - event_gen_count - 1; // 이벤트 우선순위 설정
		event.setEventNo(event_no);
		event.setEventPri(event_priority);
		event.setEventGenAddr(myAddr);
		event.setEventHandlerAddr(-1);
		QueryPerformanceCounter(&t_gen);
		event.setEventGenTime(t_gen);
		event.setEventStatus(GENERATED);
		entry_event.setKey(event.getEventPri());
		entry_event.setValue(event); // 선언했던 변수들을 이벤트 구조체 데이터멤버의 값으로 설정

		while (pPriQ_Event->insert(entry_event) == NULL) // pPriQ_Event에 entry_event를 삽입
		{
			Sleep(500);
		}

		EnterCriticalSection(pThrdParam->pCS_thrd_mon); // 모니터링 임계구역 진입
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = event; // 
		pThrdMon->numEventGenerated++; // numEventGenerated를 1만큼 증가
		pThrdMon->totalEventGenerated++; // totalEventGenerated를 1만큼 증가
		// pThrdMon의 정보를 수정하는동안 다른스레드들이 pThrdMon의 정보를수정하지않도록함
		LeaveCriticalSection(pThrdParam->pCS_thrd_mon); // 모니터링 임계구역 벗어나기
		event_gen_count++; // event_gen_count를 1만큼 증가
		Sleep(300);
	}
	_endthreadex(myExitCode); // 스레드 종료
	return 0;
}
