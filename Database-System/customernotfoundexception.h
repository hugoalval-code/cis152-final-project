#ifndef CUSTOMERNOTFOUNDEXCEPTION_H
#define CUSTOMERNOTFOUNDEXCEPTION_H

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

#include <string>
using namespace std;

/**
 * Customer Not Found Exception Class
 */
class CustomerNotFoundException {
private:
    string msg_;
public:
    CustomerNotFoundException(const string& msg = "Customer not found!") : msg_(msg) {}
    ~CustomerNotFoundException() {}

    string getMessage() const {
        return (msg_);
    }
};

#endif // CUSTOMERNOTFOUNDEXCEPTION_H
