#ifndef PRODUCT_H
#define PRODUCT_H

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
#include <sstream>
using namespace std;

class Product {
private:
    int ProductID; // Product's ID number
    string pName;   // Product's name
    string category; // Product's Category
    string supplier; // Product's Supplier
    double price;   // Product's price

    // Helper function used to make sure the double.toString has
    // precise enough numbers. 2 decimals in this case.
    string to_string_with_precision(const double value) {
        std::ostringstream out;
        out.precision(2);
        out << fixed << value;
        return std::move(out).str();
    }
public:
    // Constructor
    Product(int ProductID, const string &pName, const string &category, const string &supplier, double price);

    // Getters and Setters
    int getProductID() const;
    void setProductID(int newProductID);
    string getPName() const;
    void setPName(const string &newPName);
    string getCategory() const;
    void setCategory(const string &newCategory);
    string getSupplier() const;
    void setSupplier(const string &newSupplier);
    double getPrice() const;
    void setPrice(double newPrice);

    // Misc. Functions
    string toString();

    // Operator Overrides
    bool operator<(const Product& other) const {
        return ProductID < other.getProductID();
    }
    bool operator==(const Product& other) const {
        return (ProductID == other.getProductID()
                && pName == other.getPName()
                && category == other.getCategory()
                && supplier == other.getSupplier()
                && price == other.getPrice());
    }
};

#endif // PRODUCT_H
