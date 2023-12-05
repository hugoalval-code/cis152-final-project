#include "customerwindow.h"
#include "customer.h"
#include "ui_customerwindow.h"
#include <QFile>

CustomerWindow::CustomerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CustomerWindow) {
    ui->setupUi(this);

    connect(ui->back_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->add_btn, SIGNAL(clicked()), this, SLOT(writeToDatabase()));
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
}

CustomerWindow::~CustomerWindow() {
    delete ui;
}
