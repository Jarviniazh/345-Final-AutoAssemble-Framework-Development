// Name: Jarvinia Zhao
// Seneca Student ID: 143013233
// Seneca email: jzhao169@myseneca.ca
// Date of completion: 2024-07-13
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca
{
	size_t Station::m_widthField{}; //the maximum number of characters required to print to the screen
	int Station::id_generator{};

	//custom 1-argument constructor
	Station::Station(const std::string& record)
	{
		//this constructor uses a Utilities object(defined locally) to extract each token from the record and populates the Station object accordingly.
		Utilities util;
		size_t next_pos{};
		bool more{};
		//this constructor extracts name, starting serial number, and quantity from the string first
		m_name = util.extractToken(record, next_pos, more);
		m_serial = std::stoul(util.extractToken(record, next_pos, more));
		m_stock = std::stoul(util.extractToken(record, next_pos, more));
		
		//before extracting description, it updates Station::m_widthField to the maximum value of Station::m_widthField and Utilities::m_widthField.
		if(m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();

		m_description = util.extractToken(record, next_pos, more);
		m_id = ++id_generator;
	}

	//returns the name of the current Station object
	const std::string& Station::getItemName() const
	{
		return m_name;
	}

	// returns the next serial number to be used on the assembly line and increments m_serialNumber
	size_t Station::getNextSerialNumber()
	{
		return m_serial++;
	}

	// returns the remaining quantity of items in the Station object
	size_t Station::getQuantity() const
	{
		return m_stock;
	}

	//subtracts 1 from the available quantity; should not drop below 0.
	void Station::updateQuantity()
	{
		if (m_stock > 0)
			m_stock--;
	}

	//inserts information about the current object into stream os.
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setw(3) << std::right << std::setfill('0') << m_id << " | "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | "
			<< std::setw(6) << std::setfill('0') << std::right << m_serial << " | " << std::setfill(' ');

		if(full)
		{
			os << std::setw(4) << m_stock << " | " << m_description;
		}
		os << std::endl;
	}
}
