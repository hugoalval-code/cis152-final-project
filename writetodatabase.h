#ifndef WRITETODATABASE_H
#define WRITETODATABASE_H

#include <vector>
#include <string>
#include <fstream>
#include "Customer.h"
#include "Product.h"

void writeToCustomerDatabase(Customer customer) {
    std::string fileName = "./c-db.csv";
    std::ofstream customerDatabase;

    customerDatabase.open(fileName, std::ios::out | std::ios::app);
    if (customerDatabase.is_open()) {
        customerDatabase << std::to_string(customer.getCustomerID()) + ", "
                         << customer.getFirstName() + " " + customer.getLastName() << ", "
                         << customer.getEmail() + "\n";
    } else {
        // WILL LOOK INTO IMPLEMENTING CUSTOM EXCEPTION
        throw "ERROR: Couldn't write to customer database!";
    }
    customerDatabase.close();
}

// !TODO
void writeToOrderDatabase() {
    std::string fileName = "./o-db.csv";
    std::ofstream orderDatabase;

    // STILL NEED TO IMPLEMENT ORDER MODEL
//    orderDatabase.open(fileName);
//    if (orderDatabase.is_open()) {}
}

void writeToProductDatabase(Product product) {
    std::string fileName = "p-db.csv";
    std::ofstream productDatabase;

    productDatabase.open(fileName);
    if (productDatabase.is_open()) {
        productDatabase << std::to_string(product.getProductID()) + ", "
                        << product.getProductName() << ", "
                        << product.getCategory() << ", "
                        << product.getSupplier() << ", "
                        << product.getPrice() << "\n";
    } else {
        throw "ERROR: Couldn't write to product database!";
    }

    productDatabase.close();
}

#endif // WRITETODATABASE_H
