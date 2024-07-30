#include <iostream>
#include "Workstation.h"

namespace seneca
{
	//a custom 1-argument constructor
	Workstation::Workstation(const std::string&)
	{
		
	}

	//this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
	void Workstation::fill(std::ostream& os)
	{
		
	}

	// attempts to move the order order at the front of the queue to the next station in the assembly line
	bool Workstation::attemptToMoveOrder()
	{
		
	}

	//stores the address of the referenced Workstation object in the pointer to the m_pNextStation
	void Workstation::setNextStation(Workstation* station)
	{
		
	}

	//returns the address of next Workstation
	Workstation* Workstation::getNextStation() const
	{
		
	}

	//inserts the name of the Item for which the current object is responsible into stream os
	void Workstation::display(std::ostream& os) const
	{
		
	}

	//moves the CustomerOrder referenced in parameter newOrder to the back of the queue
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		
	}
}