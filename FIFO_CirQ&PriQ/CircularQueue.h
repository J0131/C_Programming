#include "Event.h"
#define QUEUE_CAPACITY 10
#define EVENT_GENERATOR 0
#define TOTAL_NUM_EVENTS 50
#define MAX_EVENTS_PER_ROUND 5
#define MAX_ROUND 100 
typedef struct
{
    Event* pEv; // 이벤트를 저장할 큐
    int capacity;
    int front;
    int end;
    int num_elements;
} CircularQueue; // 내부멤버로 이벤트배열을 가지는 CircularQueue구조체 선언
CircularQueue* initCirQueue(CircularQueue* pCirQ, int capacity); // CircularQueue포인터형 pCirQ을 초기화해주는 함수
void printCirQueue(CircularQueue* cirQ); // CircularQueue포인터형 cirQ을 화면에 출력하는 함수
void fprintCirQueue(FILE* fout, CircularQueue* cirQ); //CircularQueue포인터형 cirQ를 파일에 출력하는 함수
bool isCirQueueFull(CircularQueue* cirQ); // CircularQueue포인터형 cirQ에 데이터가 가득차있는지 확인하는 함수
bool isCirQueueEmpty(CircularQueue* cirQ); // CircularQueue포인터형 cirQ에 데이터가 비어있는지 확인하는 함수
Event* enCirQueue(FILE* fout, CircularQueue* cirQ, Event ev); // CircularQueue포인터형 cirQ에 이벤트를 집어넣는 함수
Event* deCirQueue(FILE* fout, CircularQueue* cirQ); // CircularQueue포인터형 cirQ에서 이벤트를 빼는 함수
void delCirQueue(CircularQueue* cirQ); // CircularQueue포인터형 cirQ의 데이터를 삭제하는 함수
