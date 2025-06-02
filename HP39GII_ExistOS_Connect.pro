QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    connectwindow.cpp \
    disconnectwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    update.cpp

HEADERS += \
    about.h \
    connectwindow.h \
    disconnectwindow.h \
    mainwindow.h \
    update.h

FORMS += \
    about.ui \
    connectwindow.ui \
    disconnectwindow.ui \
    mainwindow.ui \
    update.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    HP39GII_ExistOS_Connect.qrc

TRANSLATIONS +=
