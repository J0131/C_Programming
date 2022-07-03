#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"
CircularQueue* initCirQueue(CircularQueue* cirQ, int capacity)
{
	Event* pEv; // Event 포인터형 pEv선언
	pEv = (Event*)calloc(capacity, sizeof(Event)); // pEv를 capacity의 크기를 가지는 1차원 배열로할당
	if (pEv == NULL)
	{
		printf("Error in memory allocation for Event array of size (%d)\n", capacity);
		exit;
	}
	cirQ->pEv = pEv; 
	cirQ->capacity = capacity;
	cirQ->front = cirQ->end = 0;
	cirQ->num_elements = 0; // CircularQueue포인터형 cirQ에 초기정보대입
	return cirQ; 
}

void fprintCirQueue(FILE* fout, CircularQueue* cirQ)
{
	Event ev;
	int index;
	if ((cirQ == NULL) || (cirQ->pEv == NULL))
	{
		printf("Error in printArrayQueue: cirQ is NULL or cirQ->array is NULL");
		exit;
	} // 예외처리
	fprintf(fout, " %2d Elements in CirQ_Event (index_front:%2d) :\n ",cirQ->num_elements, cirQ->front);
	if (isCirQueueEmpty(cirQ))
	{
		fprintf(fout, "CirQ_Event is Empty");
	} // cirQ안에 데이터가 없을때
	else // cirQ안에 데이터가 있다면
	{
		for (int i = 0; i < cirQ->num_elements; i++)
		{
			index = cirQ->front + i;
			if (index >= cirQ->capacity)
				index = index % cirQ->capacity;
			ev = cirQ->pEv[index];
			fprintEvent(fout, &ev);
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != cirQ->num_elements))
				fprintf(fout, "\n ");
		}
	}
	fprintf(fout, "\n");
}
void printCirQueue(CircularQueue* cirQ)
{
	Event ev;
	int index;
	if ((cirQ == NULL) || (cirQ->pEv == NULL))
	{
		printf("Error in printArrayQueue: cirQ is NULL or cirQ->array is NULL");
		exit;
	}
	printf(" %2d Elements in CirQ_Event (index_front:%2d) :\n ",cirQ->num_elements, cirQ->front);
	if (isCirQueueEmpty(cirQ))
	{
		printf("CirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < cirQ->num_elements; i++)
		{ // cirQ안의 데이터만큼 반복
			index = cirQ->front + i;
			if (index >= cirQ->capacity)
				index = index % cirQ->capacity; // cirQ가 원형이기때문에 index값이 cirQ->capacity보다 같거나 크면 index는 index % cirQ->capacity가된다
			ev = cirQ->pEv[index]; // index위치의 이벤트를 ev에 넣어준다
			printEvent(&ev); // ev의 주소값을 넘겨준다
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != cirQ->num_elements))
				printf("\n ");
		}
	}
	printf("\n");
}
bool isCirQueueFull(CircularQueue* cirQ)
{
	if (cirQ->num_elements == cirQ->capacity)
		return true;
	else
		return false;
}// cirQ의 현재원소갯수가 cirQ의 최대갯수와 같다면 가득 차있는것이므로 1을 반환
bool isCirQueueEmpty(CircularQueue* cirQ)
{
	if (cirQ->num_elements == 0)
		return true;
	else
		return false;
}// cirQ의 현재원소갯수가 0이라면 비어있는것이므로 1을 반환
Event* enCirQueue(FILE* fout, CircularQueue* cirQ, Event ev)
{
	if (isCirQueueFull(cirQ))
	{
		return NULL;
	} // cirQ->pEv가 가득차있는지 확인
	cirQ->pEv[cirQ->end] = ev; // cirQ->pEv[cirQ->end]에 받아온 Event형 데이터 ev를 넣어준다
	cirQ->num_elements++; // 현재원소의 갯수를 1만큼늘린다
	cirQ->end++; // end값을 1늘린다
	if (cirQ->end >= cirQ->capacity)
		cirQ->end = cirQ->end % cirQ->capacity; // end가 capacity보다 같거나 커진다면 end는 cirQ->end % cirQ->capacity가 된다.
	return &(cirQ->pEv[cirQ->end]); // cirQ->pEv[cirQ->end]의 주소를 반환한다
}
Event* deCirQueue(FILE* fout, CircularQueue* cirQ)
{
	if (isCirQueueEmpty(cirQ))
		return NULL; // cirQ->pEv가 비어있는지 확인
	Event* pEv = &(cirQ->pEv[cirQ->end-1]); // pEv에 cirQ->pEv[cirQ->front]의 주소값을 저장한다
	cirQ->end--; // front를 1늘려준다
	if (cirQ->end < 0)
		cirQ->end = cirQ->capacity - 1;// front가 capacity보다 같거나 커진다면 front는 cirQ->end % cirQ->capacity가 된다.
	cirQ->num_elements--; // 현재웟소의 갯수를 1만큼 감소한다
	return pEv; // pEv를 반환한다.
}
void delCirQueue(CircularQueue* cirQ)
{
	if (cirQ->pEv != NULL)
		free(cirQ->pEv); // cirQ->pEv에 데이터가 남아있다면 동적할당해제를 해준다
	cirQ->pEv = NULL; 
	cirQ->capacity = 0;
	cirQ->front = cirQ->end = 0;
	cirQ->num_elements = 0; // 모든 데이터를 0으로 바꾸어준다
}