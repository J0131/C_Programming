#include "PriorityQueue_Event.h"
#include "Event.h"

bool hasLeftChild(int pos, PriQ_Event* pPriQ_Ev)
{
	if (pos * 2 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
} // 어떤 노드의 pos * 2의 값이 pPriQ_Ev->priQ_size값보다 작거나 같으면 그노드는 왼쪽자식노드가 존재하는것이다
bool hasRightChild(int pos, PriQ_Event* pPriQ_Ev)
{
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
} // // 어떤 노드의 pos * 2 + 1 의 값이 pPriQ_Ev->priQ_size값보다 작거나 같으면 그노드는 오른쪽자식노드가 존재하는것이다
PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Ev, const char* name, int capacity)
{
	strcpy(pPriQ_Ev->PriQ_name, name);
	pPriQ_Ev->priQ_capacity = capacity;
	pPriQ_Ev->pCBT_Event = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event));
	pPriQ_Ev->priQ_size = 0;
	pPriQ_Ev->pos_last = 0;
	return pPriQ_Ev; // pPriQ_Ev를 주어진 정보로 초기화한다
}

void deletePriQ_Event(PriQ_Event* pPriQ_Ev)
{
	CBTN_Event* pCBTN_Ev;
	for (int i = 0; i < pPriQ_Ev->priQ_size; i++)
	{
		pCBTN_Ev = &(pPriQ_Ev->pCBT_Event)[i];
		if (pCBTN_Ev != NULL)
		{
			if (pCBTN_Ev->pEvent != NULL)
				free(pCBTN_Ev->pEvent);
			free(pCBTN_Ev);
		}
	}
} // pPriQ_Ev의 데이터를 모두 초기화한다
int insertPriQ_Event(PriQ_Event* pPriQ_Ev, Event* pEv)
{
	int pos, pos_parent,pos_last;
	CBTN_Event CBTN_Ev_tmp; // 임시로 저장할 CBTN_Event형 변수선언
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity)
	{ // pPriQ_Ev->priQ_size가 pPriQ_Ev->priQ_capacity보다 같거나 크면 배열의 크기를 늘려준다
		CBTN_Event* newCBT_Event; // 새로운 큐
		int newCapacity; // 새로운 큐의 크기
		newCapacity = 2 * pPriQ_Ev->priQ_capacity; // 새로운 큐의 크기는 원래의 큐의 크기의 2배
		newCBT_Event = (CBTN_Event*)malloc((newCapacity + 1) * sizeof(CBTN_Event)); // 새로운 큐를 newCapacity + 1의 크기만큼 동적할당해준다
		if (newCBT_Event == NULL)
		{
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n");
			exit(-1);
		}
		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++)
		{
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Event[pos];
		} // newCBT_Event[pos]의 값은 pPriQ_Ev->pCBT_Event[pos]이된다 - 새로만든 큐에 기존데이터를 옮겨줌
		free(pPriQ_Ev->pCBT_Event); 
		pPriQ_Ev->pCBT_Event = newCBT_Event;
		pPriQ_Ev->priQ_capacity = newCapacity; // 데이터를 다시 옮겨준다
	}
	pos = pos_last = ++pPriQ_Ev->priQ_size; // pos와 pos_last는 pPriQ_Ev->priQ_size의 값에서 1만큼 증가시킨값으로 설정해준다.
	pPriQ_Ev->pCBT_Event[pos].priority = pEv->event_pri; // pPriQ_Ev->pCBT_Event[pos].priority에 불러온pEv->event_pri값을 넣어준다
	pPriQ_Ev->pCBT_Event[pos].pEvent = pEv; //pPriQ_Ev->pCBT_Event[pos].pEvent에 불러온pEv를 넣어준다
	//up-heap bubbling
	while (pos != POS_ROOT)
	{
		pos_parent = pos / 2; // 부모노드의 위치는 현재노드의 위치에서 2로나눈몫이다
		if (pPriQ_Ev->pCBT_Event[pos].priority > pPriQ_Ev->pCBT_Event[pos_parent].priority)
		{
			break; 
		} // 현재노드의 우선순위가 부모노드의 우선순위보다 낮다면 자리를 바꿔줄필요가없다
		else
		{
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Event[pos_parent];
			pPriQ_Ev->pCBT_Event[pos_parent] = pPriQ_Ev->pCBT_Event[pos];
			pPriQ_Ev->pCBT_Event[pos] = CBTN_Ev_tmp;
			pos = pos_parent;
		} // 현재노드의 우선순위가 부모노드의 우선순위보다 높다면 부모노드와 자리를 바꾸어주고 다음 up-heap bubbling을 위해 현재노드의 위치를 부모노드의 위치로 바꾸어준다
	} 
}

Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Ev)
{
	Event* pEv;
	CBTN_Event CBT_Event_tmp;
	int pos, pos_root = 1, pos_last, pos_child;
	if (pPriQ_Ev->priQ_size <= 0) // pPriQ_Ev->priQ_size가 0보다 작거나크면 pPriQ_Ev안에 Event데이터가 없는것이다
		return NULL; 
	pEv = pPriQ_Ev->pCBT_Event[1].pEvent; // pEv를 root노드의 이벤트의 주소로 설정한다
	pos_last = pPriQ_Ev->priQ_size; // 가장 마지막 노드위치를 pPriQ_Ev->priQ_size로둔다
	--pPriQ_Ev->priQ_size; // pPriQ_Ev->priQ_size에서 1을 감소시킨다
	if (pPriQ_Ev->priQ_size > 0)
	{
		pPriQ_Ev->pCBT_Event[pos_root] = pPriQ_Ev->pCBT_Event[pos_last]; // 가장마지막노드의 데이터를 root노드의 데이터에 넣어준다
		pos_last--; // 가장 마지막 노드위치를 1감소시킨다
		// down-heap bubbling
		pos = pos_root; // 현재노드의 위치는 root노드의 위치로 설정해준다
		while (hasLeftChild(pos, pPriQ_Ev))
		{ // 현재위치노드의 왼쪽자식노드가 있는동안 반복한다
			pos_child = pos * 2; // 왼쪽자식노드의 위치는 현재노드위치에서 2를 곱해준값이다
			if (hasRightChild(pos, pPriQ_Ev)) // 만일 현재위치노드에서 오른쪽 자식노드가있다면
			{
				if (pPriQ_Ev->pCBT_Event[pos_child].priority >pPriQ_Ev->pCBT_Event[pos_child + 1].priority)
					pos_child = pos * 2 + 1; 
			} // 오른쪽 자식노드와 왼쪽 자식노드의 우선순위를 비교한다
			// 오른쪽 자식노드의 우선순위가 더높다면 현재노드와 위치를바꿀 자식노드는 오른쪽 자식노드가된다
			if (pPriQ_Ev->pCBT_Event[pos_child].priority < pPriQ_Ev->pCBT_Event[pos].priority)
			{
				CBT_Event_tmp = pPriQ_Ev->pCBT_Event[pos];
				pPriQ_Ev->pCBT_Event[pos] =pPriQ_Ev->pCBT_Event[pos_child];
				pPriQ_Ev->pCBT_Event[pos_child] = CBT_Event_tmp;
			}// 자식노드와 현재노드를 비교하여 자식노드의 우선순위가 더높다면 현재노드와 자식노드를 바꾸어준다
			else 
			{
				break;
			}
			pos = pos_child; // 다음 down-bubbling을 위해 현재노드의 위치는 자식 노드의 위치로 둔다
		} 
	} 
	return pEv; // root노드의 이벤트를 반환한다
}

void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Ev)
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;
	if (pPriQ_Ev->priQ_size == 0)
	{
		fprintf(fout, "PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; 
	fprintf(fout, "\n CompBinTree :\n", level);
	while (count <= pPriQ_Ev->priQ_size)
	{
		fprintf(fout, " level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count)
		{
			pEv = pPriQ_Ev->pCBT_Event[pos].pEvent;
			eventPriority = pPriQ_Ev->pCBT_Event[pos].priority;
			fprintEvent(fout, pEv);
			pos++;
			count++;
			if (count > pPriQ_Ev->priQ_size)
				break;
			count_per_line++;
			if ((count_per_line % EVENT_PER_LINE) == 0)
			{
				if (count_per_line < level_count)
					fprintf(fout, "\n ");
				else
					fprintf(fout, "\n");
			}
		} 
		if ((count_per_line % EVENT_PER_LINE) != 0)
			fprintf(fout, "\n");
		level++;
		level_count *= 2;
	} 
	fprintf(fout, "\n");
}

void printPriQ_Event(PriQ_Event* pPriQ_Ev)
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;
	if (pPriQ_Ev->priQ_size == 0)
	{
		printf("PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	level = 0;
	level_count = 1; // level_count = 2^^level
	printf("\n CompBinTree :\n", level);
	while (count <= pPriQ_Ev->priQ_size)
	{
		printf(" level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count)
		{
			pEv = pPriQ_Ev->pCBT_Event[pos].pEvent;
			eventPriority = pPriQ_Ev->pCBT_Event[pos].priority;
			printEvent(pEv);
			pos++;
			count++;
			if (count > pPriQ_Ev->priQ_size)
				break;
			count_per_line++;
			if ((count_per_line % EVENT_PER_LINE) == 0)
			{
				if (count_per_line < level_count)
					printf("\n ");
				else
					printf("\n");
			}
		} // end - while
		if ((count_per_line % EVENT_PER_LINE) != 0)
			printf("\n");
		level++;
		level_count *= 2;
	} // end - while
    printf("\n");
}