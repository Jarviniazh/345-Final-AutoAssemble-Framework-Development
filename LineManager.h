#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

namespace seneca
{
	class LineManager
	{
		std::vector<Workstation*> m_activeLine{}; //the collection of workstations for the current assembly line.
		size_t m_cntCustomerOrder{};  //the total number of CustomerOrder objects
		Workstation* m_firstStation{}; // points to the first active station on the current line
	public:
		LineManager() {};
		//this constructor receives the name of the file that identifies the active stations on the assembly line and the collection of workstations available for configuring the assembly line.
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		//this modifier reorders the workstations present in the instance variable m_activeLine(loaded by the constructor) and stores the reordered collection in the same instance variable.
		void reorderStations();
		// this modifier performs one iteration of operations on all of the workstations in the current assembly line
		bool run(std::ostream& os);
		// this query displays all active stations on the assembly line in their current order
		void display(std::ostream& os) const; 
	};
}

#endif
