QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    caloricoachdbmanager.cpp \
    calorictablewindow.cpp \
    caloriecalcwindow.cpp \
    customdish.cpp \
    fooditem.cpp \
    main.cpp \
    mainwindow.cpp \
    userprofile.cpp

HEADERS += \
    caloricoachdbmanager.h \
    calorictablewindow.h \
    caloriecalcwindow.h \
    customdish.h \
    fooditem.h \
    mainwindow.h \
    userprofile.h

FORMS += \
    calorictablewindow.ui \
    caloriecalcwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
