#include "PriorityQueue_Event.h"
#include "Event.h"

bool hasLeftChild(int pos, PriQ_Event* pPriQ_Ev)
{
	if (pos * 2 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
} // � ����� pos * 2�� ���� pPriQ_Ev->priQ_size������ �۰ų� ������ �׳��� �����ڽĳ�尡 �����ϴ°��̴�
bool hasRightChild(int pos, PriQ_Event* pPriQ_Ev)
{
	if (pos * 2 + 1 <= pPriQ_Ev->priQ_size)
		return TRUE;
	else
		return FALSE;
} // // � ����� pos * 2 + 1 �� ���� pPriQ_Ev->priQ_size������ �۰ų� ������ �׳��� �������ڽĳ�尡 �����ϴ°��̴�
PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Ev, const char* name, int capacity)
{
	strcpy(pPriQ_Ev->PriQ_name, name);
	pPriQ_Ev->priQ_capacity = capacity;
	pPriQ_Ev->pCBT_Event = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event));
	pPriQ_Ev->priQ_size = 0;
	pPriQ_Ev->pos_last = 0;
	return pPriQ_Ev; // pPriQ_Ev�� �־��� ������ �ʱ�ȭ�Ѵ�
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
} // pPriQ_Ev�� �����͸� ��� �ʱ�ȭ�Ѵ�
int insertPriQ_Event(PriQ_Event* pPriQ_Ev, Event* pEv)
{
	int pos, pos_parent,pos_last;
	CBTN_Event CBTN_Ev_tmp; // �ӽ÷� ������ CBTN_Event�� ��������
	if (pPriQ_Ev->priQ_size >= pPriQ_Ev->priQ_capacity)
	{ // pPriQ_Ev->priQ_size�� pPriQ_Ev->priQ_capacity���� ���ų� ũ�� �迭�� ũ�⸦ �÷��ش�
		CBTN_Event* newCBT_Event; // ���ο� ť
		int newCapacity; // ���ο� ť�� ũ��
		newCapacity = 2 * pPriQ_Ev->priQ_capacity; // ���ο� ť�� ũ��� ������ ť�� ũ���� 2��
		newCBT_Event = (CBTN_Event*)malloc((newCapacity + 1) * sizeof(CBTN_Event)); // ���ο� ť�� newCapacity + 1�� ũ�⸸ŭ �����Ҵ����ش�
		if (newCBT_Event == NULL)
		{
			printf("Error in expanding CompleteBinaryTree for Priority Queue !!\n");
			exit(-1);
		}
		for (int pos = 1; pos <= pPriQ_Ev->priQ_size; pos++)
		{
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Event[pos];
		} // newCBT_Event[pos]�� ���� pPriQ_Ev->pCBT_Event[pos]�̵ȴ� - ���θ��� ť�� ���������͸� �Ű���
		free(pPriQ_Ev->pCBT_Event); 
		pPriQ_Ev->pCBT_Event = newCBT_Event;
		pPriQ_Ev->priQ_capacity = newCapacity; // �����͸� �ٽ� �Ű��ش�
	}
	pos = pos_last = ++pPriQ_Ev->priQ_size; // pos�� pos_last�� pPriQ_Ev->priQ_size�� ������ 1��ŭ ������Ų������ �������ش�.
	pPriQ_Ev->pCBT_Event[pos].priority = pEv->event_pri; // pPriQ_Ev->pCBT_Event[pos].priority�� �ҷ���pEv->event_pri���� �־��ش�
	pPriQ_Ev->pCBT_Event[pos].pEvent = pEv; //pPriQ_Ev->pCBT_Event[pos].pEvent�� �ҷ���pEv�� �־��ش�
	//up-heap bubbling
	while (pos != POS_ROOT)
	{
		pos_parent = pos / 2; // �θ����� ��ġ�� �������� ��ġ���� 2�γ������̴�
		if (pPriQ_Ev->pCBT_Event[pos].priority > pPriQ_Ev->pCBT_Event[pos_parent].priority)
		{
			break; 
		} // �������� �켱������ �θ����� �켱�������� ���ٸ� �ڸ��� �ٲ����ʿ䰡����
		else
		{
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Event[pos_parent];
			pPriQ_Ev->pCBT_Event[pos_parent] = pPriQ_Ev->pCBT_Event[pos];
			pPriQ_Ev->pCBT_Event[pos] = CBTN_Ev_tmp;
			pos = pos_parent;
		} // �������� �켱������ �θ����� �켱�������� ���ٸ� �θ���� �ڸ��� �ٲپ��ְ� ���� up-heap bubbling�� ���� �������� ��ġ�� �θ����� ��ġ�� �ٲپ��ش�
	} 
}

Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Ev)
{
	Event* pEv;
	CBTN_Event CBT_Event_tmp;
	int pos, pos_root = 1, pos_last, pos_child;
	if (pPriQ_Ev->priQ_size <= 0) // pPriQ_Ev->priQ_size�� 0���� �۰ų�ũ�� pPriQ_Ev�ȿ� Event�����Ͱ� ���°��̴�
		return NULL; 
	pEv = pPriQ_Ev->pCBT_Event[1].pEvent; // pEv�� root����� �̺�Ʈ�� �ּҷ� �����Ѵ�
	pos_last = pPriQ_Ev->priQ_size; // ���� ������ �����ġ�� pPriQ_Ev->priQ_size�εд�
	--pPriQ_Ev->priQ_size; // pPriQ_Ev->priQ_size���� 1�� ���ҽ�Ų��
	if (pPriQ_Ev->priQ_size > 0)
	{
		pPriQ_Ev->pCBT_Event[pos_root] = pPriQ_Ev->pCBT_Event[pos_last]; // ���帶��������� �����͸� root����� �����Ϳ� �־��ش�
		pos_last--; // ���� ������ �����ġ�� 1���ҽ�Ų��
		// down-heap bubbling
		pos = pos_root; // �������� ��ġ�� root����� ��ġ�� �������ش�
		while (hasLeftChild(pos, pPriQ_Ev))
		{ // ������ġ����� �����ڽĳ�尡 �ִµ��� �ݺ��Ѵ�
			pos_child = pos * 2; // �����ڽĳ���� ��ġ�� ��������ġ���� 2�� �����ذ��̴�
			if (hasRightChild(pos, pPriQ_Ev)) // ���� ������ġ��忡�� ������ �ڽĳ�尡�ִٸ�
			{
				if (pPriQ_Ev->pCBT_Event[pos_child].priority >pPriQ_Ev->pCBT_Event[pos_child + 1].priority)
					pos_child = pos * 2 + 1; 
			} // ������ �ڽĳ��� ���� �ڽĳ���� �켱������ ���Ѵ�
			// ������ �ڽĳ���� �켱������ �����ٸ� ������� ��ġ���ٲ� �ڽĳ��� ������ �ڽĳ�尡�ȴ�
			if (pPriQ_Ev->pCBT_Event[pos_child].priority < pPriQ_Ev->pCBT_Event[pos].priority)
			{
				CBT_Event_tmp = pPriQ_Ev->pCBT_Event[pos];
				pPriQ_Ev->pCBT_Event[pos] =pPriQ_Ev->pCBT_Event[pos_child];
				pPriQ_Ev->pCBT_Event[pos_child] = CBT_Event_tmp;
			}// �ڽĳ��� �����带 ���Ͽ� �ڽĳ���� �켱������ �����ٸ� ������� �ڽĳ�带 �ٲپ��ش�
			else 
			{
				break;
			}
			pos = pos_child; // ���� down-bubbling�� ���� �������� ��ġ�� �ڽ� ����� ��ġ�� �д�
		} 
	} 
	return pEv; // root����� �̺�Ʈ�� ��ȯ�Ѵ�
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