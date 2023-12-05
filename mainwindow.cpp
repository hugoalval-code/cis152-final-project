#include "mainwindow.h"
#include "product.h"
#include "customer.h"
#include "./ui_mainwindow.h"
#include <QLayout>
#include <QLabel>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->main_area->setSizeConstraint(QLayout::SetMinimumSize);
    this->setLayout(ui->main_area);

    connect(ui->customers_btn, SIGNAL(clicked()), this, SLOT(openCustomerWindow()));
    connect(ui->products_btn, SIGNAL(clicked()), this, SLOT(openProductWindow()));
    connect(ui->orders_btn, SIGNAL(clicked()), this, SLOT(openOrderWindow()));
}

void MainWindow::openCustomerWindow() {
    QMainWindow *customerWindow = new QMainWindow(this);
    customerWindow->setWindowTitle("Customers");
    customerWindow->resize(400,300);
    customerWindow->show();
}

void MainWindow::openOrderWindow() {
    QMainWindow *orderWindow = new QMainWindow(this);
    orderWindow->setWindowTitle("Orders");
    orderWindow->resize(400,300);
    orderWindow->show();
}

void MainWindow::openProductWindow() {
    QMainWindow *productWindow = new QMainWindow(this);
    productWindow->setWindowTitle("Products");
    productWindow->resize(400,300);
    productWindow->show();
}

void MainWindow::writeToCDatabase() {

    QFile file(R"(.\db\c-db.csv)");

    Customer c(1, "Hugo", "Alvarez", "xxxxxx@xxx.xxx");

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

void MainWindow::writeToPDatabase(Product product) {}

MainWindow::~MainWindow()
{
    delete ui;
}

