#ifndef PRODUCTWINDOW_H
#define PRODUCTWINDOW_H

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

#include <QMainWindow>
#include "product.h"
#include <list>

namespace Ui {
class ProductWindow;
}

class ProductWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductWindow(QWidget *parent = nullptr);
    ~ProductWindow();

private slots:
    list<Product> getProducts();
    void showProductTable();
    int getNextIdAvailable();
    void writeToDatabase();

private:
    Ui::ProductWindow *ui;
};

#endif // PRODUCTWINDOW_H
