/*******************************************
* 파일목적 : 완전이진트리기반의 우선순위큐의 이벤트를 멀티스레드를통해 병렬적으로 처리하는 프로그램
* 작성자 : 최범준
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
	LARGE_INTEGER QP_freq, t_before, t_after; // 시간을 저장할 변수 
	LONGLONG t_diff; // 시간차이를 저장할 변수
	double elapsed_time, min_elapsed_time, max_elapsed_time; // 경과시간을 저장할 변수
	double avg_elapsed_time, total_elapsed_time; // 평균, 총 경과시간을 저장할 변수
	HeapPrioQueue<int, Event> heapPriQ_Event(30, string("HeapPriorityQueue_Event")); // HeapPrioQueue<int, Event>형 변수 선언
	Event* pEvent, * pEv_min_elapsed_time=0, * pEv_max_elapsed_time=0; // Event 포인터형 변수선언
	int myAddr = 0;
	int pkt_event_handler_addr, eventPriority;
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr; // 스레드에 인수를 전달할 구조체변수선언
	HANDLE hTrd_EventGenerator, hTrd_EventHandler; //
	CRITICAL_SECTION cs_main; // 임계구역 세마포
	CRITICAL_SECTION cs_thrd_mon; // 임계구역 세마포
	ThreadStatusMonitor thrdMon; // ThreadStatusMonitor 형 구조체변수 선언
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

	InitializeCriticalSection(&cs_main); // 임계구역 생성
	InitializeCriticalSection(&cs_thrd_mon); // 임계구역 생성
	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&QP_freq); // 주파수를 측정하여 QP_freq에 저장
	srand(time(NULL)); // 시드 초기화

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0; // thrdMon구조체 데이터멤버초기화
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].setEventNo(-1);
		thrdMon.eventProcessed[ev].setEventPri(-1); // thrdMon구조체 데이터멤버 초기화
	}
	thrdMon.numEventProcessed = 0; // thrdMon구조체 데이터멤버 초기화
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1;
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.pThrdMon = &thrdMon; // thrdParam_EventHndlr 구조체 데이터멤버 초기화

	hTrd_EventHandler = (HANDLE)_beginthreadex(NULL, 0, Thread_EventHandler, &thrdParam_EventHndlr, 0, NULL); // 이벤트 처리 스레드 생성
	EnterCriticalSection(&cs_main); // 출력 임계구역 진입
	printf("Thread_EvenHndlr is created and activated...\n");
	LeaveCriticalSection(&cs_main); // 출력 임계구역 벗어남
    
	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0;
	thrdParam_EventGen.pCS_main = &cs_main;
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.QP_freq = QP_freq;
	thrdParam_EventGen.pThrdMon = &thrdMon; // thrdParam_EventGen 구조체 데이터멤버 초기화

	hTrd_EventGenerator = (HANDLE)_beginthreadex(NULL, 0, Thread_EventGenerator, &thrdParam_EventGen, 0, NULL); // 이벤트 생성 스레드 생성
	EnterCriticalSection(&cs_main); // 출력 임계구역 진입
	printf("Thread_EventGen is created and activated ... \n");
	LeaveCriticalSection(&cs_main); // 출력 임계구역 벗어남

	for (int round = 0; round < MAX_ROUND; round++)
	{
		EnterCriticalSection(&cs_main); // 출력 임계구역 진입
		system("cls"); // 콘솔화면 클리어
		gotoxy(consHndlr, 0, 0); // 콘솔화면의 0,0 지점으로 이동
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n",round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		// 현재 상태를 출력
		printf("\n*****************************\n");
		numEventGenerated = thrdMon.numEventGenerated; // thrdMon.numEventGenerated를 numEventGenerated에저장
		printf("Events generated (current total = %2d)\n ", numEventGenerated); // 현재 생성된 이벤트를 출력
		count = 0;
		for (int ev = 0; ev < numEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev]; // thrdMon.eventGenerated[ev]를 pEvent에 저장
			if (pEvent != NULL)
			{
				cout << *pEvent << " "; // *pEvent를 출력
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
		}
		printf("\n");

		printf("\n*****************************\n");
		num_events_in_PrioQ = heapPriQ_Event.size(); // heapPriQ_Event.size()를 num_events_in_PrioQ에 저장
		printf("Events currently in Priority_Queue (%d) : \n ", num_events_in_PrioQ); // 우선순위큐에 저장된 이벤트 갯수를 출력
		heapPriQ_Event.fprint(cout); // 우선순위큐에 저장된 이벤트를 모두 출력

		printf("\n\n*****************************\n");
		numEventProcessed = thrdMon.totalEventProcessed; // thrdMon.totalEventProcessed를 numEventProcessed에 저장
		printf("Events processed (current total = %d): \n ", numEventProcessed); // 처리된 이벤F트 갯수를 저장
		count = 0;
		total_elapsed_time = 0.0; // total_elapsed_time 초기화
		 
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev]; // thrdMon.eventProcessed[ev]를 pEvent에 저장
			if (pEvent != NULL)
			{
				pEvent->printEvent_proc(); // pEvent 출력
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
				} // 최솟값 결정
				if (max_elapsed_time < pEvent->getEventElapsedTime())
				{
					max_elapsed_time = pEvent->getEventElapsedTime(); // ms
					pEv_max_elapsed_time = pEvent;
				} // 최댓값 결정
				total_elapsed_time += pEvent->getEventElapsedTime();
			}
		} //end for showing eventProcessed
		printf("\n\n");
		if (numEventProcessed > 0) // 처리된 이벤트가 0보다 클때
		{
			printf("min_elapsed_time = %8.2lf[ms]; ", min_elapsed_time); // 최소 경과시간 출력
			cout << *pEv_min_elapsed_time << endl; // 경과시간이 최소인 이벤트를 출력
			printf("max_elapsed_time = %8.2lf[ms]; ", max_elapsed_time); // 최대 경과시간 출력
			cout << *pEv_max_elapsed_time << endl; // 경과시간이 최대인 이벤트를 출력
			avg_elapsed_time = total_elapsed_time / numEventProcessed; // 평균 경과시간을 계산
			printf("avg_elapsed_time = %8.2lf[ms]; \n", avg_elapsed_time);
		}

		if (numEventProcessed >= TOTAL_NUM_EVENTS) // 처리된 이벤트가 총 이벤트와 같아지면 
		{
			eventThreadFlag = TERMINATE; // eventThreadFlag 를 TERMINATE로 설정
			break;
		} //
		LeaveCriticalSection(&cs_main); // 임계구역 빠져나오기
		Sleep(100);
	} //
	DWORD nExitCode = NULL; // 종료 코드 설정
	
	WaitForSingleObject(hTrd_EventGenerator, INFINITE); // 이벤트 생성스레드가 종료될때까지 무한정으로 대기
	EnterCriticalSection(&cs_main);
	printf("Thread_EventGenerator is terminated !! \n");
	LeaveCriticalSection(&cs_main);
	GetExitCodeThread(hTrd_EventGenerator, &nExitCode);
	CloseHandle(hTrd_EventGenerator);

	WaitForSingleObject(hTrd_EventHandler, INFINITE); // 이벤트 처리스레드가 종료될때까지 무한정으로 대기
	EnterCriticalSection(&cs_main);
	printf("Thread_EventHandler is terminated !! \n");
	LeaveCriticalSection(&cs_main);
	GetExitCodeThread(hTrd_EventHandler, &nExitCode);
	CloseHandle(hTrd_EventHandler);

	fout.close();

	printf("Hit any key to terminate : ");
	_getch();
}   

