#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T15:35:21
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ballance
TEMPLATE = app


SOURCES += main.cpp\
        ballance.cpp \
    ballancepath.cpp \
    ballancepathopenglwidget.cpp \
    ylopenglpainter.cpp \
    ylnaturallaw.cpp

HEADERS  += ballance.h \
    ballancepath.h \
	ballancepathopenglwidget.h \
    ylqtwidgetheader.h \
    ylopenglpainter.h \
    yltree4.h \
    ylnaturallaw.h



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
    resource/img/earth1.ico \
    resource/ballance.ico \
    resource/ballance.rc \
    README.md \
	RECORD.md \
    resource/img/map.jpg \
    resource/img/path.jpg



