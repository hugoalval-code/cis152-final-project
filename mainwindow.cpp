#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Customer.h"
#include "writetodatabase.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

