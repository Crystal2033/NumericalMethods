QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Mechanic/Exceptions/Exceptions.cpp \
    Mechanic/MathClasses/Matrix.cpp \
    Mechanic/MathClasses/Methods.cpp \
    Mechanic/MathClasses/Norm.cpp \
    Mechanic/Spline/CubicSpline.cpp \
    Sliders/abstractslider.cpp \
    Sliders/classicslider.cpp \
    main.cpp \
    mainwindow.cpp \
    plot.cpp \

HEADERS += \
    Mechanic/Colors.h \
    Mechanic/Exceptions/Exceptions.h \
    Mechanic/MathClasses/Matrix.h \
    Mechanic/MathClasses/Methods.h \
    Mechanic/MathClasses/Norm.h \
    Mechanic/Spline/CubicSpline.h \
    PatternObserver/Observer.h \
    PatternObserver/Subject.h \
    Sliders/abstractslider.h \
    Sliders/classicslider.h \
    mainwindow.h \
    plot.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
