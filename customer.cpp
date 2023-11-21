#include "customer.h"

Customer::Customer(int CustomerID, const string &fName, const string &lName, const string &email) : CustomerID(CustomerID),
    fName(fName),
    lName(lName),
    email(email)
{}

int Customer::getCustomerID() const
{
    return CustomerID;
}

void Customer::setCustomerID(int newCustomerID)
{
    CustomerID = newCustomerID;
}

string Customer::getFName() const
{
    return fName;
}

void Customer::setFName(const string &newFName)
{
    fName = newFName;
}

string Customer::getLName() const
{
    return lName;
}

void Customer::setLName(const string &newLName)
{
    lName = newLName;
}

string Customer::getEmail() const
{
    return email;
}

void Customer::setEmail(const string &newEmail)
{
    email = newEmail;
}

string Customer::toString() {
    string customerStr = "";
    customerStr += to_string(CustomerID) + ",";
    customerStr += fName + "," + lName + ",";
    customerStr += email;
    return customerStr;
}



