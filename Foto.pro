#-------------------------------------------------
#
# Project created by QtCreator 2018-06-29T18:53:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Foto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pyr_window.cpp \
    selectpictureaction.cpp

HEADERS  += \
    mainwindow.h \
    pyr_window.h \
    selectpictureaction.h

FORMS    += mainwindow.ui \
    Pyr_window.ui

RESOURCES += \
    Resources.qrc
