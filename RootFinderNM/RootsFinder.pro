QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sliders/abstractslider.cpp \
    Sliders/classicslider.cpp \
    SolveMechanic/Exceptions.cpp \
    SolveMechanic/Methods.cpp \
    Widgets/plot.cpp \
    Widgets/solverwidget.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    Observer.h \
    PatternObserver/Observer.h \
    PatternObserver/Subject.h \
    Sliders/abstractslider.h \
    Sliders/classicslider.h \
    SolveMechanic/Exceptions.h \
    SolveMechanic/Methods.h \
    Subject.h \
    Widgets/plot.h \
    Widgets/solverwidget.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Pics.qrc
