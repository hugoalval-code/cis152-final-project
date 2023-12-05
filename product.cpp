#include "product.h"

Product::Product(int ProductID, const string &pName, const string &category, const string &supplier, double price) : ProductID(ProductID),
    pName(pName),
    category(category),
    supplier(supplier),
    price(price)
{}

int Product::getProductID() const
{
    return ProductID;
}

void Product::setProductID(int newProductID)
{
    ProductID = newProductID;
}

string Product::getPName() const
{
    return pName;
}

void Product::setPName(const string &newPName)
{
    pName = newPName;
}

string Product::getCategory() const
{
    return category;
}

void Product::setCategory(const string &newCategory)
{
    category = newCategory;
}

string Product::getSupplier() const
{
    return supplier;
}

void Product::setSupplier(const string &newSupplier)
{
    supplier = newSupplier;
}

double Product::getPrice() const
{
    return price;
}

void Product::setPrice(double newPrice)
{
    price = newPrice;
}



string Product::toString() {
    string productStr = "";
    productStr += to_string(ProductID) + ",";
    productStr += pName + ",";
    productStr += category + ",";
    productStr += supplier + ",";
    productStr += to_string_with_precision(price);
    return productStr;
}


