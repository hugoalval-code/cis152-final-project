
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

#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "order.h"
#include "mergesort.h"
#include <QFile>
#include <QColor>
#include <QColorDialog>

// OrderWindow Constructor
OrderWindow::OrderWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OrderWindow) {
    ui->setupUi(this);

    // Call function to parse csv file.
    showOrderTable();

    // Set the current date to the QDateEdit widget.
    ui->date_edit->setDate(QDate::currentDate());

    // Connect UI buttons to their clicked() signals to either go back
    // to the homescreen or write a new order object to the database.
    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
}

/**
 * @brief This function parses the order csv database, storing
 * each row's worth of data into an Order object, which is then
 * added to the std::list that is used at runtime to access orders.
 *
 * @returns list of Order objects from CSV database.
 */
list<Order> OrderWindow::getOrders() {
    list<Order> orders;
    QFile file(R"(./db/o-db.csv)");

    // If there is an error opening the database the app will crash, and
    // display an error message in the console.
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qFatal() << "Failed to open the file.";

    QTextStream in(&file);

    // Since the database file comes with headers, the first line
    // is ignored. Just cleanup.
    if (!in.atEnd())
        in.readLine();

    // Loop through the entire file, getting each row's data and storing into
    // an Order object, which is then stored in the orders list.
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        Order order(fields[0].toInt(), fields[1].toInt(), fields[2].toInt(), fields[3].toStdString());
        orders.push_back(order);
    }

    // Closing the file for safety
    file.close();

    return orders;
}

/**
 * @brief This function updates the QTableView widget in the main UI
 * with the data acquired from the database via getOrders().
 */
void OrderWindow::showOrderTable() {
    // This line ensures refreshing the QTableView widget instead
    // of appending to it.
    ui->orderTable->clear();

    // Setting table headers
    ui->orderTable->setHorizontalHeaderLabels({"OrderID", "CustomerID", "ProductID", "Date"});
    ui->orderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Getting orders from database
    list<Order> orders = getOrders();
    orders = mergeSort(orders);
    ui->orderTable->setRowCount(orders.size());

    // For each order in the list, set its data into a given column of the current row.
    // Most Qt types take QStrings instead of std::strings so the line QString::number and
    // QString::fromStdString are used to make this convertion.
    int row = 0;
    for (const auto& order : orders) {
        ui->orderTable->insertRow(row);
        ui->orderTable->setItem(row, 0, new QTableWidgetItem(QString::number(order.getOrderID())));
        ui->orderTable->setItem(row, 1, new QTableWidgetItem(QString::number(order.getCustomerID())));
        ui->orderTable->setItem(row, 2, new QTableWidgetItem(QString::number(order.getProductID())));
        ui->orderTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(order.getPurchasedDate())));

        // Center align each cell.
        for (int col = 0; col < ui->orderTable->columnCount(); ++col)
            ui->orderTable->item(row, col)->setTextAlignment(Qt::AlignCenter);

        ++row;
    }

    // Display the newly refreshed table.
    ui->orderTable->show();
}

/**
 * @brief This function opens the "next-available" file, which
 * keeps a counter of IDs to make sure no one order has the
 * same ID. First the file is read, then the number is stored,
 * and finally the file is overwritten with whatever was stored
 * plus one.
 *
 * @returns Next ID available in the database.
 */
int OrderWindow::getNextIdAvailable() {
    QFile file(R"(./db/o-next.txt)");
    int nextAvailable = 0;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        nextAvailable = stream.readAll().toInt();
        file.close();

        int updatedNext = nextAvailable + 1;
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QTextStream out(&file);
            out << updatedNext;
            file.close();
        } else {
            qCritical() << "Error opening file for writing.";
            return 0;
        }
    } else {
        qCritical() << "Error opening file for reading.";
        return 0;
    }

    return nextAvailable;
}

/**
 * @brief This function is used to write a new Order object
 * into the csv database. It takes the strings from the QTextEdit
 * and QDateEdit widgets and uses them to create said object.
 * Basic user input validation to make sure we don't store a
 * nameless customer. This function depends entirely in the
 * success of the getNextIdAvailable() function. If that fails,
 * this function will display an error message.
 */
void OrderWindow::writeToDatabase() {
    QFile file(R"(./db/o-db.csv)");

    // Get data fields from QTextEdit and QDateEdit widgets.
    int id = getNextIdAvailable();
    int cid = ui->customer_edit->text().toInt();
    int pid = ui->product_edit->text().toInt();
    QString date = ui->date_edit->text();

    // Input validation
    if (id == 0 || cid == 0 || pid == 0 || date == "") {
        QColor color = Qt::red;
        QPalette palette = ui->errorMessage->palette();
        palette.setColor(QPalette::WindowText, color);
        ui->errorMessage->setPalette(palette);
        ui->errorMessage->setText("ERROR: Could not add new oder!");
    }

    else {
        Order o(id, cid, pid, date.toStdString());
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            // Convert the QStringList to a comma-separated string
            QString row = QString::fromStdString(o.toString()) + '\n';
            // Append the row to the CSV file
            stream << row;

            file.close();
            qDebug() << "Data appended to CSV file successfully.";
        } else qDebug() << "Error opening the CSV file for appending." << file.errorString();
    }

    // Finally, reset the text inside the QTextEdit widgets
    // is reset to empty strings so that the placeholders
    // appear again. Same with QDateEdit, reset to today's date
    ui->customer_edit->setText("");
    ui->product_edit->setText("");
    ui->date_edit->setDate(QDate::currentDate());

    // Call showCustomerTable to refresh right after appending
    // new customer.
    showOrderTable();
}

// OrderWindow Destructor
OrderWindow::~OrderWindow() {
    delete ui;
}
