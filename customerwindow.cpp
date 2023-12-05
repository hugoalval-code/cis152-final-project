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

void CustomerWindow::writeToDatabase() {
    QFile file(R"(./db/c-db.csv)");

    string fname = ui->fname_edit->text().toStdString();
    string lname = ui->lname_edit->text().toStdString();
    string email = ui->email_edit->text().toStdString();

    if (fname == "" || lname == "" || email == "")
        qDebug() << "Can't add new user";

    else {
        Customer c(1, fname, lname, email);
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
}


CustomerWindow::~CustomerWindow() {
    delete ui;
}
