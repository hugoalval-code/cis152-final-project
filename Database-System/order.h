#ifndef ORDER_H
#define ORDER_H

/***************************************************************
* Name : Final Project
* Author: Hugo Alvarez Valdivia
* Course: CIS 152 - Data Structures
* Version: 1.0
* OS: Mac OSX
* IDE: QT
* Copyright : This is my own original work
* based on specifications issued by our instructor
* Description : Database system to manage a business' customers,
*               products, as well as order tracking.
* Academic Honesty: I attest that this is my original work.
* I have not used unauthorized source code, either modified or
* unmodified. I have not given other fellow student(s) access
* to my program.
***************************************************************/

#include <string>
using namespace std;

class Order {
private:
    int OrderID;    // Order's ID number
    int CustomerID; // Customer's ID number
    int ProductID;  // Product's ID number
    string PurchasedDate;   // Date the order was made
public:
    // Constructor
    Order(int oid, int cid, int pid, string purchasedDate);

    // Getters and Setters
    int getOrderID() const;
    void setOrderID(int newOrderID);
    int getCustomerID() const;
    void setCustomerID(int newCustomerID);
    int getProductID() const;
    void setProductID(int newProductID);
    string getPurchasedDate() const;
    void setPurchasedDate(const string &newPurchasedDate);

    // Misc. Functions
    string toString();

    // Operator Overrides
    bool operator<(const Order& other) const {
        return OrderID < other.getOrderID();
    }
    bool operator==(const Order& other) const {
        return (OrderID == other.getOrderID()
                && CustomerID == other.CustomerID
                && ProductID == other.getProductID()
                && PurchasedDate == other.getPurchasedDate());
    }
};

#endif // ORDER_H
