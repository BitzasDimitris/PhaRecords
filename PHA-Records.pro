#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T21:24:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += xml
QT += charts
TARGET = PHA-Records
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    addrecord.cpp \
    xmlparser.cpp \
    record.cpp \
    keyenterfilter.cpp \
    structure.cpp \
    chartselector.cpp \
    chart.cpp \
    chartcreator.cpp \
    chartviewer.cpp \
    collection.cpp

HEADERS += \
        mainwindow.h \
    addrecord.h \
    xmlparser.h \
    record.h \
    keyenterfilter.h \
    structure.h \
    chartselector.h \
    chart.h \
    chartcreator.h \
    chartviewer.h \
    collection.h

FORMS += \
        mainwindow.ui \
    addrecord.ui \
    addrecord.ui \
    structure.ui \
    chartselector.ui \
    chartcreator.ui \
    chartviewer.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
