TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lcsfml-graphics -lcsfml-audio -lcsfml-window -lcsfml-system

SOURCES += main.c \
    cenario.c \
    nave.c \
    aliens.c \
    csfml.c \
    tiro.c \
    global.c

HEADERS += \
    cenario.h \
    nave.h \
    aliens.h \
    csfml.h \
    tiro.h \
    global.h

