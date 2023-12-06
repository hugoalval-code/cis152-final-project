#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "order.h"
#include "mergesort.h"
#include <QFile>

OrderWindow::OrderWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OrderWindow) {
    ui->setupUi(this);

    showOrderTable();

    ui->date_edit->setDate(QDate::currentDate());

    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
}

list<Order> OrderWindow::getOrders() {
    list<Order> orders;
    QFile file(R"(./db/o-db.csv)");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qFatal() << "Failed to open the file.";

    QTextStream in(&file);

    // Ignore the first line, since that includes the database headers.
    if (!in.atEnd())
        in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        Order order(fields[0].toInt(), fields[1].toInt(), fields[2].toInt(), fields[3].toStdString());
        orders.push_back(order);
    }

    file.close();

    return orders;
}

void OrderWindow::showOrderTable() {
    // This line ensures refreshing instead of rewritting.
    ui->orderTable->clear();

    // Setting table headers
    ui->orderTable->setHorizontalHeaderLabels({"OrderID", "CustomerID", "ProductID", "Date"});
    ui->orderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Getting customers from database
    list<Order> orders = getOrders();
    orders = mergeSort(orders);
    ui->orderTable->setRowCount(orders.size());

    int row = 0;
    for (const auto& order : orders) {
        ui->orderTable->insertRow(row);
        ui->orderTable->setItem(row, 0, new QTableWidgetItem(QString::number(order.getOrderID())));
        ui->orderTable->setItem(row, 1, new QTableWidgetItem(QString::number(order.getCustomerID())));
        ui->orderTable->setItem(row, 2, new QTableWidgetItem(QString::number(order.getProductID())));
        ui->orderTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(order.getPurchasedDate())));

        for (int col = 0; col < ui->orderTable->columnCount(); ++col)
            ui->orderTable->item(row, col)->setTextAlignment(Qt::AlignCenter);

        ++row;
    }

    ui->orderTable->show();
}

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

void OrderWindow::writeToDatabase() {
    QFile file(R"(./db/o-db.csv)");

    int id = getNextIdAvailable();
    int cid = ui->customer_edit->text().toInt();
    int pid = ui->product_edit->text().toInt();
    QString date = ui->date_edit->text();

    if (id == 0 || cid == 0 || pid == 0 || date == "")
        qDebug() << "Can't add new order";

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

    ui->customer_edit->setText("");
    ui->product_edit->setText("");
    ui->date_edit->setDate(QDate::currentDate());

    showOrderTable();
}

OrderWindow::~OrderWindow() {
    delete ui;
}
