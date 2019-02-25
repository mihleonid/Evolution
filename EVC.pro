TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    main.cpp

INCLUDEPATH += /usr/include/SDL2/
LIBS += -LC:/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

SUBDIRS += \
    EVC.pro

DISTFILES += \
    EVC.pro.user

HEADERS += \
    bact.h \
    cfv.h \
    clean.h \
    eater.h \
    energy.h \
    field.h \
    fighter.h \
    food.h \
    go.h \
    good.h \
    mainwindow.h \
    neuro.h \
    pools.h \
    poolsdef.h \
    universal.h \
    zed.h
