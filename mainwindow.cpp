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
#include <iostream>
#include <fstream>
#include <filesystem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
    this->setLayout(ui->verticalLayout);

    Product p(1, "Product1", "Category1", "Supplier1", 12.99);

    QLabel *productLabel = new QLabel;
    productLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    productLabel->setWordWrap(true);
    productLabel->setText(QString::fromStdString(p.toString()));
    ui->verticalLayout->addWidget(productLabel);

    QPushButton *writeDBbtn = new QPushButton("Write to database", this);
    ui->verticalLayout->addWidget(writeDBbtn);
    connect(writeDBbtn, &QPushButton::clicked, this, &MainWindow::writeToCDatabase);
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

