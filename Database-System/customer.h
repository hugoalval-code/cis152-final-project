#ifndef CUSTOMER_H
#define CUSTOMER_H

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

/*
 * Implementation of a Customer class.
 */
class Customer {
private:
    int CustomerID; // Customer's ID number
    string fName;   // Customer's First Name
    string lName;   // Customer's Last Name
    string email;   // Customer's Email
public:
    // Constructor
    Customer(int CustomerID, const string &fName, const string &lName, const string &email);

    // Getters and Setters
    int getCustomerID() const;
    void setCustomerID(int newCustomerID);
    string getFName() const;
    void setFName(const string &newFName);
    string getLName() const;
    void setLName(const string &newLName);
    string getEmail() const;
    void setEmail(const string &newEmail);

    // Misc Functions
    string toString();

    // Operator Overrides
    bool operator<(const Customer& other) const {
        return CustomerID < other.getCustomerID();
    }
    bool operator==(const Customer& other) const {
        return (CustomerID == other.getCustomerID()
                && fName == other.getFName()
                && lName == other.getLName()
                && email == other.getEmail());
    }
};

#endif // CUSTOMER_H
