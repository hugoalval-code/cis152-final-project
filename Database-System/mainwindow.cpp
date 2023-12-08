
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

#include "mainwindow.h"
#include "customerwindow.h"
#include "productwindow.h"
#include "orderwindow.h"
#include "./ui_mainwindow.h"
#include <QLayout>
#include <QLabel>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QPushButton>
#include <QTimer>
#include <QDateTime>

// MainWindow Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Call code to initialize database files and directory
    initializeDatabases();

    // This block creates a timer event to handle a QLCDNumber
    // widget that represents a clock.
    ui->clock->setDigitCount(8);
    ui->clock->setSegmentStyle(QLCDNumber::Flat);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDateTime);
    timer->start(1000);
    updateDateTime();

    // Connecting buttons to their respective clicked() signals
    // and functions. Each one opens a different window of the program.
    connect(ui->customers_btn, SIGNAL(clicked()), this, SLOT(openCustomerWindow()));
    connect(ui->products_btn, SIGNAL(clicked()), this, SLOT(openProductWindow()));
    connect(ui->orders_btn, SIGNAL(clicked()), this, SLOT(openOrderWindow()));
}

/**
 * @brief This function is used to create database directory
 * and files. It performs a quick check to see if they already exists
 * to prevent overwritting instead of appending.
 */
void MainWindow::initializeDatabases() {
    // =====================================================================
    // CREATING DATABASE DIRECTORY
    QDir directory = QDir::currentPath() + R"(/db)";

    if (!directory.exists()) {
        if (directory.mkpath("."))
            qDebug() << "Database directory created successfully";
        else
            qWarning() << "Failed to create database directory";
    }
    else
        qDebug() << "Database directory already exists. Continuing...";

    // =====================================================================
    // CREATING CUSTOMER DATABASE
    QString filePath = R"(./db/c-db.csv)";
    QFile cFile(filePath);

    if (!cFile.exists()) {
        if (cFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&cFile);
            stream << "CustomerID,FirstName,LastName,Email\n";
            cFile.close();
            qDebug() << "Customer database file created successfully";
        }
        else
            qWarning() << "Failed to create customer database file";
    }
    else
        qDebug() << "Customer database file already exists. Continuing...";

    // Next customer id available file
    filePath = R"(./db/c-next.txt)";
    QFile cNextFile(filePath);
    if (!cNextFile.exists()) {
        if (cNextFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&cNextFile);
            stream << "1";
            cNextFile.close();
            qDebug() << "Customer next-available file created successfully";
        }
        else
            qWarning() << "Failed to create customer next-available file!";
    }
    else
        qDebug() << "Customer next-available file already exists. Continuing...";

    // =====================================================================
    // CREATING PRODUCT DATABASE
    filePath = R"(./db/p-db.csv)";
    QFile pFile(filePath);
    if (!pFile.exists()) {
        if (pFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&pFile);
            stream << "ProductID,ProductName,Category,Supplier,Price\n";
            pFile.close();
            qDebug() << "Product database file created successfully";
        }
        else
            qWarning() << "Failed to create product database file";
    }
    else
        qDebug() << "Product database file already exists. Continuing...";

    // Next product id available file
    filePath = R"(./db/p-next.txt)";
    QFile pNextFile(filePath);
    if (!pNextFile.exists()) {
        if (pNextFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&pNextFile);
            stream << "1";
            pNextFile.close();
            qDebug() << "Product next-available file created successfully";
        }
        else
            qWarning() << "Failed to create product next-available file!";
    }
    else
        qDebug() << "Product next-available file already exists. Continuing...";

    // =====================================================================
    // CREATING ORDER DATABASE
    filePath = R"(./db/o-db.csv)";
    QFile oFile(filePath);
    if (!oFile.exists()) {
        if (oFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&oFile);
            stream << "OrderID,CustomerID,ProductID,PurchaseDate\n";
            pFile.close();
            qDebug() << "Order database file created successfully";
        }
        else
            qWarning() << "Failed to create order database file";
    }
    else
        qDebug() << "Order database file already exists. Continuing...";

    // Next order id available file
    filePath = R"(./db/o-next.txt)";
    QFile oNextFile(filePath);
    if (!oNextFile.exists()) {
        if (oNextFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&oNextFile);
            stream << "1";
            oNextFile.close();
            qDebug() << "Order next-available file created successfully";
        }
        else
            qWarning() << "Failed to create order next-available file!";
    }
    else
        qDebug() << "Order next-available file already exists. Continuing...";

    // =====================================================================
}

/**
 * @brief This function opens the Customer window.
 */
void MainWindow::openCustomerWindow() {
    CustomerWindow *customerWindow = new CustomerWindow(this);
    customerWindow->setWindowTitle("Customers");
    customerWindow->show();
}

/**
 * @brief This function opens the Order window.
 */
void MainWindow::openOrderWindow() {
    OrderWindow *orderWindow = new OrderWindow(this);
    orderWindow->setWindowTitle("Orders");
    orderWindow->show();
}

/**
 * @brief This function opens the Product window.
 */
void MainWindow::openProductWindow() {
    ProductWindow *productWindow = new ProductWindow(this);
    productWindow->setWindowTitle("Products");
    productWindow->show();
}

/**
 * @brief This function is called every time the QTimer
 * event gets a signal, in this case it's setup to call it
 * every second. It gets the current time, and updates the
 * values inside the QLCDNumber widet to match the time.
 */
void MainWindow::updateDateTime() {
    // Get current time
    QTime currentTime = QTime::currentTime();
    ui->clock->display(currentTime.toString("hh:mm:ss"));
}

// MainWindow Destructor
MainWindow::~MainWindow() {
    delete ui;
}

