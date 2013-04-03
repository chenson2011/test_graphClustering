#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T09:21:34
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = test_graphClustering
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    spectral.cpp \
    graph.cpp \
    kmean.cpp

INCLUDEPATH += D:\eigen

INCLUDEPATH += D:\boost_1_53_0

HEADERS += \
    graph.h \
    kmean.h

OTHER_FILES += \
    polbooks.gml \
    airlines.graphml

