#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

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
