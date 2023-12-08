
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

#include "productwindow.h"
#include "ui_productwindow.h"
#include "product.h"
#include "mergesort.h"
#include <QFile>

// ProductWindow Constructor
ProductWindow::ProductWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProductWindow) {
    ui->setupUi(this);

    // Call function to parse csv file.
    showProductTable();

    // Connect UI buttons to their clicked() signals to either go back
    // to the homescreen or write a new order object to the database.
    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
}

/**
 * @brief This function parses the product csv database, storing
 * each row's worth of data into an Product object, which is then
 * added to the std::list that is used at runtime to access products.
 *
 * @returns list of Product objects from CSV database.
 */
list<Product> ProductWindow::getProducts() {
    list<Product> products;
    QFile file(R"(./db/p-db.csv)");

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
        Product product(fields[0].toInt(), fields[1].toStdString(), fields[2].toStdString(), fields[3].toStdString()
                        , fields[4].toDouble());
        products.push_back(product);
    }

    // Closing the file for safety
    file.close();

    return products;
}

/**
 * @brief This function updates the QTableView widget in the main UI
 * with the data acquired from the database via getOrders().
 */
void ProductWindow::showProductTable() {
    // This line ensures refreshing the QTableView widget instead
    // of appending to it.
    ui->productTable->clear();

    // Setting table headers
    ui->productTable->setHorizontalHeaderLabels({"ProductID", "Name", "Category", "Supplier", "Price"});
    ui->productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Getting products from database
    list<Product> products = getProducts();
    products = mergeSort(products);
    ui->productTable->setRowCount(products.size());

    // For each product in the list, set its data into a given column of the current row.
    // Most Qt types take QStrings instead of std::strings so the line QString::number and
    // QString::fromStdString are used to make this convertion.
    int row = 0;
    for (const auto& product : products) {
        ui->productTable->insertRow(row);
        ui->productTable->setItem(row, 0, new QTableWidgetItem(QString::number(product.getProductID())));
        ui->productTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(product.getPName())));
        ui->productTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(product.getCategory())));
        ui->productTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(product.getSupplier())));
        ui->productTable->setItem(row, 4, new QTableWidgetItem(QString::number(product.getPrice(), 'f', 2)));

        // Center align each cell.
        for (int col = 0; col < ui->productTable->columnCount(); ++col)
            ui->productTable->item(row, col)->setTextAlignment(Qt::AlignCenter);

        ++row;
    }

    // Display the newly refreshed table.
    ui->productTable->show();
}

/**
 * @brief This function opens the "next-available" file, which
 * keeps a counter of IDs to make sure no one product has the
 * same ID. First the file is read, then the number is stored,
 * and finally the file is overwritten with whatever was stored
 * plus one.
 *
 * @returns Next ID available in the database.
 */
int ProductWindow::getNextIdAvailable() {
    QFile file(R"(./db/p-next.txt)");
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
 * @brief This function is used to write a new Product object
 * into the csv database. It takes the strings from the QTextEdit
 * widgets and uses them to create said object. Basic user input
 * validation to make sure we don't store a nameless product.
 * This function depends entirely in the success of the
 * getNextIdAvailable() function. If that fails, this function
 * will display an error message.
 */
void ProductWindow::writeToDatabase() {
    QFile file(R"(./db/p-db.csv)");

    // Get data fields from QTextEdit and QDateEdit widgets.
    string name = ui->name_edit->text().toStdString();
    string category = ui->category_box->currentText().toStdString();
    string supplier = ui->supplier_edit->text().toStdString();
    double price = ui->price_edit->text().toDouble();
    int id = getNextIdAvailable();

    // Input validation
    if (name == "" || supplier == "" || category == "" || id == 0) {
        QColor color = Qt::red;
        QPalette palette = ui->errorMessage->palette();
        palette.setColor(QPalette::WindowText, color);
        ui->errorMessage->setPalette(palette);
        ui->errorMessage->setText("ERROR: Could not add new product!");
    }
    else {
        Product p(id,name,category,supplier,price);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            // Convert the QStringList to a comma-separated string
            QString row = QString::fromStdString(p.toString()) + '\n';
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
    ui->name_edit->setText("");
    ui->category_box->clearEditText();
    ui->supplier_edit->setText("");
    ui->price_edit->setText("");

    // Call showCustomerTable to refresh right after appending
    // new customer.
    showProductTable();
}

// ProductWindow Destructor
ProductWindow::~ProductWindow() {
    delete ui;
}
