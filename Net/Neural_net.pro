TEMPLATE = app
CONFIG += console c++latest
CONFIG -= app_bundle
CONFIG += qt

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
        DataSet/dataset.cpp \
        DataSet/mnistset.cpp \
        activationfunction.cpp \
        layer.cpp \
        main.cpp \
        net.cpp \
        neuron.cpp \
        painter/paintwidget.cpp

HEADERS += \
    DataSet/dataset.h \
    DataSet/mnistset.h \
    activationfunction.h \
    dataset.h \
    layer.h \
    net.h \
    neuron.h \
    painter/paintwidget.h

FORMS += \
    painter/paintwidget.ui
