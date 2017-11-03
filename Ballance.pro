#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T15:35:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ballance
TEMPLATE = app


SOURCES += main.cpp\
        ballance.cpp \
    ballancepath.cpp \
    ballancepathopenglwidget.cpp \
    ylopenglpainter.cpp

HEADERS  += ballance.h \
    ballancepath.h \
	ballancepathopenglwidget.h \
    ylqtwidgetheader.h \
    ylopenglpainter.h \
    yltree4.h



QT       += opengl

win32:LIBS += -lOpengl32 \
				-lglu32 \
#				-lglut


RESOURCES += \
    resource/img.qrc


RC_FILE = ./resource/ballance.rc


DEFINES += YL_WIN32_QT


DISTFILES += \
    resource/img/earth.jpg \
    resource/img/earth.png \
    resource/img/mmexport1502771182717.png \
    resource/img/mmexport1507349001837.png \
    resource/img/mmexport1507349023277.png \
    resource/img/mmexport1507349027215.png \
    resource/img/mmexport1507349033771.png \
    resource/earth.png \
    resource/img/earth1.ico \
    resource/ballance.ico \
    resource/ballance.rc \
    README.md \
	RECORD.md



