#include "productwindow.h"
#include "ui_productwindow.h"
#include "product.h"
#include "mergesort.h"
#include <QFile>

ProductWindow::ProductWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProductWindow) {
    ui->setupUi(this);

    showProductTable();

    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
}

list<Product> ProductWindow::getProducts() {
    list<Product> products;
    QFile file(R"(./db/p-db.csv)");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qFatal() << "Failed to open the file.";

    QTextStream in(&file);

    // Ignore the first line, since that includes the database headers.
    if (!in.atEnd())
        in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        Product product(fields[0].toInt(), fields[1].toStdString(), fields[2].toStdString(), fields[3].toStdString()
                        , fields[4].toDouble());
        products.push_back(product);
    }

    file.close();

    return products;
}

void ProductWindow::showProductTable() {
    // This line ensures refreshing instead of rewritting.
    ui->productTable->clear();

    // Setting table headers
    ui->productTable->setHorizontalHeaderLabels({"ProductID", "Name", "Category", "Supplier", "Price"});
    ui->productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Getting customers from database
    list<Product> products = getProducts();
    products = mergeSort(products);
    ui->productTable->setRowCount(products.size());

    int row = 0;
    for (const auto& product : products) {
        ui->productTable->insertRow(row);
        ui->productTable->setItem(row, 0, new QTableWidgetItem(QString::number(product.getProductID())));
        ui->productTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(product.getPName())));
        ui->productTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(product.getCategory())));
        ui->productTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(product.getSupplier())));
        ui->productTable->setItem(row, 4, new QTableWidgetItem(QString::number(product.getPrice(), 'f', 2)));

        for (int col = 0; col < ui->productTable->columnCount(); ++col)
            ui->productTable->item(row, col)->setTextAlignment(Qt::AlignCenter);

        ++row;
    }

    ui->productTable->show();
}

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

void ProductWindow::writeToDatabase() {
    QFile file(R"(./db/p-db.csv)");

    string name = ui->name_edit->text().toStdString();
    string category = ui->category_box->currentText().toStdString();
    string supplier = ui->supplier_edit->text().toStdString();
    double price = ui->price_edit->text().toDouble();
    int id = getNextIdAvailable();

    if (name == "" || supplier == "" || category == "" || id == 0)
        qDebug() << "Can't add new product";

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
    }

    ui->name_edit->setText("");
    ui->category_box->clearEditText();
    ui->supplier_edit->setText("");
    ui->price_edit->setText("");

    showProductTable();
}


ProductWindow::~ProductWindow()
{
    delete ui;
}
