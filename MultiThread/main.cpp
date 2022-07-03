/*******************************************
* ���ϸ��� : ��������Ʈ������� �켱����ť�� �̺�Ʈ�� ��Ƽ�����带���� ���������� ó���ϴ� ���α׷�
* �ۼ��� : �ֹ���
* final update : 2020.11.05
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Multi_thread.h"
#include "HeapPrioQ.h"
#include "Event.h"
#include "ConsoleDisplay.h"
#include "SimParam.h"
#include <time.h>
#include <conio.h>

void main()
{
	ofstream fout;
	LARGE_INTEGER QP_freq, t_before, t_after; // �ð��� ������ ���� 
	LONGLONG t_diff; // �ð����̸� ������ ����
	double elapsed_time, min_elapsed_time, max_elapsed_time; // ����ð��� ������ ����
	double avg_elapsed_time, total_elapsed_time; // ���, �� ����ð��� ������ ����
	HeapPrioQueue<int, Event> heapPriQ_Event(30, string("HeapPriorityQueue_Event")); // HeapPrioQueue<int, Event>�� ���� ����
	Event* pEvent, * pEv_min_elapsed_time=0, * pEv_max_elapsed_time=0; // Event �������� ��������
	int myAddr = 0;
	int pkt_event_handler_addr, eventPriority;
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr; // �����忡 �μ��� ������ ����ü��������
	HANDLE hTrd_EventGenerator, hTrd_EventHandler; //
	CRITICAL_SECTION cs_main; // �Ӱ豸�� ������
	CRITICAL_SECTION cs_thrd_mon; // �Ӱ豸�� ������
	ThreadStatusMonitor thrdMon; // ThreadStatusMonitor �� ����ü���� ����
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventGenerated, numEventProcessed;
	int num_events_in_PrioQ;
	Event eventProcessed[TOTAL_NUM_EVENTS];

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output .txt file for results !!" << endl;
		exit;
	}

	InitializeCriticalSection(&cs_main); // �Ӱ豸�� ����
	InitializeCriticalSection(&cs_thrd_mon); // �Ӱ豸�� ����
	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&QP_freq); // ���ļ��� �����Ͽ� QP_freq�� ����
	srand(time(NULL)); // �õ� �ʱ�ȭ

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0; // thrdMon����ü �����͸���ʱ�ȭ
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].setEventNo(-1);
		thrdMon.eventProcessed[ev].setEventPri(-1); // thrdMon����ü �����͸�� �ʱ�ȭ
	}
	thrdMon.numEventProcessed = 0; // thrdMon����ü �����͸�� �ʱ�ȭ
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1;
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.pThrdMon = &thrdMon; // thrdParam_EventHndlr ����ü �����͸�� �ʱ�ȭ

	hTrd_EventHandler = (HANDLE)_beginthreadex(NULL, 0, Thread_EventHandler, &thrdParam_EventHndlr, 0, NULL); // �̺�Ʈ ó�� ������ ����
	EnterCriticalSection(&cs_main); // ��� �Ӱ豸�� ����
	printf("Thread_EvenHndlr is created and activated...\n");
	LeaveCriticalSection(&cs_main); // ��� �Ӱ豸�� ���
    
	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0;
	thrdParam_EventGen.pCS_main = &cs_main;
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.QP_freq = QP_freq;
	thrdParam_EventGen.pThrdMon = &thrdMon; // thrdParam_EventGen ����ü �����͸�� �ʱ�ȭ

	hTrd_EventGenerator = (HANDLE)_beginthreadex(NULL, 0, Thread_EventGenerator, &thrdParam_EventGen, 0, NULL); // �̺�Ʈ ���� ������ ����
	EnterCriticalSection(&cs_main); // ��� �Ӱ豸�� ����
	printf("Thread_EventGen is created and activated ... \n");
	LeaveCriticalSection(&cs_main); // ��� �Ӱ豸�� ���

	for (int round = 0; round < MAX_ROUND; round++)
	{
		EnterCriticalSection(&cs_main); // ��� �Ӱ豸�� ����
		system("cls"); // �ܼ�ȭ�� Ŭ����
		gotoxy(consHndlr, 0, 0); // �ܼ�ȭ���� 0,0 �������� �̵�
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n",round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		// ���� ���¸� ���
		printf("\n*****************************\n");
		numEventGenerated = thrdMon.numEventGenerated; // thrdMon.numEventGenerated�� numEventGenerated������
		printf("Events generated (current total = %2d)\n ", numEventGenerated); // ���� ������ �̺�Ʈ�� ���
		count = 0;
		for (int ev = 0; ev < numEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev]; // thrdMon.eventGenerated[ev]�� pEvent�� ����
			if (pEvent != NULL)
			{
				cout << *pEvent << " "; // *pEvent�� ���
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
		}
		printf("\n");

		printf("\n*****************************\n");
		num_events_in_PrioQ = heapPriQ_Event.size(); // heapPriQ_Event.size()�� num_events_in_PrioQ�� ����
		printf("Events currently in Priority_Queue (%d) : \n ", num_events_in_PrioQ); // �켱����ť�� ����� �̺�Ʈ ������ ���
		heapPriQ_Event.fprint(cout); // �켱����ť�� ����� �̺�Ʈ�� ��� ���

		printf("\n\n*****************************\n");
		numEventProcessed = thrdMon.totalEventProcessed; // thrdMon.totalEventProcessed�� numEventProcessed�� ����
		printf("Events processed (current total = %d): \n ", numEventProcessed); // ó���� �̺�FƮ ������ ����
		count = 0;
		total_elapsed_time = 0.0; // total_elapsed_time �ʱ�ȭ
		 
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev]; // thrdMon.eventProcessed[ev]�� pEvent�� ����
			if (pEvent != NULL)
			{
				pEvent->printEvent_proc(); // pEvent ���
				if (((ev + 1) % 4) == 0)
					printf("\n ");
			}
			if (ev == 0)
			{
				min_elapsed_time = max_elapsed_time = total_elapsed_time= pEvent->getEventElapsedTime(); // ms
				pEv_min_elapsed_time= pEv_max_elapsed_time = pEvent;
			}
			else
			{
				if (min_elapsed_time > pEvent->getEventElapsedTime())
				{
					min_elapsed_time = pEvent->getEventElapsedTime(); // ms
					pEv_min_elapsed_time = pEvent;
				} // �ּڰ� ����
				if (max_elapsed_time < pEvent->getEventElapsedTime())
				{
					max_elapsed_time = pEvent->getEventElapsedTime(); // ms
					pEv_max_elapsed_time = pEvent;
				} // �ִ� ����
				total_elapsed_time += pEvent->getEventElapsedTime();
			}
		} //end for showing eventProcessed
		printf("\n\n");
		if (numEventProcessed > 0) // ó���� �̺�Ʈ�� 0���� Ŭ��
		{
			printf("min_elapsed_time = %8.2lf[ms]; ", min_elapsed_time); // �ּ� ����ð� ���
			cout << *pEv_min_elapsed_time << endl; // ����ð��� �ּ��� �̺�Ʈ�� ���
			printf("max_elapsed_time = %8.2lf[ms]; ", max_elapsed_time); // �ִ� ����ð� ���
			cout << *pEv_max_elapsed_time << endl; // ����ð��� �ִ��� �̺�Ʈ�� ���
			avg_elapsed_time = total_elapsed_time / numEventProcessed; // ��� ����ð��� ���
			printf("avg_elapsed_time = %8.2lf[ms]; \n", avg_elapsed_time);
		}

		if (numEventProcessed >= TOTAL_NUM_EVENTS) // ó���� �̺�Ʈ�� �� �̺�Ʈ�� �������� 
		{
			eventThreadFlag = TERMINATE; // eventThreadFlag �� TERMINATE�� ����
			break;
		} //
		LeaveCriticalSection(&cs_main); // �Ӱ豸�� ����������
		Sleep(100);
	} //
	DWORD nExitCode = NULL; // ���� �ڵ� ����
	
	WaitForSingleObject(hTrd_EventGenerator, INFINITE); // �̺�Ʈ ���������尡 ����ɶ����� ���������� ���
	EnterCriticalSection(&cs_main);
	printf("Thread_EventGenerator is terminated !! \n");
	LeaveCriticalSection(&cs_main);
	GetExitCodeThread(hTrd_EventGenerator, &nExitCode);
	CloseHandle(hTrd_EventGenerator);

	WaitForSingleObject(hTrd_EventHandler, INFINITE); // �̺�Ʈ ó�������尡 ����ɶ����� ���������� ���
	EnterCriticalSection(&cs_main);
	printf("Thread_EventHandler is terminated !! \n");
	LeaveCriticalSection(&cs_main);
	GetExitCodeThread(hTrd_EventHandler, &nExitCode);
	CloseHandle(hTrd_EventHandler);

	fout.close();

	printf("Hit any key to terminate : ");
	_getch();
}   

