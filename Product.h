#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <sstream>
using namespace std;

class Product {
private:
    int ProductID;
    string pName;
    string category;
    string supplier;
    double price;

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

    // Misc Functions
    string toString();
    bool operator<(const Product& other) const {
        return ProductID < other.getProductID();
    }
};

#endif // PRODUCT_H
