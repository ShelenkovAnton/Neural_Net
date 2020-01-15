TEMPLATE = app
CONFIG += console c++latest
CONFIG -= app_bundle
CONFIG += qt

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

FORMS += \
    GUI/mainwindow.ui \
    GUI/paintwidget.ui

HEADERS += \
    DataSet/dataset.h \
    DataSet/mnistset.h \
    GUI/mainwindow.h \
    GUI/paintwidget.h \
    GUI/styles.h \
    Net/activationfunction.h \
    Net/layer.h \
    Net/net.h \
    Net/neuron.h

SOURCES += \
    DataSet/dataset.cpp \
    DataSet/mnistset.cpp \
    GUI/mainwindow.cpp \
    GUI/paintwidget.cpp \
    GUI/styles.cpp \
    Net/activationfunction.cpp \
    Net/layer.cpp \
    Net/net.cpp \
    Net/neuron.cpp \
    main.cpp


