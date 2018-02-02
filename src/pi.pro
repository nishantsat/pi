#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T16:40:35
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++14
INCLUDEPATH += /home/nishant/stuff/boost_1_66_0

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    parser.h

FORMS    += mainwindow.ui
