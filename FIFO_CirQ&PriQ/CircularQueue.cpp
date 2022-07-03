#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"
CircularQueue* initCirQueue(CircularQueue* cirQ, int capacity)
{
	Event* pEv; // Event �������� pEv����
	pEv = (Event*)calloc(capacity, sizeof(Event)); // pEv�� capacity�� ũ�⸦ ������ 1���� �迭���Ҵ�
	if (pEv == NULL)
	{
		printf("Error in memory allocation for Event array of size (%d)\n", capacity);
		exit;
	}
	cirQ->pEv = pEv; 
	cirQ->capacity = capacity;
	cirQ->front = cirQ->end = 0;
	cirQ->num_elements = 0; // CircularQueue�������� cirQ�� �ʱ���������
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
	} // ����ó��
	fprintf(fout, " %2d Elements in CirQ_Event (index_front:%2d) :\n ",cirQ->num_elements, cirQ->front);
	if (isCirQueueEmpty(cirQ))
	{
		fprintf(fout, "CirQ_Event is Empty");
	} // cirQ�ȿ� �����Ͱ� ������
	else // cirQ�ȿ� �����Ͱ� �ִٸ�
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
		{ // cirQ���� �����͸�ŭ �ݺ�
			index = cirQ->front + i;
			if (index >= cirQ->capacity)
				index = index % cirQ->capacity; // cirQ�� �����̱⶧���� index���� cirQ->capacity���� ���ų� ũ�� index�� index % cirQ->capacity���ȴ�
			ev = cirQ->pEv[index]; // index��ġ�� �̺�Ʈ�� ev�� �־��ش�
			printEvent(&ev); // ev�� �ּҰ��� �Ѱ��ش�
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
}// cirQ�� ������Ұ����� cirQ�� �ִ밹���� ���ٸ� ���� ���ִ°��̹Ƿ� 1�� ��ȯ
bool isCirQueueEmpty(CircularQueue* cirQ)
{
	if (cirQ->num_elements == 0)
		return true;
	else
		return false;
}// cirQ�� ������Ұ����� 0�̶�� ����ִ°��̹Ƿ� 1�� ��ȯ
Event* enCirQueue(FILE* fout, CircularQueue* cirQ, Event ev)
{
	if (isCirQueueFull(cirQ))
	{
		return NULL;
	} // cirQ->pEv�� �������ִ��� Ȯ��
	cirQ->pEv[cirQ->end] = ev; // cirQ->pEv[cirQ->end]�� �޾ƿ� Event�� ������ ev�� �־��ش�
	cirQ->num_elements++; // ��������� ������ 1��ŭ�ø���
	cirQ->end++; // end���� 1�ø���
	if (cirQ->end >= cirQ->capacity)
		cirQ->end = cirQ->end % cirQ->capacity; // end�� capacity���� ���ų� Ŀ���ٸ� end�� cirQ->end % cirQ->capacity�� �ȴ�.
	return &(cirQ->pEv[cirQ->end]); // cirQ->pEv[cirQ->end]�� �ּҸ� ��ȯ�Ѵ�
}
Event* deCirQueue(FILE* fout, CircularQueue* cirQ)
{
	if (isCirQueueEmpty(cirQ))
		return NULL; // cirQ->pEv�� ����ִ��� Ȯ��
	Event* pEv = &(cirQ->pEv[cirQ->end-1]); // pEv�� cirQ->pEv[cirQ->front]�� �ּҰ��� �����Ѵ�
	cirQ->end--; // front�� 1�÷��ش�
	if (cirQ->end < 0)
		cirQ->end = cirQ->capacity - 1;// front�� capacity���� ���ų� Ŀ���ٸ� front�� cirQ->end % cirQ->capacity�� �ȴ�.
	cirQ->num_elements--; // ����m���� ������ 1��ŭ �����Ѵ�
	return pEv; // pEv�� ��ȯ�Ѵ�.
}
void delCirQueue(CircularQueue* cirQ)
{
	if (cirQ->pEv != NULL)
		free(cirQ->pEv); // cirQ->pEv�� �����Ͱ� �����ִٸ� �����Ҵ������� ���ش�
	cirQ->pEv = NULL; 
	cirQ->capacity = 0;
	cirQ->front = cirQ->end = 0;
	cirQ->num_elements = 0; // ��� �����͸� 0���� �ٲپ��ش�
}