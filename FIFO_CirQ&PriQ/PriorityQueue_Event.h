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
    int priority; // 우선순위
    Event* pEvent;
} CBTN_Event; // 완전이진트리
typedef struct
{
    char PriQ_name[MAX_NAME_LEN];
    int priQ_capacity;
    int priQ_size;
    int pos_last;
    CBTN_Event* pCBT_Event;
} PriQ_Event;

PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Ev, const char* name, int capacity); // PriQ_Event포인트형 pPriQ_Ev를 초기화하는 함수
int insertPriQ_Event(PriQ_Event* pPriQ_Ev, Event* pEv); // PriQ_Event포인트형 pPriQ_Ev에 이벤트를 넣는 함수
Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Ev); // PriQ_Event포인트형 pPriQ_Ev에서 우선순위가 가장높은 이벤트를 삭제하는 함수
void printPriQ_Event(PriQ_Event* pPriQ_Ev); // PriQ_Event포인트형 pPriQ_Ev를 화면에 출력하는 함수
void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Ev); //PriQ_Event포인트형 pPriQ_Ev를 파일에 출력하는함수
void deletePriQ_Event(PriQ_Event* pPriQ_Ev); // PriQ_Event포인트형 pPriQ_Ev의 데이터를 삭제하는 함수
bool hasLeftChild(int pos, PriQ_Event* pPriQ_Ev); //PriQ_Event포인트형 pPriQ_Ev의 이벤트가 들어가있는노드에서 왼쪽자식노드가있는지 확인하는 함수
bool hasRightChild(int pos, PriQ_Event* pPriQ_Ev); //PriQ_Event포인트형 pPriQ_Ev의 이벤트가 들어가있는노드에서 오른쪽자식노드가있는지 확인하는 함수

#endif