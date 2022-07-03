#include <stdio.h>
#include <stdlib.h>
#include "Event.h"
const char* strEventStatus[] = {"GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" }; // �̺�Ʈ�� ���¸� ��Ÿ������ ���ڿ��迭

void printEvent(Event* pEvent)
{
	char str_pri[6]; 
	printf("Ev(no:%3d, pri:%2d) ", pEvent->event_no, pEvent->event_pri); // �޾ƿ� �̺�Ʈ�� ��ȣ�� �켱������ ȭ�鿡 ���
}
void fprintEvent(FILE* fout, Event* pEvent)
{
	char str_pri[6];
	fprintf(fout, "Ev(no:%3d, pri:%2d) ", pEvent->event_no, pEvent->event_pri); // �޾ƿ� �̺�Ʈ�� ��ȣ�� �켱������ ���Ͽ� ���
}
Event* genEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri)
{
	pEv = (Event*)calloc(1, sizeof(Event)); // �޾ƿ� �̺�Ʈ pEv�� �����Ҵ�
	if (pEv == NULL)
		return NULL;
	initEvent(pEv, ev_gen_ID, ev_no, ev_pri, -1, GENERATED); // �̺�Ʈ pEv�� �޾ƿ������� �ʱ�ȭ�Ѵ�
	return pEv; // pEv ��ȯ
}
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status)
{
	pEv->event_gen_addr = ev_gen_ID;
	pEv->event_handler_addr = -1; 
	pEv->event_no = ev_no;
	pEv->event_pri = ev_pri;
	pEv->event_handler_addr = ev_handler_addr;
	pEv->eventStatus = ev_status; // �̺�Ʈ����ü�� �� �׸��� �޾ƿ� ������ �ʱ�ȭ
}
void printEventArray(Event* pEv, int size, int items_per_line)
{
	for (int i = 0; i < size; i++)
	{
		printEvent(&pEv[i]); // printEvent�Լ��� pEv[i]�� �ּҰ��� �Ѱ��ش�
		if (((i + 1) % items_per_line) == 0) 
			printf("\n ");
	}
}