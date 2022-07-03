#include <stdio.h>
#include <stdlib.h>
#include "Event.h"
const char* strEventStatus[] = {"GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" }; // 이벤트의 상태를 나타나내는 문자열배열

void printEvent(Event* pEvent)
{
	char str_pri[6]; 
	printf("Ev(no:%3d, pri:%2d) ", pEvent->event_no, pEvent->event_pri); // 받아온 이벤트의 번호와 우선순위를 화면에 출력
}
void fprintEvent(FILE* fout, Event* pEvent)
{
	char str_pri[6];
	fprintf(fout, "Ev(no:%3d, pri:%2d) ", pEvent->event_no, pEvent->event_pri); // 받아온 이벤트의 번호와 우선순위를 파일에 출력
}
Event* genEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri)
{
	pEv = (Event*)calloc(1, sizeof(Event)); // 받아온 이벤트 pEv를 동적할당
	if (pEv == NULL)
		return NULL;
	initEvent(pEv, ev_gen_ID, ev_no, ev_pri, -1, GENERATED); // 이벤트 pEv를 받아온정보로 초기화한다
	return pEv; // pEv 반환
}
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status)
{
	pEv->event_gen_addr = ev_gen_ID;
	pEv->event_handler_addr = -1; 
	pEv->event_no = ev_no;
	pEv->event_pri = ev_pri;
	pEv->event_handler_addr = ev_handler_addr;
	pEv->eventStatus = ev_status; // 이벤트구조체의 각 항목을 받아온 정보로 초기화
}
void printEventArray(Event* pEv, int size, int items_per_line)
{
	for (int i = 0; i < size; i++)
	{
		printEvent(&pEv[i]); // printEvent함수에 pEv[i]의 주소값을 넘겨준다
		if (((i + 1) % items_per_line) == 0) 
			printf("\n ");
	}
}