#-------------------------------------------------
#
# Project created by QtCreator 2021-12-23T17:42:25
#
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c+=11

TARGET = Chat
TEMPLATE = app


SOURCES += main.cpp\
        mainframe.cpp \
    chat.cpp \
    rsa.cpp

HEADERS  += mainframe.h \
    dependence_qt.h \
    chat.h \
    rsa.h

RESOURCES += \
    recource.qrc

OTHER_FILES += \
    style/DarkGray.qss \
    test.txt
