#ifndef PRODUCTWINDOW_H
#define PRODUCTWINDOW_H

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
