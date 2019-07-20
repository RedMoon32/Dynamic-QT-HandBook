
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HomeWork
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
        src/basetableclass.cpp \
        src/combobox.cpp \
        src/htmlconverter.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/tabledatamodel.cpp

HEADERS += \
    src/basetableclass.h \
    src/combobox.h \
    src/htmlconverter.h \
        src/mainwindow.h \
    src/entity.h \
    src/datamodel.h \
    src/tabledatamodel.h

FORMS += \
        src/mainwindow.ui



DISTFILES += \
    template.html
