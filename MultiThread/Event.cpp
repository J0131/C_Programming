#include "Event.h"
#include <Windows.h>
#include <time.h>
Event::Event()
{
	event_no = 0;
	event_gen_addr = 0;
	event_handler_addr = 0; // 주소
	event_pri = 0; // 우선순위
}
Event::Event(int evt_no, int evt_pri, int evtGenAddr)
{
	event_no = evt_no;
	event_gen_addr = evtGenAddr;
	event_handler_addr = -1; // 주소
	event_pri = evt_pri; // 우선순위
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
} // 이벤트를 랜덤으로 생성
void Event::printEvent_proc()
{
	cout << "Ev(no:" << setw(2) << event_no << ", pri:" << setw(3) << event_pri;
	cout << ", t_elapsed:" << setw(8) << t_elapsed_time_ms << ") ";
} // 화면에 이벤트를 출력하는 함수
ostream& operator<<(ostream& fout, const Event& evt)
{
	fout << "Event(no:" << setw(3) << evt.event_no << ", pri:" << setw(3) << evt.event_pri;
	fout << ")";
	return fout;
} // 화면에 이벤트를 출력하는 연산자 오버로딩


