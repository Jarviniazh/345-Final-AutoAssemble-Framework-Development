#include <iostream>
#include <algorithm>
#include "Workstation.h"

namespace seneca
{
	//m_orders push_back and pop_front

	//a custom 1-argument constructor
	Workstation::Workstation(const std::string& str) : Station(str) {};

	//this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	// attempts to move the order order at the front of the queue to the next station in the assembly line
	bool Workstation::attemptToMoveOrder()
	{
		if (m_orders.empty()) 
			return false;

		bool moved{false};
		CustomerOrder& order = m_orders.front();

		//if the order requires no more service at this station or cannot be filled (not enough inventory), move it to the next station
		if(order.isItemFilled(getItemName()) || getQuantity() == 0)
		{
			if(m_pNextStation != nullptr)
			{
				*m_pNextStation += std::move(order);
				m_orders.pop_front();
				moved = true;
			}
			else
			{
				if(order.isOrderFilled())
				{
					g_completed.push_back(std::move(order));
					m_orders.pop_front();
				}
				else
				{
					g_incomplete.push_back(std::move(order));
					m_orders.pop_front();
				}
			}
		}
		return moved;
	}

	//stores the address of the referenced Workstation object in the pointer to the m_pNextStation
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	//returns the address of next Workstation
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	//inserts the name of the Item for which the current object is responsible into stream os
	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation != nullptr)
		{
			os << getItemName() << " --> " << m_pNextStation->getItemName() << "\n";
		}
		else
		{
			os << getItemName() << " --> End of Line" << "\n";
		}
	}

	//moves the CustomerOrder referenced in parameter newOrder to the back of the queue
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}