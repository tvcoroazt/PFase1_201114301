TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


TEMPLATE = app
TARGET = practica
QT += core gui
QT += widgets
#INCLUDEPATH += .
# Input


SOURCES += main.c \
    a.c \
    comandos.c \
    disk.c \
    reportes.c \
    particion.c \
    sistema.c

DISTFILES += \
    prueba

HEADERS += \
    comandos.h \
    disk.h \
    reportes.h \
    particion.h \
    a.h \
    sistema.h \
    sarchivos.h
