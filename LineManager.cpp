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

        while (std::getline(ofile, line)) 
        {
            Utilities util;
            size_t next_pos{};
            bool more = true;

            std::string firstStationName = util.extractToken(line, next_pos, more);
            if (!more) 
            { 
                // end station
                for (auto& ws : stations) 
                {
                    if (ws->getItemName() == firstStationName) 
                    {
                        endStations.push_back(ws);
                        m_activeLine.push_back(ws);
                        break;
                    }
                }
                continue; 
            }

            std::string nextStationName = util.extractToken(line, next_pos, more);
            Workstation* firstStation = nullptr;
            Workstation* nextStation = nullptr;

            // Find the matching workstations in the vector
            for (auto& ws : stations) 
            {
                if (ws->getItemName() == firstStationName)
                {
                    firstStation = ws;
                }
                if (ws->getItemName() == nextStationName) 
                {
                    nextStation = ws;
                }
            }

            if (firstStation && nextStation) 
            {
                firstStation->setNextStation(nextStation);
                m_activeLine.push_back(firstStation);
                nextStations.push_back(nextStation);
            }
        }

        // Check number of end stations
        if (endStations.size() != 1) 
            throw "Multiple end stations detected OR Missing end station";
        

        // Determine the start station
        m_firstStation = nullptr;
        for (auto& station : m_activeLine) 
        {
            if (std::find(nextStations.begin(), nextStations.end(), station) == nextStations.end()) 
            {
                if (m_firstStation != nullptr) 
                {
                    throw "Multiple first stations detected";
                }
                m_firstStation = station;
            }
        }

        if (!m_firstStation) 
        {
            throw "Missing first station";
        }
        m_cntCustomerOrder = g_pending.size();

	}

	//this modifier reorders the workstations present in the instance variable m_activeLine(loaded by the constructor) and stores the reordered collection in the same instance variable.
	void LineManager::reorderStations()
	{
        //start from the first station
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
        for (auto& station : m_activeLine) {
            station->fill(os);
        }

        //for each station on the line, attempts to move an order down the line
        for (auto& station : m_activeLine) {
            station->attemptToMoveOrder();
        }

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
