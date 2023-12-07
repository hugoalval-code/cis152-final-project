QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Database-System

SOURCES +=  ../Database-System/product.cpp \
            ../Database-System/customer.cpp \
            ../Database-System/order.cpp \
            tst_models.cpp

HEADERS += ../Database-System/mergesort.h
