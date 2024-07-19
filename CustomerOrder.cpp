#include <iostream>
#include <string>
#include <exception>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca{
    size_t m_widthField{}; // the maximum width of a field, used for display purposes

    //a custom 1-argument constructor that takes a reference to an unmodifiable string.
    CustomerOrder::CustomerOrder(const std::string&){
        //uses a local Utilities object to extract the tokens from the string
    }
    //a CustomerOrder object should not allow copy operations. The copy constructor should throw an exception if called and the copy operator= should be deleted.
    CustomerOrder::CustomerOrder(const CustomerOrder&){

    }

    //a move constructor. This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
    CustomerOrder::CustomerOrder(CustomerOrder&&) noexcept{

    }

    //a move assignment operator. This operator should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&&) noexcept{

    }
    //a destructor
    CustomerOrder::~CustomerOrder(){

    }

    //returns true if all the items in the order have been filled; false otherwise
    bool CustomerOrder::isOrderFilled() const{

    }

    //returns true if all items specified by itemName have been filled.
    bool CustomerOrder::isItemFilled(const std::string& itemName) const{

    }

    //this modifier fills one item in the current order that the Station specified in the first parameter handles.
    void CustomerOrder::fillItem(Station& station, std::ostream& os){

    }

    //this query displays the state of the current object in the format
    void CustomerOrder::display(std::ostream& os) const{

    }
}