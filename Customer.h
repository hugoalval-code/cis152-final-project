#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

int CIDCOUNTER = 3001;

class Customer {
private:
    int CustomerID;
    std::string fName;
    std::string lName;
    std::string email;

public:
    // Constructor
    Customer(std::string fName, std::string lName, std::string email) :
        fName(fName), lName(lName), email(email) {
        CustomerID = CIDCOUNTER;
        CIDCOUNTER++;
    }
    // Getters and Setters
    void setFirstName(std::string fName) {this->fName = fName;}
    void setLastName(std::string lName) {this->lName = lName;}
    void setEmail(std::string email) {this->email = email;}
    int getCustomerID() {return CustomerID;}
    std::string getFirstName() {return fName;}
    std::string getLastName() {return lName;}
    std::string getEmail() {return email;}
    // Misc.
    std::string toString() {
        std::string str = "";
        str += "CID: " + std::to_string(CustomerID) + ", ";
        str += "Name: " + fName + " " + lName + ", ";
        str += "Email: " + email;
        return str;
    }
};

#endif // CUSTOMER_H
