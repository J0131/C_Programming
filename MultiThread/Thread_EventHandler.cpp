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
	ThreadStatusMonitor* pThrdMon; // �������� �� �ʱ�ȭ

	pThrdParam = (ThreadParam_Event*)pParam; // pParam����ü�� �����͸� pThrdParam�� ����
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	QP_freq = pThrdParam->QP_freq;
	targetEventGen = pThrdParam->targetEventGen; // pThrdParam����ü����� ������ �����ߴ� ������ ����

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break; // *pThrdMon->pFlagThreadTerminate�� TERMINATE�̸� �ݺ��� ������
		if (!pPriQ_Event->isEmpty()) // pPriQ_Event�ȿ� �̺�Ʈ�� �ִٸ� 
		{
			pEntry = pPriQ_Event->removeHeapMin(); // ��Ʈ����� �����͸� �����Ͽ� pEntry�� ����
			event = pEntry->getValue(); // pEntry�� value�� event�� ����
			EnterCriticalSection(pThrdParam->pCS_thrd_mon); // ����͸� �Ӱ豸�� ����
			event.setEventHandlerAddr(myAddr); // event�� �ּҸ� ����
			QueryPerformanceCounter(&t_proc); // ���� clock�� �����Ͽ� t_proc�� ����
			event.setEventProcTime(t_proc); // event�� ó���Ƚð��� t_proc���� ����
			t_gen = event.getEventGenTime(); // event�� �����Ƚð��� �ҷ��� t_gen�� ����
			t_diff = t_proc.QuadPart - t_gen.QuadPart; // ó���������� clock���� ������������ clock�� ���̸� t_diff�� ����
			elapsed_time = ((double)t_diff / QP_freq.QuadPart); // t_diff�� ���ļ��� ������ elapsed time�� ����
			event.setEventElaspsedTime(elapsed_time * 1000); // ms������ �����ϱ����� elapsed time*1000�� �̺�Ʈó�� ����ð����� ����
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event; //
			pThrdMon->numEventProcessed++; // numEventProcessed 1��ŭ ����
			pThrdMon->totalEventProcessed++; // totalEventProcessed 1��ŭ ����
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon); // �Ӱ豸�� �����
		}
		Sleep(500);
	}
	_endthreadex(myExitCode); // ������ ����

	return 0;
}