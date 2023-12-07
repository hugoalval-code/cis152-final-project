QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

ICON = icon256.png

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    product.cpp \
    customer.cpp \
    order.cpp \
    customerwindow.cpp \
    productwindow.cpp \
    orderwindow.cpp

HEADERS += \
    mainwindow.h \
    product.h \
    customer.h \
    order.h \
    customernotfoundexception.h \
    customerwindow.h \
    productwindow.h \
    orderwindow.h \
    mergesort.h

FORMS += \
    mainwindow.ui \
    customerwindow.ui \
    productwindow.ui \
    orderwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
