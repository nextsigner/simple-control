#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T21:48:48
#
#-------------------------------------------------

QT       += core gui sql
#QT += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = control_1
TEMPLATE = app

#win32 {
       #CONFIG += embed_manifest_exe
       #QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
       #QMAKE_CFLAGS_RELEASE -= -MD
       #QMAKE_CFLAGS_RELEASE = -MT
 #}

SOURCES += main.cpp\
        mainwindow.cpp \
    dialogeditar.cpp \
    dialogconfirmar.cpp \
    dialogeditarmultiple.cpp \
    dialogagregarboleta.cpp \
    dialogagregarpago.cpp

HEADERS  += mainwindow.h \
    dialogeditar.h \
    dialogconfirmar.h \
    definiciones.h \
    dialogeditarmultiple.h \
    dialogagregarboleta.h \
    dialogagregarpago.h

FORMS    += mainwindow.ui \
    dialogeditar.ui \
    dialogconfirmar.ui \
    dialogeditarmultiple.ui \
    dialogagregarboleta.ui \
    dialogagregarpago.ui
