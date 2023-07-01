QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT +=network
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createchannel.cpp \
    forgot.cpp \
    join.cpp \
    logout.cpp \
    main.cpp \
    mainpage.cpp \
    mainwindow.cpp \
    send_message.cpp \
    signup.cpp

HEADERS += \
    createchannel.h \
    forgot.h \
    join.h \
    logout.h \
    mainpage.h \
    mainwindow.h \
    send_message.h \
    signup.h

FORMS += \
    createchannel.ui \
    forgot.ui \
    join.ui \
    logout.ui \
    mainpage.ui \
    mainwindow.ui \
    send_message.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
