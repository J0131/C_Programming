#include "Event.h"
#define QUEUE_CAPACITY 10
#define EVENT_GENERATOR 0
#define TOTAL_NUM_EVENTS 50
#define MAX_EVENTS_PER_ROUND 5
#define MAX_ROUND 100 
typedef struct
{
    Event* pEv; // �̺�Ʈ�� ������ ť
    int capacity;
    int front;
    int end;
    int num_elements;
} CircularQueue; // ���θ���� �̺�Ʈ�迭�� ������ CircularQueue����ü ����
CircularQueue* initCirQueue(CircularQueue* pCirQ, int capacity); // CircularQueue�������� pCirQ�� �ʱ�ȭ���ִ� �Լ�
void printCirQueue(CircularQueue* cirQ); // CircularQueue�������� cirQ�� ȭ�鿡 ����ϴ� �Լ�
void fprintCirQueue(FILE* fout, CircularQueue* cirQ); //CircularQueue�������� cirQ�� ���Ͽ� ����ϴ� �Լ�
bool isCirQueueFull(CircularQueue* cirQ); // CircularQueue�������� cirQ�� �����Ͱ� �������ִ��� Ȯ���ϴ� �Լ�
bool isCirQueueEmpty(CircularQueue* cirQ); // CircularQueue�������� cirQ�� �����Ͱ� ����ִ��� Ȯ���ϴ� �Լ�
Event* enCirQueue(FILE* fout, CircularQueue* cirQ, Event ev); // CircularQueue�������� cirQ�� �̺�Ʈ�� ����ִ� �Լ�
Event* deCirQueue(FILE* fout, CircularQueue* cirQ); // CircularQueue�������� cirQ���� �̺�Ʈ�� ���� �Լ�
void delCirQueue(CircularQueue* cirQ); // CircularQueue�������� cirQ�� �����͸� �����ϴ� �Լ�
