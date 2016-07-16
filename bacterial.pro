#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T16:01:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bacterial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp \
    bacteria.cpp \
    Integrator.cpp \
    BacteriaSystem.cpp \
    PlotGraph.cpp

HEADERS  += mainwindow.h \
    widget.h \
    bacteria.h \
    Integrator.h \
    BacteriaSystem.h \
    PlotGraph.h

FORMS    += mainwindow.ui
