#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace seneca
{
    //std::deque<CustomerOrder> g_pending{};

	//this constructor receives the name of the file that identifies the active stations on the assembly line and the collection of workstations available for configuring the assembly line.
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		//if no next station => bookcase is the end station

		//exception for multiple first stations and multiple last stations
		std::ifstream ofile(file);
		if (!ofile)
			throw "Failed to open the file: " + file;

        std::string line{};
        std::vector<Workstation*> nextStations{};
        std::vector<Workstation*> potentialEndStations{}; // To track end stations

        while (std::getline(ofile, line)) {
            Utilities util;
            size_t next_pos = 0;
            bool more = true;

            std::string firstStationName = util.extractToken(line, next_pos, more);
            if (!more) { // No next station specified, treat as potential end station
                // Find the station and add to potential end stations
                for (auto& ws : stations) {
                    if (ws->getItemName() == firstStationName) {
                        potentialEndStations.push_back(ws);
                        m_activeLine.push_back(ws); // Still add this to activeLine
                        break;
                    }
                }
                continue; // Move to the next line in the file
            }

            std::string nextStationName = util.extractToken(line, next_pos, more);
            Workstation* firstStation = nullptr;
            Workstation* nextStation = nullptr;

            // Find the matching workstations in the vector
            for (auto& ws : stations) {
                if (ws->getItemName() == firstStationName) {
                    firstStation = ws;
                }
                if (ws->getItemName() == nextStationName) {
                    nextStation = ws;
                }
            }

            if (firstStation && nextStation) {
                firstStation->setNextStation(nextStation);
                m_activeLine.push_back(firstStation);
                nextStations.push_back(nextStation);
            }
        }

        // Check for end stations - there should be exactly one
        if (potentialEndStations.size() != 1) {
            throw "Incorrect number of end stations detected: expected 1, found " + std::to_string(potentialEndStations.size());
        }

        // Determine the start station
        m_firstStation = nullptr;
        for (auto& station : m_activeLine) {
            if (std::find(nextStations.begin(), nextStations.end(), station) == nextStations.end()) {
                if (m_firstStation != nullptr) {
                    throw "Multiple first stations detected";
                }
                m_firstStation = station;
            }
        }

        if (!m_firstStation) {
            throw "Missing first station";
        }
	}

	//this modifier reorders the workstations present in the instance variable m_activeLine(loaded by the constructor) and stores the reordered collection in the same instance variable.
	void LineManager::reorderStations()
	{
        // Start from the first station
        Workstation* currentStation = m_firstStation;
        std::vector<Workstation*> reorderedStations;

        // Follow the chain of next stations and add them to the reordered list
        while (currentStation != nullptr) {
            reorderedStations.push_back(currentStation);
            currentStation = currentStation->getNextStation();  // Move to the next station in the line
        }

        // Update m_activeLine with the correctly ordered stations
        m_activeLine = reorderedStations;
	}

	// this modifier performs one iteration of operations on all of the workstations in the current assembly line
	bool LineManager::run(std::ostream& os)
	{
        static size_t iterationCount = 0; 
        iterationCount++;  

        os << "Line Manager Iteration: " << iterationCount << std::endl; 

      
        if (!g_pending.empty()) {
            m_firstStation->operator+=(std::move(g_pending.front())); 
            g_pending.pop_front(); 
        }

        // Execute one fill operation at each station
        for (auto& station : m_activeLine) {
            station->fill(os);
        }

        
        bool allOrdersComplete = true;
        for (auto& station : m_activeLine) {
            if (!station->attemptToMoveOrder()) {
                allOrdersComplete = false; 
            }
        }

        return allOrdersComplete; 
    }

	// this query displays all active stations on the assembly line in their current order
	void LineManager::display(std::ostream& os) const
	{
		for(auto& ws : m_activeLine)
		{
			ws->display(os);
		}
	}
}
