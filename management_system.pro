#-------------------------------------------------
#
# Project created by QtCreator 2019-04-03T22:10:21
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = management_system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newgroup.cpp \
    databox.cpp \
    StaffModel.cpp

HEADERS  += mainwindow.h \
    newgroup.h \
    structbox.h \
    databox.h \
    ContentProvider.h \
    StaffModel.h

FORMS    += mainwindow.ui \
    newgroup.ui

RESOURCES += \
    resource/resource.qrc
