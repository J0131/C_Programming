/************************************************
* ���ϸ��� : circular buffer�� ��������� FiFO queue�� ����Ʈ������������� piroirty queue����
* �ۼ��� : �ֹ���
* final update : 2020-06-11
*************************************************/
#include <stdio.h>
#include <time.h>
#include "Event.h"
#include "CircularQueue.h"
#include "PriorityQueue_Event.h"

#define CIRQUEUE_CAPACITY 10
#define EVENT_GENERATOR 0
#define TOTAL_NUM_EVENTS 50
#define MAX_EVENTS_PER_ROUND 5
#define MAX_ROUND 100
#define INIT_PriQ_SIZE 1 // �������� ����
void test_FIFO_CirQ_Event(FILE* fout);
void test_PriQ_Event(FILE* fout);
void main()
{
	FILE* fout; // ���������� ����
	int menu;
	fout = fopen("output.txt", "w"); // output.txt�� ������� ����
	if (fout == NULL)
	{
		printf("Error in creation of output.txt file !!\n");
		exit(-1);
	} // �����Ͱ� NULL�̸� ����ó��
	srand(time(0)); // �õ��ʱ�ȭ
	while (1)
	{
		printf(" 1. Test FIFO/CirQ Event.\n");
		printf(" 2. Test PriQ Event.\n");
		printf("-1: Quit\n");
		printf("Input menu : "); // ȭ�鿡 ���� �Է¹ް� menu������ ����
		scanf("%d", &menu);
		if (menu == -1)
			break; // menu�� -1�̸� ���α׷� ����
		switch (menu)
		{
		case 1:
			test_FIFO_CirQ_Event(fout);
			break; // menu��1�϶� ����ť�� �����ϴ� ���α׷�
		case 2:
			test_PriQ_Event(fout);
			break; // menu��2�϶� �켱����ť�� �����ϴ� ���α׷�
		default:
			break;
		} 
	} 
	fclose(fout);
}

void test_FIFO_CirQ_Event(FILE* fout) // ���� ť�� �����ϴ� �Լ�
{
    CircularQueue* pCirQ_Event; // CircularQueue���������� ������ ����
    Event ev, *pEv = NULL; // Event���� ��������
    int processed_events = 0; // ó���� �̺�Ʈ�� processed_events�� ����
    int generated_events = 0; // ������ �̺�Ʈ�� generated_events�� ����
    int num_events = 0; // ���� �����ϴ� �̺�Ʈ�� ���ڸ� num_events�μ���
    pCirQ_Event = (CircularQueue*)malloc(sizeof(CircularQueue)); // CircularQueue* ������ �������Ͽ� �����Ҵ�
    fprintf(fout, "Initializing integer stack of capacity (%d)\n", QUEUE_CAPACITY);
    pCirQ_Event = initCirQueue(pCirQ_Event, QUEUE_CAPACITY); // CircularQueue*�� pCirQ_Event�� �ʱ�ȭ���ش�
    for (int round = 0; round < MAX_ROUND; round++)
    {
        if (generated_events < TOTAL_NUM_EVENTS)
        { // ������ �̺�Ʈ������ ��ü �̺�Ʈ�������� ������
            num_events = rand() % MAX_EVENTS_PER_ROUND; // num_events�� rand() % MAX_EVENTS_PER_ROUND�� �ȴ�.
            if ((generated_events + num_events) > TOTAL_NUM_EVENTS) // ������ �̺�Ʈ�� �����ϴ� �̺�Ʈ�� ���� �������� �̰��� TOTAL_NUM_EVENTS���� ũ�ٸ� 
                num_events = TOTAL_NUM_EVENTS - generated_events; // ��ü �̺�Ʈ������ ������ �̺�Ʈ ����ŭ�� �A���� ���� ������ �̺�Ʈ�������ȴ�.
            fprintf(fout, "generate and enque %2d events\n", num_events);
            for (int i = 0; i < num_events; i++)
            {
                if (isCirQueueFull(pCirQ_Event)) // ���� ���� ť�� �����Ͱ� �������ִٸ� �ݺ����� ������
                {
                    fprintf(fout, " !!! CirQ_Event is full --> skip generation and enqueueing of event. \n");
                        break;
                }
                pEv = genEvent(pEv, EVENT_GENERATOR, generated_events,TOTAL_NUM_EVENTS - generated_events - 1); // pEv�������� ������ �ʱ�ȭ��Ų��
                fprintf(fout, ">>> Enqueue event = ");
                fprintEvent(fout, pEv);
                fprintf(fout, "\n");
                enCirQueue(fout, pCirQ_Event, *pEv); // pCirQ_Event�� pEv�� �����͸� �־��ش�
                fprintCirQueue(fout, pCirQ_Event);
                free(pEv); // pEv�� ���������Ѵ�
                generated_events++; // �߻��� event�� 1������Ų��
            } 
        } 
        num_events = rand() % MAX_EVENTS_PER_ROUND; // num_events �� rand() % MAX_EVENTS_PER_ROUND���μ����Ѵ�
        if ((processed_events + num_events) > TOTAL_NUM_EVENTS)  // ó���� �̺�Ʈ + �̹��� ������ �̺�Ʈ�� �� �̺�Ʈ������ ũ��
            num_events = TOTAL_NUM_EVENTS - processed_events; //  num_events�� TOTAL_NUM_EVENTS - processed_events�εд�
        fprintf(fout, "dequeue %2d events\n", num_events);
        for (int i = 0; i < num_events; i++)
        {
            if (isCirQueueEmpty(pCirQ_Event))
                break; // ����ť�� �����Ͱ� �ϳ������ٸ� �ݺ����� ����������
            pEv = deCirQueue(fout, pCirQ_Event); // �����͸� ����
            if (pEv != NULL)
            {
                fprintf(fout, "<<< Dequed event = ");
                fprintEvent(fout, pEv);
                fprintf(fout, "\n");
                processed_events++; // �� �������� ������ ���Ͽ� ������ְ� ó���� �̺�Ʈ�� 1������Ų��
            }
            fprintCirQueue(fout, pCirQ_Event);
        } 
        fprintf(fout, "Round(%2d): total_generated_events(%3d), total_processed_events(%3d),CirQ capacity(% 2d), events_in_queue(% 3d)\n\n", round, generated_events,processed_events, pCirQ_Event->capacity, pCirQ_Event->num_elements);
        if (processed_events >= TOTAL_NUM_EVENTS)
            break; // ó���� �̺�Ʈ�� �� �̺�Ʈ���� ũ�ų� �������ԵǸ� �ݺ����� ����������.
    } 
    delCirQueue(pCirQ_Event); // pCirQ_Event���� �����͸� ��� �����Ѵ�
}

void test_PriQ_Event(FILE* fout) // �켱���� ť�� �����ϴ� �Լ�
{
    PriQ_Event* PriQ_Ev;
    Event* pEv = NULL;
    int data;
    int processed_events = 0; // ó���� �̺�Ʈ�� ��Ÿ���� ����
    int generated_events = 0; // �߻��� �̺�Ʈ�� ��Ÿ���� ����
    int num_events = 0; // ���� ������ �̺�Ʈ�� ��Ÿ���� ����
    PriQ_Ev = (PriQ_Event*)malloc(sizeof(PriQ_Event)); // PriQ_Event���������� PriQ_Ev�����Ҵ�
    if (PriQ_Ev == NULL)
    {
        printf("Error in malloc() for PriorityQueue_Event !\n");
        fclose(fout);
        exit(-1);
    } // ����ó��
    initPriQ_Event(PriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE); // PriQ_Ev�� ������ ������ �ʱ�ȭ
    for (int round = 0; round < MAX_ROUND; round++)
    {
        if (generated_events < TOTAL_NUM_EVENTS)
        { // ������ �̺�Ʈ�� ���̺�Ʈ���� ������
            num_events = rand() % MAX_EVENTS_PER_ROUND; //num_events�� rand() % MAX_EVENTS_PER_ROUND
            if ((generated_events + num_events) > TOTAL_NUM_EVENTS) // ������ �̺�Ʈ�� �̹��� �����ϴ� �̺�Ʈ������ ���̺�Ʈ���� ũ�ٸ�
                num_events = TOTAL_NUM_EVENTS - generated_events; //num_events�� TOTAL_NUM_EVENTS���� generated_events�� ������ �ȴ�
            fprintf(fout, ">>> enque %2d events\n", num_events);
            for (int i = 0; i < num_events; i++)
            {
                pEv = genEvent(pEv, 0, generated_events, TOTAL_NUM_EVENTS - generated_events - 1);// pEv�� ������ ���� ������ �����
                if (pEv == NULL)
                {
                    printf("Error in generation of event !!\n");
                    fclose(fout);
                    exit(-1);
                }
                fprintf(fout, " *** enqued event : ");
                fprintEvent(fout, pEv);
                insertPriQ_Event(PriQ_Ev, pEv); // pEv�� �����͸� PriQ_Ev�� �ִ´�
                generated_events++; // �߻��� �̺�Ʈ�� 1������Ų��
                fprintPriQ_Event(fout, PriQ_Ev);
            }
        }
        num_events = rand() % MAX_EVENTS_PER_ROUND; // num_events�� rand() % MAX_EVENTS_PER_ROUND�� ���� ������
        if ((processed_events + num_events) > TOTAL_NUM_EVENTS) // ó���� �̺�Ʈ�� ��������� �̺�Ʈ�� ���� �� �̺�Ʈ�� �������� ũ�ٸ�
            num_events = TOTAL_NUM_EVENTS - processed_events; //num_events�� TOTAL_NUM_EVENTS���� processed_events��ŭ�� �A ������ �����Ѵ�
        fprintf(fout, "<<< dequeue %2d events\n", num_events);
        for (int i = 0; i < num_events; i++) // �̹��� ������ �̺�Ʈ�� ������ŭ �ݺ�
        {
            pEv = removeMinPriQ_Event(PriQ_Ev); // �켱������ ������� �����͸� PriQ_Ev���� ���µ� pEv�� �����Ѵ�
            if (pEv == NULL)
            {
                fprintf(fout, " PriQ is empty\n");
                break;
            }
            fprintf(fout, " *** dequeued event : ");
            fprintEvent(fout, pEv);
            fprintPriQ_Event(fout, PriQ_Ev);
            processed_events++; // ó���� �̺�Ʈ�� ������ 1�÷��ش�
        }
        /* Monitoring simulation status */
        fprintf(fout, "\nRound(%2d): total_generated_events(%3d), total_processed_events(%3d),PriQ capacity(% 2d), events_in_PriQ(% 3d)\n", round, generated_events, processed_events,PriQ_Ev->priQ_capacity, PriQ_Ev->priQ_size);
        fflush(fout); // ��� ���۸� ���� 
        if (processed_events >= TOTAL_NUM_EVENTS)
            break; // ���������� ó���� �̺�Ʈ�� �� �̺�Ʈ�� �������� ���ų� Ŀ���� �ݺ����� ������
    }
    deletePriQ_Event(PriQ_Ev);
    fprintf(fout, "\n");
    fclose(fout);
}
