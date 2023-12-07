#include "customerwindow.h"
#include "customer.h"
#include "mergesort.h"
#include "ui_customerwindow.h"
#include <QFile>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

CustomerWindow::CustomerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CustomerWindow) {
    ui->setupUi(this);

    showCustomerTable();

    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
}

list<Customer> CustomerWindow::getCustomers() {
    list<Customer> customers;
    QFile file(R"(./db/c-db.csv)");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qFatal() << "Failed to open the file.";

    QTextStream in(&file);

    if (!in.atEnd()) {
        in.readLine();
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        Customer customer(fields[0].toInt(), fields[1].toStdString(), fields[2].toStdString(), fields[3].toStdString());
        customers.push_back(customer);
    }

    file.close();

    return customers;
}

void CustomerWindow::showCustomerTable() {
    // This line ensures refreshing instead of rewritting.
    ui->customerTable->clear();

    // Setting table headers
    ui->customerTable->setHorizontalHeaderLabels({"CustomerID", "FirstName", "LastName", "Email"});
    ui->customerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Getting customers from database
    list<Customer> customers = getCustomers();
    customers = mergeSort(customers);
    ui->customerTable->setRowCount(customers.size());

    int row = 0;
    for (const auto& customer : customers) {
        ui->customerTable->insertRow(row);
        ui->customerTable->setItem(row, 0, new QTableWidgetItem(QString::number(customer.getCustomerID())));
        ui->customerTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(customer.getFName())));
        ui->customerTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(customer.getLName())));
        ui->customerTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(customer.getEmail())));

        for (int col = 0; col < ui->customerTable->columnCount(); ++col)
            ui->customerTable->item(row, col)->setTextAlignment(Qt::AlignCenter);

        ++row;
    }

    ui->customerTable->show();
}

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

void CustomerWindow::writeToDatabase() {
    QFile file(R"(./db/c-db.csv)");

    string fname = ui->fname_edit->text().toStdString();
    string lname = ui->lname_edit->text().toStdString();
    string email = ui->email_edit->text().toStdString();
    int id = getNextIdAvailable();

    if (fname == "" || lname == "" || email == "" || id == 0)
        qDebug() << "Can't add new user";

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
    }

    ui->fname_edit->setText("");
    ui->lname_edit->setText("");
    ui->email_edit->setText("");

    showCustomerTable();
}

CustomerWindow::~CustomerWindow() {
    delete ui;
}
