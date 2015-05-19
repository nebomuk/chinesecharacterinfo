#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T21:38:22
#
#-------------------------------------------------

QT       += core gui webkit concurrent network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = chinesecharacterinfo
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    inputform.cpp \
    hanzisearch.cpp \
    adjdecloader.cpp \
    deprecated/hanzisearch2.cpp \
    dictloader_edict.cpp \
    dictloadersep.cpp \
    convertpinyin.cpp \
    htmldelegate.cpp

HEADERS  += mainwindow.h \
    inputform.h \
    hanzisearch.h \
    adjdecloader.h \
    deprecated/hanzisearch2.h \
    dictloader_edict.h \
    dictloadersep.h \
    charfreq.h \
    color.h \
    convertpinyin.h \
    htmldelegate.h

FORMS    += mainwindow.ui \
    mainwindow_small.ui

DEFINES *= QT_USE_QSTRINGBUILDER

RESOURCES += \
    res.qrc
