#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5
#define SIZE_DESCRIPTION 2048
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED }; // �̺�Ʈ�� ���¸� ���������� ����
extern const char* strEventStatus[]; // ���¸� ��Ÿ�� ���ڿ��迭 ����

typedef struct
{
	int event_no;
	int event_gen_addr;
	int event_handler_addr;
	int event_pri; // �̺�Ʈ�� �켱����
	EventStatus eventStatus;
} Event;
void initEvent(Event* pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr, EventStatus ev_status); // �̺�Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void printEvent(Event* pEvt); // �̺�Ʈ�� ȭ�鿡 ����ϴ� �Լ�
void fprintEvent(FILE* fout, Event* pEvent); // �̺�Ʈ�� ���Ͽ� ����ϴ� �Լ�
void printEventArray(Event* pEvent, int size, int items_per_line); // �̺�Ʈ�迭�� ����ϴ� �Լ�
Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri); // �̺�Ʈ�� �ϳ� ����� Event������������ ��ȯ���ִ��Լ�
#endif
