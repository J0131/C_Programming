#include "Event.h"
Event::Event(int evt_no, int evt_pri,string title, int evtGenAddr)
{
	event_no = evt_no;
	event_gen_addr = evtGenAddr;
	event_title = title;
	event_handler_addr = -1; // event handler is not defined at this moment
	event_pri = evt_pri; // event_priority
	eventStatus = GENERATED;
}
Event* genRandEvent(int evt_no)
{
	Event* pEv;
	int evt_prio;
	int evt_generator_id;
	evt_prio = rand() % MAX_EVENT_PRIORITY;
	evt_generator_id = rand() % NUM_EVENT_GENERATORS;
	pEv = (Event*) new Event(evt_no, evt_prio,"title", evt_generator_id);
	return pEv;
}
void Event::printEvent(ostream& fout)
{
	fout << "Event(pri:" << setw(3) << event_pri << ", gen:" << setw(3) << event_gen_addr;
	fout << ", no:" << setw(3) << event_no << ")";
}
ostream& operator<<(ostream& fout, const Event& evt)
{
	fout << "Event(no:" << setw(3) << evt.event_no << ", pri:" << setw(3) << evt.event_pri;
	fout << ", gen:" << setw(3) << evt.event_gen_addr << ", title:" << setw(3) << evt.event_title << ")";
	return fout;
}