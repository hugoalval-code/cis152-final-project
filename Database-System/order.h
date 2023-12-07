#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

class Order {
private:
    int OrderID;
    int CustomerID;
    int ProductID;
    string PurchasedDate;
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
