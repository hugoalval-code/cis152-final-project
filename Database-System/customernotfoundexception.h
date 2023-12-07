#ifndef CUSTOMERNOTFOUNDEXCEPTION_H
#define CUSTOMERNOTFOUNDEXCEPTION_H

#include <string>
using namespace std;

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
