#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "order.h"
#include <QFile>

OrderWindow::OrderWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OrderWindow) {
    ui->setupUi(this);

    ui->date_edit->setDate(QDate::currentDate());

    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
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
}

OrderWindow::~OrderWindow() {
    delete ui;
}
