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
	ThreadStatusMonitor* pThrdMon; // �������� �� �ʱ�ȭ

	pThrdParam = (ThreadParam_Event*)pParam; // pParam����ü�� �����͸� pThrdParam�� ����
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	targetEventGen = pThrdParam->targetEventGen; // pThrdParam����ü����� ������ �����ߴ� ������ ����

	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen) // event_gen_count�� targetEventGen�� �������� 
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break; // *pThrdMon->pFlagThreadTerminate�� TERMINATE�̸� �ݺ��� ������
			else
			{ // �׷��� �ʴٸ� SLEEP �� �ݺ��� ó������ ���ư���
				Sleep(500);
				continue;
			}
		}
		event_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr; // �̺�Ʈ no ����
		event_priority = targetEventGen - event_gen_count - 1; // �̺�Ʈ �켱���� ����
		event.setEventNo(event_no);
		event.setEventPri(event_priority);
		event.setEventGenAddr(myAddr);
		event.setEventHandlerAddr(-1);
		QueryPerformanceCounter(&t_gen);
		event.setEventGenTime(t_gen);
		event.setEventStatus(GENERATED);
		entry_event.setKey(event.getEventPri());
		entry_event.setValue(event); // �����ߴ� �������� �̺�Ʈ ����ü �����͸���� ������ ����

		while (pPriQ_Event->insert(entry_event) == NULL) // pPriQ_Event�� entry_event�� ����
		{
			Sleep(500);
		}

		EnterCriticalSection(pThrdParam->pCS_thrd_mon); // ����͸� �Ӱ豸�� ����
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = event; // 
		pThrdMon->numEventGenerated++; // numEventGenerated�� 1��ŭ ����
		pThrdMon->totalEventGenerated++; // totalEventGenerated�� 1��ŭ ����
		// pThrdMon�� ������ �����ϴµ��� �ٸ���������� pThrdMon�� ���������������ʵ�����
		LeaveCriticalSection(pThrdParam->pCS_thrd_mon); // ����͸� �Ӱ豸�� �����
		event_gen_count++; // event_gen_count�� 1��ŭ ����
		Sleep(300);
	}
	_endthreadex(myExitCode); // ������ ����
	return 0;
}
