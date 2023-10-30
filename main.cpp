#include "mainwindow.h"
#include "Product.h"
#include "Customer.h"
#include <QApplication>
#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Product prod1("Product1", "Category1", "Supplier1", 50.0);
    Product prod2("Product2", "Category2", "Supplier1", 65.2);
    Product prod3("Product3", "Category3", "Supplier1", 34.7);

    std::cout << prod1.toString() << std::endl;
    std::cout << prod2.toString() << std::endl;
    std::cout << prod3.toString() << std::endl;

    Customer cust1("Customer1", "Last1", "xxxx@xxx.com");
    Customer cust2("Customer2", "Last2", "xxxx@xxx.com");
    Customer cust3("Customer3", "Last3", "xxxx@xxx.com");

    std::cout << cust1.toString() << std::endl;
    std::cout << cust2.toString() << std::endl;
    std::cout << cust3.toString() << std::endl;

    return a.exec();
}
