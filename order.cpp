#include "order.h"

Order::Order(int oid, int cid, int pid, string purchaseDate) {
    OrderID = oid;
    CustomerID = cid;
    ProductID = pid;
    PurchasedDate = purchaseDate;
}

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

int Order::getProductIDs() const {
    return ProductID;
}

void Order::setProductID(int &newProductID) {
    ProductID = newProductID;
}

string Order::getPurchasedDate() const {
    return PurchasedDate;
}

void Order::setPurchasedDate(const string &newPurchasedDate) {
    PurchasedDate = newPurchasedDate;
}

string Order::toString() {
    string orderStr = "";
    orderStr += to_string(OrderID) + ",";
    orderStr += to_string(CustomerID) + ",";
    orderStr += to_string(ProductID) + ",";
    orderStr += PurchasedDate;
    return orderStr;
}

