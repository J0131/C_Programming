#include "Event.h"
#include <Windows.h>
#include <time.h>
Event::Event()
{
	event_no = 0;
	event_gen_addr = 0;
	event_handler_addr = 0; // �ּ�
	event_pri = 0; // �켱����
}
Event::Event(int evt_no, int evt_pri, int evtGenAddr)
{
	event_no = evt_no;
	event_gen_addr = evtGenAddr;
	event_handler_addr = -1; // �ּ�
	event_pri = evt_pri; // �켱����
	eventStatus = GENERATED;
}
Event* genRandEvent(int evt_no)
{
	Event* pEv;
	int evt_prio;
	int evt_generator_id;
	evt_prio = rand() % MAX_EVENT_PRIORITY;
	evt_generator_id = rand() % NUM_EVENT_GENERATORS;
	pEv = (Event*) new Event(evt_no, evt_prio, evt_generator_id);
	return pEv;
} // �̺�Ʈ�� �������� ����
void Event::printEvent_proc()
{
	cout << "Ev(no:" << setw(2) << event_no << ", pri:" << setw(3) << event_pri;
	cout << ", t_elapsed:" << setw(8) << t_elapsed_time_ms << ") ";
} // ȭ�鿡 �̺�Ʈ�� ����ϴ� �Լ�
ostream& operator<<(ostream& fout, const Event& evt)
{
	fout << "Event(no:" << setw(3) << evt.event_no << ", pri:" << setw(3) << evt.event_pri;
	fout << ")";
	return fout;
} // ȭ�鿡 �̺�Ʈ�� ����ϴ� ������ �����ε�


