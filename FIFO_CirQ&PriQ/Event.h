#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
#define SIZE_DESCRIPTION 2048
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED }; // 이벤트의 상태를 열겨형으로 나열
extern const char* strEventStatus[]; // 상태를 나타낼 문자열배열 선언

typedef struct
{
	int event_no;
	int event_gen_addr;
	int event_handler_addr;
	int event_pri; // 이벤트의 우선순위
	EventStatus eventStatus;
} Event;
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status); // 이벤트를 초기화하는 함수
void printEvent(Event* pEvt); // 이벤트를 화면에 출력하는 함수
void fprintEvent(FILE* fout, Event* pEvent); // 이벤트를 파일에 출력하는 함수
void printEventArray(Event* pEvent, int size, int items_per_line); // 이벤트배열을 출력하는 함수
Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri); // 이벤트를 하나 만들어 Event포인터형으로 반환해주는함수
#endif
