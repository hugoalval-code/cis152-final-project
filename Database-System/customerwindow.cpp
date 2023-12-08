
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

#include "customerwindow.h"
#include "customer.h"
#include "mergesort.h"
#include "ui_customerwindow.h"
#include <QFile>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

// CustomerWindow Constructor
CustomerWindow::CustomerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CustomerWindow) {
    ui->setupUi(this);

    // Call function to parse csv file.
    showCustomerTable();

    // Connect UI buttons to their clicked() signals to either close
    // or write a new customer object to database.
    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
}

/**
 * @brief This function parses the customer csv database, storing
 * each row's worth of data into a Customer object, which is then
 * added to the std::list that is used at runtime to access customers.
 *
 * @returns list of Customer objects from CSV database.
 */
list<Customer> CustomerWindow::getCustomers() {
    list<Customer> customers;
    QFile file(R"(./db/c-db.csv)");

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
    // a Customer object, which is then stored in the customer list.
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        Customer customer(fields[0].toInt(), fields[1].toStdString(), fields[2].toStdString(), fields[3].toStdString());
        customers.push_back(customer);
    }

    // Closing the file for safety.
    file.close();

    return customers;
}

/**
 * @brief This function updates the QTableView widget in the main UI
 * with the data acquired from the database via getCustomers().
 */
void CustomerWindow::showCustomerTable() {
    // This line ensures refreshing the QTableView widget instead
    // of appending to it.
    ui->customerTable->clear();

    // Setting table headers
    ui->customerTable->setHorizontalHeaderLabels({"CustomerID", "FirstName", "LastName", "Email"});
    ui->customerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Getting customers from database
    list<Customer> customers = getCustomers();
    customers = mergeSort(customers);
    ui->customerTable->setRowCount(customers.size());


    // For each customer in the list, set its data into a given column of the current row.
    // Most Qt types take QStrings instead of std::strings so the line QString::number and
    // QString::fromStdString are used to make this convertion.
    int row = 0;
    for (const auto& customer : customers) {
        ui->customerTable->insertRow(row);
        ui->customerTable->setItem(row, 0, new QTableWidgetItem(QString::number(customer.getCustomerID())));
        ui->customerTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(customer.getFName())));
        ui->customerTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(customer.getLName())));
        ui->customerTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(customer.getEmail())));

        // Center align each cell.
        for (int col = 0; col < ui->customerTable->columnCount(); ++col)
            ui->customerTable->item(row, col)->setTextAlignment(Qt::AlignCenter);

        ++row;
    }

    // Display the newly refreshed table.
    ui->customerTable->show();
}

/**
 * @brief This function opens the "next-available" file, which
 * keeps a counter of IDs to make sure no one customer has the
 * same ID. First the file is read, then the number is stored,
 * and finally the file is overwritten with whatever was stored
 * plus one.
 *
 * @returns Next ID available in the database.
 */
int CustomerWindow::getNextIdAvailable() {
    QFile file(R"(./db/c-next.txt)");
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
 * @brief This function is used to write a new Customer object
 * into the csv database. It takes the strings from the QTextEdit
 * widgets and uses them to create said object. Basic user input
 * validation to make sure we don't store a nameless customer.
 * This function depends entirely in the success of the
 * getNextIdAvailable() function. If that fails, this function will
 * display an error message.
 */
void CustomerWindow::writeToDatabase() {
    QFile file(R"(./db/c-db.csv)");

    // Get data fields from QTextEdit widgets.
    string fname = ui->fname_edit->text().toStdString();
    string lname = ui->lname_edit->text().toStdString();
    string email = ui->email_edit->text().toStdString();
    int id = getNextIdAvailable();

    // Input validation
    if (fname == "" || lname == "" || email == "" || id == 0) {
        QColor color = Qt::red;
        QPalette palette = ui->errorMessage->palette();
        palette.setColor(QPalette::WindowText, color);
        ui->errorMessage->setPalette(palette);
        ui->errorMessage->setText("ERROR: Could not add new customer!");
    }
    else {
        Customer c(id, fname, lname, email);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            // Convert the QStringList to a comma-separated string
            QString row = QString::fromStdString(c.toString()) + '\n';
            // Append the row to the CSV file
            stream << row;

            file.close();
            qDebug() << "Data appended to CSV file successfully.";
        } else qDebug() << "Error opening the CSV file for appending." << file.errorString();
        ui->errorMessage->setText("");
    }

    // Finally, reset the text inside the QTextEdit widgets
    // is reset to empty strings so that the placeholders
    // appear again.
    ui->fname_edit->setText("");
    ui->lname_edit->setText("");
    ui->email_edit->setText("");

    // Call showCustomerTable to refresh right after appending
    // new customer.
    showCustomerTable();
}

// CustomerWindow Destructor
CustomerWindow::~CustomerWindow() {
    delete ui;
}
