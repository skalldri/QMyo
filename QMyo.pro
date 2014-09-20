#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T03:53:56
#
#-------------------------------------------------

QT       -= gui

TARGET = QMyo
TEMPLATE = lib

DEFINES += QMYO_LIBRARY

SOURCES += qmyo.cpp \
    myodatacollector.cpp

HEADERS += qmyo.h\
        qmyo_global.h \
    myodatacollector.h

OTHER_FILES += \
    lib/myo64.lib \
    lib/myo32.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lmyo32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lmyo32

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/myo32.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/myo32.lib

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
