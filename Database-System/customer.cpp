
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

#include "customer.h"

// CONSTRUCTOR
Customer::Customer(int CustomerID, const string &fName, const string &lName, const string &email) : CustomerID(CustomerID),
    fName(fName),
    lName(lName),
    email(email)
{}

// -----------------------------------------------
// GETTERS AND SETTERS
int Customer::getCustomerID() const {
    return CustomerID;
}

void Customer::setCustomerID(int newCustomerID) {
    CustomerID = newCustomerID;
}

string Customer::getFName() const {
    return fName;
}

void Customer::setFName(const string &newFName) {
    fName = newFName;
}

string Customer::getLName() const {
    return lName;
}

void Customer::setLName(const string &newLName) {
    lName = newLName;
}

string Customer::getEmail() const {
    return email;
}

void Customer::setEmail(const string &newEmail) {
    email = newEmail;
}
// -----------------------------------------------

/**
 * @brief This function converts a customer's data into
 * a formatted string that is separated by commas, which
 * facilitates input into CSV file.
 *
 * @returns comma-separated string with customer's data.
 */
string Customer::toString() {
    string customerStr = "";
    customerStr += to_string(CustomerID) + ",";
    customerStr += fName + "," + lName + ",";
    customerStr += email;
    return customerStr;
}



