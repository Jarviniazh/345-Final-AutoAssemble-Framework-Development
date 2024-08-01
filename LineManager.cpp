#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace seneca
{
	//this constructor receives the name of the file that identifies the active stations on the assembly line and the collection of workstations available for configuring the assembly line.
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream ofile(file);
		if (!ofile)
			throw "Failed to open the file: " + file;

        std::string line{};
        std::vector<Workstation*> nextStations{};
        std::vector<Workstation*> endStations{}; 

        //loads the contents of the file
        while (std::getline(ofile, line)) 
        {
            Utilities util;
            size_t next_pos{};
            bool more = true;

            std::string firstStationName = util.extractToken(line, next_pos, more);
            //if it is the last station
			if (!more) 
            { 
                auto it = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getItemName() == firstStationName;
                    });

                if (it != stations.end()) 
                {
                    endStations.push_back(*it);
                    m_activeLine.push_back(*it);
                }

            }
            else
            {
	            std::string nextStationName = util.extractToken(line, next_pos, more);
				Workstation* firstStation = nullptr;
				Workstation* nextStation = nullptr;

                std::for_each(stations.begin(), stations.end(), [&](Workstation* station)
                    {
                        if (station->getItemName() == firstStationName)
                            firstStation = station;
                        else if (station->getItemName() == nextStationName)
                            nextStation = station;
                    });

                //stores the address of the next workstation in each element of the collection
                if (firstStation && nextStation)
                {
                    firstStation->setNextStation(nextStation);
                    m_activeLine.push_back(firstStation);
                    nextStations.push_back(nextStation);
                }
            }
        }

        // Check number of end stations
        if (endStations.size() != 1) 
            throw "Multiple end stations detected OR Missing the end station";

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
            if (std::find(nextStations.begin(), nextStations.end(), station) == nextStations.end()) {
                if (m_firstStation != nullptr) {
                    throw "Multiple first stations detected";
                }
                m_firstStation = station;
            }
            });

        if (m_firstStation == nullptr) 
            throw "Missing the first station";

        //This function also updates the attribute that holds the total number of orders in the g_pending queue.
        m_cntCustomerOrder = g_pending.size();
	}

	//this modifier reorders the workstations present in the instance variable m_activeLine(loaded by the constructor) and stores the reordered collection in the same instance variable.
	void LineManager::reorderStations()
	{
        //start with the first station
		Workstation* currentStation = m_firstStation;
        std::vector<Workstation*> orderedStations;

        while (currentStation != nullptr) {
            orderedStations.push_back(currentStation);
            currentStation = currentStation->getNextStation();  
        }

        m_activeLine = orderedStations;
	}

	// this modifier performs one iteration of operations on all of the workstations in the current assembly line
	bool LineManager::run(std::ostream& os)
	{
        //keeps track of the current iteration number(use a local variable)
		static size_t count = 1; 

        //inserts into stream os the iteration number
        os << "Line Manager Iteration: " << count++ << std::endl; 

        //moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue. 
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front()); 
            g_pending.pop_front(); 
        }

        //for each station on the line, executes one fill operation
        for (auto& station : m_activeLine) 
            station->fill(os);

        //for each station on the line, attempts to move an order down the line
        for (auto& station : m_activeLine) 
            station->attemptToMoveOrder();

        //std::cout << "incompleted: " << g_incomplete.size() << std::endl;
        //std::cout << "completed: " << g_completed.size() << std::endl;
        //std::cout << "order received: " << m_cntCustomerOrder << std::endl;

        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }

	// this query displays all active stations on the assembly line in their current order
	void LineManager::display(std::ostream& os) const
	{
		for(auto& station : m_activeLine)
			station->display(os);
	}
}
