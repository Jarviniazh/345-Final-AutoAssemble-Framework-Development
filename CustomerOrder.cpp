#include <iostream>
#include <string>
#include <exception>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca{
    size_t CustomerOrder::m_widthField{}; // the maximum width of a field, used for display purposes

    //a custom 1-argument constructor that takes a reference to an unmodifiable string.
    CustomerOrder::CustomerOrder(const std::string& order){
        //uses a local Utilities object to extract the tokens from the string
        Utilities util{};
        size_t next_pos{};
        bool more{};
        m_name = util.extractToken(order, next_pos, more);
        m_product = util.extractToken(order, next_pos, more);
        m_cntItem = std::count_if(order.begin(), order.end(), [=](char c){return c == util.getDelimiter();}) - 1;
        m_lstItem = new Item*[m_cntItem];
        for(auto i = 0u; i < m_cntItem; ++i)
            m_lstItem[i] = new Item(util.extractToken(order, next_pos, more));

        if (m_widthField < util.getFieldWidth())
            m_widthField = util.getFieldWidth();
    }

    //a CustomerOrder object should not allow copy operations. The copy constructor should throw an exception if called and the copy operator= should be deleted.
    CustomerOrder::CustomerOrder(const CustomerOrder& source){
        throw "Copy operations are not allowed";
    }

    //a move constructor. This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
    CustomerOrder::CustomerOrder(CustomerOrder&& source) noexcept{
        *this = std::move(source);
    }

    //a move assignment operator. This operator should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& source) noexcept{
        if (this != &source) {
        	for (auto i = 0u; i < m_cntItem; ++i)
	            delete m_lstItem[i];
        	delete[] m_lstItem;

        	m_name = source.m_name;
            source.m_name = "";

            m_product = source.m_product;
            source.m_product = "";

            m_cntItem = source.m_cntItem;
            source.m_cntItem = 0u;

            m_lstItem = source.m_lstItem;
            source.m_lstItem = nullptr;
        }
        return *this;
    }

    //a destructor
    CustomerOrder::~CustomerOrder(){
        for (auto i = 0u; i < m_cntItem; ++i)
        	delete m_lstItem[i];
        
        delete [] m_lstItem;
    }

    //returns true if all the items in the order have been filled; false otherwise
    bool CustomerOrder::isOrderFilled() const{
        for (auto i = 0u; i < m_cntItem; ++i)
        {
            if(!m_lstItem[i]->m_isFilled)
                return false;
        }
        return true;
    }

    //returns true if all items specified by itemName have been filled.
    bool CustomerOrder::isItemFilled(const std::string& itemName) const{
        for (auto i = 0u; i < m_cntItem; ++i)
        {
            if(m_lstItem[i]->m_itemName == itemName)
            {
            	if (!m_lstItem[i]->m_isFilled)
					return false;
            }
        }
        return true;
    }

    //this modifier fills one item in the current order that the Station specified in the first parameter handles.
    void CustomerOrder::fillItem(Station& station, std::ostream& os){
        for(auto i = 0u; i < m_cntItem; ++i)
		{
            //if the order doesn't contain the item handled, this function does nothing
        	if(m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)
			{
                //if the order contains items handled, and the Station's inventory contains at least one item
        		if(station.getQuantity() > 0)
				{
					station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;
				}
				else
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				
			}
		}
    }

    //this query displays the state of the current object in the format
    void CustomerOrder::display(std::ostream& os) const{
        os << m_name << " - " << m_product << std::endl;
        for(auto i = 0u; i < m_cntItem; ++i)
        {
	        os << "[" << std::setw(6) << std::right << std::setfill('0')<< m_lstItem[i]->m_serialNumber << "] " << std::setw(m_widthField)
        		<< std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";

            if(m_lstItem[i]->m_isFilled)
			{
				os << "FILLED" << std::endl;
			}
			else
			{
				os << "TO BE FILLED" << std::endl;
			}
        }
        
    }
}