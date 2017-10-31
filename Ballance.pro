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
    glutdlls37beta/glut.h



QT       += opengl

win32:LIBS += -lOpengl32 \
				-lglu32 \
#				-lglut



RESOURCES += \
    resource/img.qrc





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/glutdlls37beta/ -lglut32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/glutdlls37beta/ -lglut32

INCLUDEPATH += $$PWD/glutdlls37beta
DEPENDPATH += $$PWD/glutdlls37beta

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/glutdlls37beta/ -lglut
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/glutdlls37beta/ -lglut
else:unix: LIBS += -L$$PWD/glutdlls37beta/ -lglut

INCLUDEPATH += $$PWD/glutdlls37beta
DEPENDPATH += $$PWD/glutdlls37beta



RC_FILE = ./resource/ballance.rc

DISTFILES += \
    glutdlls37beta/glut.lib \
    glutdlls37beta/glut32.lib \
    glutdlls37beta/glut.dll \
    glutdlls37beta/glut32.dll \
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
    README.md



