#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca
{
	extern std::deque<CustomerOrder> g_pending; //the orders to be placed onto the assembly line at the first station.
	extern std::deque<CustomerOrder> g_completed; //the orders that have been removed from the last station and have been completely filled
	extern std::deque<CustomerOrder> g_incomplete; //the orders that have been removed from the last station and could not be filled completely


	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders{}; //These are orders that have been placed on this station to receive service (or already received service).
		Workstation* m_pNextStation{}; //a pointer to the next Workstation on the assembly line.
	public:
		Workstation() {};
		//a custom 1-argument constructor
		Workstation(const std::string&);
		//the object cannot be copied or moved
		Workstation(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation& operator=(Workstation&&) = delete;
		//this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
		void fill(std::ostream& os);
		// attempts to move the order order at the front of the queue to the next station in the assembly line
		bool attemptToMoveOrder();
		//stores the address of the referenced Workstation object in the pointer to the m_pNextStation
		void setNextStation(Workstation* station = nullptr);
		//returns the address of next Workstation
		Workstation* getNextStation() const;
		//inserts the name of the Item for which the current object is responsible into stream os
		void display(std::ostream& os) const;
		//moves the CustomerOrder referenced in parameter newOrder to the back of the queue
		Workstation& operator+=(CustomerOrder&& newOrder);
		
	};
}

#endif
