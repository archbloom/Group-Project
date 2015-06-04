#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T22:40:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = weblog_analyser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    log_entry.cpp \
    displaywindow.cpp

HEADERS  += mainwindow.h \
    log_entry.h \
    displaywindow.h

FORMS    += mainwindow.ui \
    displaywindow.ui
