
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

namespace seneca
{
	class Station
	{
		int m_id{};//the id of the station(integer)
		std::string m_name{};//the name of the item handled by the station(string)
		std::string m_description{}; //the description of the station(string)
		size_t m_serial{}; //the next serial number to be assigned to an item at this station(non - negative integer)
		size_t m_stock{};//the number of items currently in stock(non - negative integer)

		//class variable
		static size_t m_widthField; //the maximum number of characters required to print to the screen
		static int id_generator; //used to generate IDs for new instances of type Station

	public:
		Station() {};
		//custom 1-argument constructor
		Station(const std::string&);
		//returns the name of the current Station object
		const std::string& getItemName() const;
		// returns the next serial number to be used on the assembly line and increments m_serialNumber
		size_t getNextSerialNumber();
		// returns the remaining quantity of items in the Station object
		size_t getQuantity() const;
		//subtracts 1 from the available quantity; should not drop below 0.
		void updateQuantity();
		//inserts information about the current object into stream os.
		void display(std::ostream& os, bool full) const;
	};
}

#endif

