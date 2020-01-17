TEMPLATE = app
CONFIG += console c++latest
CONFIG -= app_bundle
CONFIG += qt

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

FORMS += \
    GUI/layeritem.ui \
    GUI/learningwidget.ui \
    GUI/mainwindow.ui \
    GUI/paintwidget.ui \
    GUI/setupnetwidget.ui

HEADERS += \
    DataSet/dataset.h \
    DataSet/mnistset.h \
    GUI/layeritem.h \
    GUI/learningwidget.h \
    GUI/mainwindow.h \
    GUI/paintwidget.h \
    GUI/setupnetwidget.h \
    GUI/styles.h \
    Net/activationfunction.h \
    Net/layer.h \
    Net/net.h \
    Net/neuron.h

SOURCES += \
    DataSet/dataset.cpp \
    DataSet/mnistset.cpp \
    GUI/layeritem.cpp \
    GUI/learningwidget.cpp \
    GUI/mainwindow.cpp \
    GUI/paintwidget.cpp \
    GUI/setupnetwidget.cpp \
    GUI/styles.cpp \
    Net/activationfunction.cpp \
    Net/layer.cpp \
    Net/net.cpp \
    Net/neuron.cpp \
    main.cpp


