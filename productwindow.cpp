#include "productwindow.h"
#include "ui_productwindow.h"
#include "product.h"
#include <QFile>

ProductWindow::ProductWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProductWindow) {
    ui->setupUi(this);

    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
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
}


ProductWindow::~ProductWindow()
{
    delete ui;
}
