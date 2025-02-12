QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
        c++17 \
	console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chess.cpp \
    GameManager.cpp \
    main.cpp \
    viewer.cpp \
    Board.cpp

HEADERS += \
    Chess.h \
    GameManager.h \
    Header.h \
    Ma.h \
    viewer.h \
    Board.h

FORMS += \
    viewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
