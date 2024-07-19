#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include "Station.h"
namespace seneca{
    class CustomerOrder {
        struct Item
        {
            std::string m_itemName;
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            Item(const std::string& src) : m_itemName(src) {};
        };
        std::string m_name; // the name of the customer (e.g., John, Sara, etc)
        std::string m_product; // the name of the product being assembled (e.g., Desktop, Laptop, etc)
        size_t m_cntItem; //a count of the number of items in the customer's order
        Item** m_lstItem; // a dynamically allocated array of pointers.
        //Class Variable
        static size_t m_widthField; // the maximum width of a field, used for display purposes

    public:
        //default constructor
        CustomerOrder(){};
        //a custom 1-argument constructor that takes a reference to an unmodifiable string.
        CustomerOrder(const std::string&);
        //a CustomerOrder object should not allow copy operations. The copy constructor should throw an exception if called and the copy operator= should be deleted.
        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&) = delete;
        //a move constructor. This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
        CustomerOrder(CustomerOrder&&) noexcept;

        //a move assignment operator. This operator should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
        CustomerOrder& operator=(CustomerOrder&&) noexcept;
        //a destructor
        ~CustomerOrder();

        //returns true if all the items in the order have been filled; false otherwise
        bool isOrderFilled() const;

        //returns true if all items specified by itemName have been filled.
        bool isItemFilled(const std::string& itemName) const;

        //this modifier fills one item in the current order that the Station specified in the first parameter handles.
        void fillItem(Station& station, std::ostream& os);

        //this query displays the state of the current object in the format
        void display(std::ostream& os) const;
    };
}

#endif //SENECA_CUSTOMERORDER_H
