
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

#include "order.h"

// CONSTRUCTOR
Order::Order(int oid, int cid, int pid, string purchaseDate) {
    OrderID = oid;
    CustomerID = cid;
    ProductID = pid;
    PurchasedDate = purchaseDate;
}

// --------------------------------------------------------------
// GETTERS AND SETTERS
int Order::getOrderID() const {
    return OrderID;
}

void Order::setOrderID(int newOrderID) {
    OrderID = newOrderID;
}

int Order::getCustomerID() const {
    return CustomerID;
}

void Order::setCustomerID(int newCustomerID) {
    CustomerID = newCustomerID;
}

int Order::getProductID() const {
    return ProductID;
}

void Order::setProductID(int newProductID) {
    ProductID = newProductID;
}

string Order::getPurchasedDate() const {
    return PurchasedDate;
}

void Order::setPurchasedDate(const string &newPurchasedDate) {
    PurchasedDate = newPurchasedDate;
}
// --------------------------------------------------------------

/**
 * @brief This function converts an order's data into
 * a formatted string that is separated by commas, which
 * facilitates input into CSV file.
 *
 * @returns comma-separated string with order's data.
 */
string Order::toString() {
    string orderStr = "";
    orderStr += to_string(OrderID) + ",";
    orderStr += to_string(CustomerID) + ",";
    orderStr += to_string(ProductID) + ",";
    orderStr += PurchasedDate;
    return orderStr;
}

