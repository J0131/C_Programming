#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <process.h>
#include <string> 
#include "HeapPrioQ.h"
#include "Event.h"
#include "SimParam.h"
using namespace std;
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };
typedef struct ThreadStatusMonitor
{
	int numEventGenerated;
	int numEventProcessed;
	int totalEventGenerated;
	int totalEventProcessed;
	Event eventGenerated[TOTAL_NUM_EVENTS]; // used for monitoring only
	Event eventProcessed[TOTAL_NUM_EVENTS]; // used for monitoring only
	THREAD_FLAG* pFlagThreadTerminate;
}ThreadStatusMonitor;
typedef struct ThreadParam
{
	CRITICAL_SECTION* pCS_main;
	CRITICAL_SECTION* pCS_thrd_mon;
	HeapPrioQueue<int, Event>* pPriQ_Event;
	FILE* fout;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;
	LARGE_INTEGER QP_freq;
	ThreadStatusMonitor* pThrdMon;
}ThreadParam_Event;
#endif
