
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

#include "product.h"

// CONSTRUCTOR
Product::Product(int ProductID, const string &pName, const string &category, const string &supplier, double price) : ProductID(ProductID),
    pName(pName),
    category(category),
    supplier(supplier),
    price(price)
{}

// --------------------------------------------------------------
// GETTERS AND SETTERS
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
// --------------------------------------------------------------

/**
 * @brief This function converts a product's data into
 * a formatted string that is separated by commas, which
 * facilitates input into CSV file.
 *
 * @returns comma-separated string with product's data.
 */
string Product::toString() {
    string productStr = "";
    productStr += to_string(ProductID) + ",";
    productStr += pName + ",";
    productStr += category + ",";
    productStr += supplier + ",";
    productStr += to_string_with_precision(price);
    return productStr;
}


