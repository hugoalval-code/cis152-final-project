
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

#include <QtTest>
#include <list>
#include "customer.h"
#include "product.h"
#include "order.h"
#include "mergesort.h"
// add necessary includes here

class models : public QObject {
    Q_OBJECT

public:
    models();
    ~models();

private slots:
    void test_create_customer();
    void test_create_product();
    void test_create_order();
    void test_customer_to_string();
    void test_product_to_string();
    void test_order_to_string();
    void test_merge_sort_int();
    void test_merge_sort_customer();
    void test_merge_sort_product();
    void test_merge_sort_order();
};

models::models() {}

models::~models() {}

void models::test_create_customer() {
    // ARRANGE
    Customer customer(1, "first", "last", "email");
    // ACT
    bool actual = customer.getLName() == "last";
    //ASSERT
    QVERIFY(actual);
}

void models::test_create_product() {
    // ARRANGE
    Product product(1, "name", "category", "supplier", 1);
    // ACT
    bool actual = product.getPrice() == 1;
    // ASSERT
    QVERIFY(actual);
}

void models::test_create_order() {
    // ARRANGE
    Order order(1, 3, 2, "MM/DD/YYYY");
    // ACT
    bool actual = order.getPurchasedDate() == "MM/DD/YYYY";
    // ASSERT
    QVERIFY(actual);
}

void models::test_customer_to_string() {
    // ARRANGE
    Customer customer(1, "Hugo", "Alvarez", "hugoav@email.net");
    // ACT
    string actual = customer.toString();
    string expected = "1,Hugo,Alvarez,hugoav@email.net";
    // ASSERT
    QCOMPARE(actual, expected);
}

void models::test_product_to_string() {
    // ARRANGE
    Product product(1, "Soda", "Grocery", "Coca Cola", 1.99);
    // ACT
    string actual = product.toString();
    string expected = "1,Soda,Grocery,Coca Cola,1.99";
    // ASSERT
    QCOMPARE(actual, expected);
}

void models::test_order_to_string() {
    // ARRANGE
    Order order(1,3,2,"12/06/2023");
    // ACT
    string actual = order.toString();
    string expected = "1,3,2,12/06/2023";
    // ASSERT
    QCOMPARE(actual, expected);
}

void models::test_merge_sort_int() {
    // ARRANGE
    list<int> intList = {5, 7, 1, 9, 20, 2, 4, 3};
    // ACT
    list<int> expected = {1, 2, 3, 4, 5, 7, 9, 20};
    list<int> actual = mergeSort(intList);
    // ASSERT
    QCOMPARE(actual, expected);
}

void models::test_merge_sort_customer() {
    // ARRANGE
    Customer c1(3, "first3", "last3", "email3");
    Customer c2(1, "first1", "last1", "email1");
    Customer c3(20, "first20", "last20", "email20");
    Customer c4(7, "first7", "last7", "email7");
    list<Customer> customers = {c1, c2, c3, c4};
    // ACT
    list<Customer> actual = mergeSort(customers);
    list<Customer> expected = {c2, c1, c4, c3};
    // ASSERT
    QCOMPARE(actual, expected);
}

void models::test_merge_sort_product() {
    // ARRANGE
    Product p1(7, "name7", "category7", "supplier7", 3.99);
    Product p2(10, "name10", "category10", "supplier10", 3.99);
    Product p3(20, "name20", "category20", "supplier20", 3.99);
    Product p4(2, "name2", "category2", "supplier2", 3.99);
    Product p5(3, "name3", "category3", "supplier3", 3.99);
    list<Product> products = {p1, p2, p3, p4, p5};
    // ACT
    list<Product> actual = mergeSort(products);
    list<Product> expected = {p4, p5, p1, p2, p3};
    // ASSERT
    QCOMPARE(actual, expected);
}

void models::test_merge_sort_order() {
    // ARRANGE
    Order o1(20,3,5,"10/12/2022");
    Order o2(9,3,5,"12/06/2023");
    Order o3(15,3,5,"11/21/2023");
    Order o4(11,3,5,"11/25/2023");
    list<Order> orders = {o1, o2, o3, o4};
    // ACT
    list<Order> actual = mergeSort(orders);
    list<Order> expected = {o2, o4, o3, o1};
    // ASSERT
    QCOMPARE(actual, expected);
}

QTEST_APPLESS_MAIN(models)

#include "tst_models.moc"
