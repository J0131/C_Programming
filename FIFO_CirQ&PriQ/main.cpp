/************************************************
* 파일목적 : circular buffer를 기반으로한 FiFO queue와 완전트리를기반으로한 piroirty queue구현
* 작성자 : 최범준
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
#define INIT_PriQ_SIZE 1 // 전역변수 선언
void test_FIFO_CirQ_Event(FILE* fout);
void test_PriQ_Event(FILE* fout);
void main()
{
	FILE* fout; // 파일포인터 선언
	int menu;
	fout = fopen("output.txt", "w"); // output.txt를 쓰기모드로 열기
	if (fout == NULL)
	{
		printf("Error in creation of output.txt file !!\n");
		exit(-1);
	} // 포인터가 NULL이면 에러처리
	srand(time(0)); // 시드초기화
	while (1)
	{
		printf(" 1. Test FIFO/CirQ Event.\n");
		printf(" 2. Test PriQ Event.\n");
		printf("-1: Quit\n");
		printf("Input menu : "); // 화면에 수를 입력받고 menu값으로 저장
		scanf("%d", &menu);
		if (menu == -1)
			break; // menu가 -1이면 프로그램 종료
		switch (menu)
		{
		case 1:
			test_FIFO_CirQ_Event(fout);
			break; // menu가1일때 원형큐를 구현하는 프로그램
		case 2:
			test_PriQ_Event(fout);
			break; // menu가2일때 우선순위큐를 구현하는 프로그램
		default:
			break;
		} 
	} 
	fclose(fout);
}

void test_FIFO_CirQ_Event(FILE* fout) // 원형 큐를 구현하는 함수
{
    CircularQueue* pCirQ_Event; // CircularQueue포인터형의 변수를 선언
    Event ev, *pEv = NULL; // Event형의 변수선언
    int processed_events = 0; // 처리된 이벤트를 processed_events로 선언
    int generated_events = 0; // 생성된 이벤트를 generated_events로 선언
    int num_events = 0; // 현재 생성하는 이벤트의 숫자를 num_events로선언
    pCirQ_Event = (CircularQueue*)malloc(sizeof(CircularQueue)); // CircularQueue* 형으로 형변한하여 동적할당
    fprintf(fout, "Initializing integer stack of capacity (%d)\n", QUEUE_CAPACITY);
    pCirQ_Event = initCirQueue(pCirQ_Event, QUEUE_CAPACITY); // CircularQueue*형 pCirQ_Event를 초기화해준다
    for (int round = 0; round < MAX_ROUND; round++)
    {
        if (generated_events < TOTAL_NUM_EVENTS)
        { // 생성된 이벤트갯수가 전체 이벤트갯수보다 작을때
            num_events = rand() % MAX_EVENTS_PER_ROUND; // num_events는 rand() % MAX_EVENTS_PER_ROUND가 된다.
            if ((generated_events + num_events) > TOTAL_NUM_EVENTS) // 생성된 이벤트와 생성하는 이벤트의 수를 더했을때 이값이 TOTAL_NUM_EVENTS보다 크다면 
                num_events = TOTAL_NUM_EVENTS - generated_events; // 전체 이벤트수에서 생성한 이벤트 수만큼을 뺸값이 현재 생성할 이벤트갯수가된다.
            fprintf(fout, "generate and enque %2d events\n", num_events);
            for (int i = 0; i < num_events; i++)
            {
                if (isCirQueueFull(pCirQ_Event)) // 만약 원형 큐에 데이터가 가득차있다면 반복문을 나간다
                {
                    fprintf(fout, " !!! CirQ_Event is full --> skip generation and enqueueing of event. \n");
                        break;
                }
                pEv = genEvent(pEv, EVENT_GENERATOR, generated_events,TOTAL_NUM_EVENTS - generated_events - 1); // pEv를다음의 정보로 초기화시킨다
                fprintf(fout, ">>> Enqueue event = ");
                fprintEvent(fout, pEv);
                fprintf(fout, "\n");
                enCirQueue(fout, pCirQ_Event, *pEv); // pCirQ_Event에 pEv의 데이터를 넣어준다
                fprintCirQueue(fout, pCirQ_Event);
                free(pEv); // pEv를 동적해제한다
                generated_events++; // 발생한 event를 1증가시킨다
            } 
        } 
        num_events = rand() % MAX_EVENTS_PER_ROUND; // num_events 는 rand() % MAX_EVENTS_PER_ROUND으로설정한다
        if ((processed_events + num_events) > TOTAL_NUM_EVENTS)  // 처리한 이벤트 + 이번에 생성할 이벤트가 총 이벤트수보다 크면
            num_events = TOTAL_NUM_EVENTS - processed_events; //  num_events는 TOTAL_NUM_EVENTS - processed_events로둔다
        fprintf(fout, "dequeue %2d events\n", num_events);
        for (int i = 0; i < num_events; i++)
        {
            if (isCirQueueEmpty(pCirQ_Event))
                break; // 원형큐에 데이터가 하나도없다면 반복문을 빠져나간다
            pEv = deCirQueue(fout, pCirQ_Event); // 데이터를 뺀다
            if (pEv != NULL)
            {
                fprintf(fout, "<<< Dequed event = ");
                fprintEvent(fout, pEv);
                fprintf(fout, "\n");
                processed_events++; // 뺀 데이터의 정보를 파일에 출력해주고 처리된 이벤트를 1증가시킨다
            }
            fprintCirQueue(fout, pCirQ_Event);
        } 
        fprintf(fout, "Round(%2d): total_generated_events(%3d), total_processed_events(%3d),CirQ capacity(% 2d), events_in_queue(% 3d)\n\n", round, generated_events,processed_events, pCirQ_Event->capacity, pCirQ_Event->num_elements);
        if (processed_events >= TOTAL_NUM_EVENTS)
            break; // 처리된 이벤트가 총 이벤트보다 크거나 같아지게되면 반복문을 빠져나간다.
    } 
    delCirQueue(pCirQ_Event); // pCirQ_Event안의 데이터를 모두 삭제한다
}

void test_PriQ_Event(FILE* fout) // 우선순위 큐를 구현하는 함수
{
    PriQ_Event* PriQ_Ev;
    Event* pEv = NULL;
    int data;
    int processed_events = 0; // 처리된 이벤트를 나타내는 변수
    int generated_events = 0; // 발생된 이벤트를 나타내는 변수
    int num_events = 0; // 현재 생성할 이벤트를 나타내는 변수
    PriQ_Ev = (PriQ_Event*)malloc(sizeof(PriQ_Event)); // PriQ_Event포인터형의 PriQ_Ev동적할당
    if (PriQ_Ev == NULL)
    {
        printf("Error in malloc() for PriorityQueue_Event !\n");
        fclose(fout);
        exit(-1);
    } // 예외처리
    initPriQ_Event(PriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE); // PriQ_Ev를 다음의 정보로 초기화
    for (int round = 0; round < MAX_ROUND; round++)
    {
        if (generated_events < TOTAL_NUM_EVENTS)
        { // 생성된 이벤트가 총이벤트보다 작을때
            num_events = rand() % MAX_EVENTS_PER_ROUND; //num_events는 rand() % MAX_EVENTS_PER_ROUND
            if ((generated_events + num_events) > TOTAL_NUM_EVENTS) // 생성된 이벤트와 이번에 생성하는 이벤트의합이 총이벤트보다 크다면
                num_events = TOTAL_NUM_EVENTS - generated_events; //num_events는 TOTAL_NUM_EVENTS에서 generated_events를 뺀값이 된다
            fprintf(fout, ">>> enque %2d events\n", num_events);
            for (int i = 0; i < num_events; i++)
            {
                pEv = genEvent(pEv, 0, generated_events, TOTAL_NUM_EVENTS - generated_events - 1);// pEv를 다음과 같은 정보로 만든다
                if (pEv == NULL)
                {
                    printf("Error in generation of event !!\n");
                    fclose(fout);
                    exit(-1);
                }
                fprintf(fout, " *** enqued event : ");
                fprintEvent(fout, pEv);
                insertPriQ_Event(PriQ_Ev, pEv); // pEv의 데이터를 PriQ_Ev에 넣는다
                generated_events++; // 발생한 이벤트를 1증가시킨다
                fprintPriQ_Event(fout, PriQ_Ev);
            }
        }
        num_events = rand() % MAX_EVENTS_PER_ROUND; // num_events는 rand() % MAX_EVENTS_PER_ROUND의 값을 가진다
        if ((processed_events + num_events) > TOTAL_NUM_EVENTS) // 처리한 이벤트와 현재생성할 이벤트의 합이 총 이벤트의 갯수보다 크다면
            num_events = TOTAL_NUM_EVENTS - processed_events; //num_events는 TOTAL_NUM_EVENTS에서 processed_events만큼을 뺸 값으로 설정한다
        fprintf(fout, "<<< dequeue %2d events\n", num_events);
        for (int i = 0; i < num_events; i++) // 이번에 생성할 이벤트의 갯수만큼 반복
        {
            pEv = removeMinPriQ_Event(PriQ_Ev); // 우선순위가 가장높은 데이터를 PriQ_Ev에서 빼온뒤 pEv에 저장한다
            if (pEv == NULL)
            {
                fprintf(fout, " PriQ is empty\n");
                break;
            }
            fprintf(fout, " *** dequeued event : ");
            fprintEvent(fout, pEv);
            fprintPriQ_Event(fout, PriQ_Ev);
            processed_events++; // 처리된 이벤트의 갯수를 1늘려준다
        }
        /* Monitoring simulation status */
        fprintf(fout, "\nRound(%2d): total_generated_events(%3d), total_processed_events(%3d),PriQ capacity(% 2d), events_in_PriQ(% 3d)\n", round, generated_events, processed_events,PriQ_Ev->priQ_capacity, PriQ_Ev->priQ_size);
        fflush(fout); // 출력 버퍼를 비운다 
        if (processed_events >= TOTAL_NUM_EVENTS)
            break; // 마찬가지로 처리된 이벤트가 총 이벤트의 갯수보다 같거나 커지면 반복문을 끝낸다
    }
    deletePriQ_Event(PriQ_Ev);
    fprintf(fout, "\n");
    fclose(fout);
}
