QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HomingMethods
TEMPLATE = app

include($$_PRO_FILE_PWD_/../Interface/QInterface_files.pri)

INCLUDEPATH += EXAMPLES
INCLUDEPATH += Model/Missile
INCLUDEPATH += Model/Target
INCLUDEPATH += Tasks
INCLUDEPATH += Tasks/ADD_NEW_TASK

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += MODEL

OBJECTS_DIR = ./tmp/obj
MOC_DIR = ./tmp/moc
UI_DIR = ./tmp/ui
RCC_DIR = ./tmp/rcc
DESTDIR = $$_PRO_FILE_PWD_

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Tasks/CreateTask.cpp \
    Model/Target/Target.cpp \
    Tasks/Matrosova.cpp \
    Model/Missile/mymissile.cpp \
    Model/Target/mytarget.cpp

HEADERS += \
    Tasks/CreateTask.h \
    Model/Target/Target.h \
    Tasks/ADD_NEW_TASK/ADD_Target.hpp \
    Tasks/ADD_NEW_TASK/Target_List.hpp \
    Tasks/ADD_NEW_TASK/Task_Include.hpp \
    Tasks/ADD_NEW_TASK/Task_List.hpp \
    Tasks/ADD_NEW_TASK/Task_New.hpp \
    Tasks/Matrosova.h \
    Model/Missile/exchange.h \
    Model/Missile/mymissile.h \
    Model/Target/mytarget.h
