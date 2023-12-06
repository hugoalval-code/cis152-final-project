#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer {
private:
    int CustomerID;
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
    bool operator<(const Customer& other) const {
        return CustomerID < other.getCustomerID();
    }
};

#endif // CUSTOMER_H
