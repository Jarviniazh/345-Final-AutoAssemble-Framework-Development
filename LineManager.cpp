#include <iostream>

#include "LineManager.h"

namespace seneca
{
	//this constructor receives the name of the file that identifies the active stations on the assembly line and the collection of workstations available for configuring the assembly line.
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		
	}

	//this modifier reorders the workstations present in the instance variable m_activeLine(loaded by the constructor) and stores the reordered collection in the same instance variable.
	void LineManager::reorderStations()
	{
		
	}

	// this modifier performs one iteration of operations on all of the workstations in the current assembly line
	bool LineManager::run(std::ostream& os)
	{
		
	}

	// this query displays all active stations on the assembly line in their current order
	void LineManager::display(std::ostream& os) const
	{
		
	}
}
