#ifndef PEVENT_H
#define PEVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Event.h"
#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0
#define TOTAL_NUM_EVENTS 50
#define MAX_EVENTS_PER_ROUND 5
#define MAX_ROUND 100 
#define INIT_PriQ_SIZE 1 
typedef struct
{
    int priority; // �켱����
    Event* pEvent;
} CBTN_Event; // ��������Ʈ��
typedef struct
{
    char PriQ_name[MAX_NAME_LEN];
    int priQ_capacity;
    int priQ_size;
    int pos_last;
    CBTN_Event* pCBT_Event;
} PriQ_Event;

PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Ev, const char* name, int capacity); // PriQ_Event����Ʈ�� pPriQ_Ev�� �ʱ�ȭ�ϴ� �Լ�
int insertPriQ_Event(PriQ_Event* pPriQ_Ev, Event* pEv); // PriQ_Event����Ʈ�� pPriQ_Ev�� �̺�Ʈ�� �ִ� �Լ�
Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Ev); // PriQ_Event����Ʈ�� pPriQ_Ev���� �켱������ ������� �̺�Ʈ�� �����ϴ� �Լ�
void printPriQ_Event(PriQ_Event* pPriQ_Ev); // PriQ_Event����Ʈ�� pPriQ_Ev�� ȭ�鿡 ����ϴ� �Լ�
void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Ev); //PriQ_Event����Ʈ�� pPriQ_Ev�� ���Ͽ� ����ϴ��Լ�
void deletePriQ_Event(PriQ_Event* pPriQ_Ev); // PriQ_Event����Ʈ�� pPriQ_Ev�� �����͸� �����ϴ� �Լ�
bool hasLeftChild(int pos, PriQ_Event* pPriQ_Ev); //PriQ_Event����Ʈ�� pPriQ_Ev�� �̺�Ʈ�� ���ִ³�忡�� �����ڽĳ�尡�ִ��� Ȯ���ϴ� �Լ�
bool hasRightChild(int pos, PriQ_Event* pPriQ_Ev); //PriQ_Event����Ʈ�� pPriQ_Ev�� �̺�Ʈ�� ���ִ³�忡�� �������ڽĳ�尡�ִ��� Ȯ���ϴ� �Լ�

#endif