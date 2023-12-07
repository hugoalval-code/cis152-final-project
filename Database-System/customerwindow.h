#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include <QMainWindow>
#include "customer.h"
#include <list>

namespace Ui {
class CustomerWindow;
}

class CustomerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerWindow(QWidget *parent = nullptr);
    ~CustomerWindow();

private slots:
    list<Customer> getCustomers();
    void showCustomerTable();
    int getNextIdAvailable();
    void writeToDatabase();

private:
    Ui::CustomerWindow *ui;
};

#endif // CUSTOMERWINDOW_H
