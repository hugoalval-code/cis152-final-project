#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

int PIDCOUNTER = 1001;

class Product {
private:
    int ProductID;
    std::string pName;
    std::string category;
    std::string supplier;
    double price;
public:
    // Constructor
    Product(std::string pName, std::string category, std::string supplier, double price) {
        ProductID = PIDCOUNTER;
        PIDCOUNTER++;
        this->pName = pName;
        this->category = category;
        this->supplier = supplier;
        this->price = price;
    }
    // Getters and Setters
    void setProductName(std::string pName) {this->pName = pName;}
    void setCategory(std::string category) {this->category = category;}
    void setSupplier(std::string supplier) {this->supplier = supplier;}
    void setPrice(double price) {this->price = price;}
    std::string getProductName() {return pName;}
    std::string getCategory() {return category;}
    std::string getSupplier() {return supplier;}
    int getProductID() {return ProductID;}
    double getPrice() {return price;}
    // Misc.
    std::string toString() {
        std::string str = "";
        str += "PID: " + std::to_string(ProductID) + ", ";
        str += "Name: " + pName + ", ";
        str += "Price: " + std::to_string(price) + ", ";
        str += "Category: " + category + ", ";
        str += "Supplier: " + supplier + ", ";
        return str;
    }
};

#endif // PRODUCT_H
