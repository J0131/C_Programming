/* Event.h */
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <thread>
#include <process.h>
using namespace std;
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
#define MAX_EVENT_PRIORITY 100
#define NUM_EVENT_GENERATORS 10
class Event
{
	friend ostream& operator<<(ostream& fout, const Event& e);
public:
	Event(); // 기본생성자
	Event(int event_id, int event_pri, int srcAddr); // 생성자
	void printEvent_proc();
	void setEventHandlerAddr(int evtHndlerAddr) { event_handler_addr = evtHndlerAddr; }
	void setEventGenAddr(int genAddr) { event_gen_addr = genAddr; }
	void setEventNo(int evtNo) { event_no = evtNo; }
	void setEventPri(int pri) { event_pri = pri; }
	void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; }
	void setEventGenTime(LARGE_INTEGER t_gen) { t_event_gen = t_gen; } // 생성시간 설정
	void setEventProcTime(LARGE_INTEGER t_proc) { t_event_proc = t_proc; } // 처리시간 설정
	LARGE_INTEGER getEventGenTime() { return t_event_gen; } // 생성시간 읽어오기
	LARGE_INTEGER getEventProcTime() { return t_event_proc; } // 처리시간 읽어오기
	void setEventElaspsedTime(double t_elapsed_ms) { t_elapsed_time_ms = t_elapsed_ms; } // 경과시간 설정
	double getEventElapsedTime() { return t_elapsed_time_ms; } // 경과시간 읽어오기
	int getEventPri() { return event_pri; }
	int getEventNo() { return event_no; }
	bool operator>(Event& e) { return (event_pri > e.event_pri); }
	bool operator<(Event& e) { return (event_pri < e.event_pri); }
private:
	int event_no;
	int event_gen_addr;
	int event_handler_addr;
	int event_pri; // 우선순위
	LARGE_INTEGER t_event_gen; // 생성시간
	LARGE_INTEGER t_event_proc; // 처리시간
	double t_elapsed_time_ms; // 경과시간 
	EventStatus eventStatus; 
};
Event* genRandEvent(int evt_no);
unsigned __stdcall Thread_EventGenerator(LPVOID pParam);
unsigned __stdcall Thread_EventHandler(LPVOID pParam);


