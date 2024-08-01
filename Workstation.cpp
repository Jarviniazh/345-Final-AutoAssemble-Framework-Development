#include <iostream>

#include "Workstation.h"

namespace seneca
{
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	//a custom 1-argument constructor
	Workstation::Workstation(const std::string& str) : Station(str) {};

	//this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
			m_orders.front().fillItem(*this, os);
	}

	// attempts to move the order order at the front of the queue to the next station in the assembly line
	bool Workstation::attemptToMoveOrder()
	{
		bool moved{false};

		if (!m_orders.empty())
		{
			CustomerOrder& order = m_orders.front();
			//if the order requires no more service at this station or cannot be filled (not enough inventory), move it to the next station
			if(order.isItemFilled(getItemName()) || getQuantity() == 0)
			{
				if(m_pNextStation != nullptr)
					*m_pNextStation += std::move(order);
				//if there is no next station in the assembly line, then the order is moved into g_completed or g_incomplete queue
				else
				{
					if(order.isOrderFilled())
						g_completed.push_back(std::move(order));
					else
						g_incomplete.push_back(std::move(order));
				}

				m_orders.pop_front();
				moved = true;
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
		os << getItemName() << " --> ";
		if (m_pNextStation != nullptr)
			os << m_pNextStation->getItemName() << "\n";
		//if the current object is the last Workstation in the assembly line this query inserts
		else
			os << "End of Line\n";
	}

	//moves the CustomerOrder referenced in parameter newOrder to the back of the queue
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}