#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

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
#include "order.h"
#include <list>

namespace Ui {
class OrderWindow;
}

class OrderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrderWindow(QWidget *parent = nullptr);
    ~OrderWindow();

private slots:
    list<Order> getOrders();
    void showOrderTable();
    int getNextIdAvailable();
    void writeToDatabase();

private:
    Ui::OrderWindow *ui;
};

#endif // ORDERWINDOW_H
