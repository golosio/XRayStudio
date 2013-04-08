#-------------------------------------------------
#
# Project created by QtCreator 2013-03-18T17:29:42
#
#-------------------------------------------------

QT       += core gui

TARGET = XRayStudio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    icondiagram.cpp \
    connectdialog.cpp \
    deviceinterf.cpp \
    consoleform.cpp \
    savedevice.cpp \
    loaddevice.cpp \
    deviceinspect.cpp \
    devicecommands.cpp \
    devices.cpp \
    sourceform.cpp \
    xrs_error.cpp \
    icondiagramwidget.cpp \
    projectdialog.cpp \
    projtemplatedialog.cpp \
    warningdialog.cpp \
    savechangesdialog.cpp \
    devicenameedit.cpp \
    rundialog.cpp \
    choosesavedevice.cpp \
    bannerdialog.cpp

HEADERS  += mainwindow.h \
    icondiagram.h \
    connectdialog.h \
    deviceinterf.h \
    consoleform.h \
    deviceinspect.h \
    devicecommands.h \
    sourceform.h \
    xrs_error.h \
    icondiagramwidget.h \
    projectdialog.h \
    projtemplatedialog.h \
    warningdialog.h \
    savechangesdialog.h \
    devicenameedit.h \
    rundialog.h \
    choosesavedevice.h \
    bannerdialog.h

FORMS    += mainwindow.ui \
    connectdialog.ui \
    consoleform.ui \
    deviceinspect.ui \
    devicecommands.ui \
    sourceform.ui \
    icondiagramwidget.ui \
    projectdialog.ui \
    projtemplatedialog.ui \
    warningdialog.ui \
    savechangesdialog.ui \
    rundialog.ui \
    choosesavedevice.ui \
    bannerdialog.ui

RESOURCES += \
    banner.qrc

OTHER_FILES += \
    devices/Standard setup/bug.jpeg \
    devices/Standard setup/spectrum.png \
    devices/Standard setup/source.png \
    devices/Standard setup/sample.png \
    devices/Standard setup/quadrics.png \
    devices/Standard setup/geom3d.png \
    devices/Standard setup/detector.png \
    devices/Standard setup/composition.png \
    devices/Standard setup/composition.png \
    devices/Standard setup/*.png \
    devices/Standard setup/*.png \
    devices/Standard setup/spectrum.png \
    devices/Standard setup/source.png \
    devices/Standard setup/sample.png \
    devices/Standard setup/quadrics.png \
    devices/Standard setup/geom3d.png \
    devices/Standard setup/detector.png \
    devices/Standard setup/composition.png

INCLUDEPATH += \
/home/golosio/progetti/xrmc/xrmc/src/arrayNd \
/home/golosio/progetti/xrmc/xrmc/src/composition \
/home/golosio/progetti/xrmc/xrmc/src/detector \
/home/golosio/progetti/xrmc/xrmc/src/device \
/home/golosio/progetti/xrmc/xrmc/src/exception \
/home/golosio/progetti/xrmc/xrmc/src/geom3d \
/home/golosio/progetti/xrmc/xrmc/src/gettoken \
/home/golosio/progetti/xrmc/xrmc/src/main \
/home/golosio/progetti/xrmc/xrmc/src/photon \
/home/golosio/progetti/xrmc/xrmc/src/randmt \
/home/golosio/progetti/xrmc/xrmc/src/sample \
/home/golosio/progetti/xrmc/xrmc/src/source \
/home/golosio/progetti/xrmc/xrmc/src/spectrum \
/home/golosio/progetti/xrmc/xrmc/src/xrmc_algo \
/home/golosio/progetti/xrmc/xrmc/src/xrmc_math \
/usr/local/include/xraylib/

DEPENDPATH += \
/home/golosio/progetti/xrmc/xrmc/src/arrayNd \
/home/golosio/progetti/xrmc/xrmc/src/composition \
/home/golosio/progetti/xrmc/xrmc/src/detector \
/home/golosio/progetti/xrmc/xrmc/src/device \
/home/golosio/progetti/xrmc/xrmc/src/exception \
/home/golosio/progetti/xrmc/xrmc/src/geom3d \
/home/golosio/progetti/xrmc/xrmc/src/gettoken \
/home/golosio/progetti/xrmc/xrmc/src/main \
/home/golosio/progetti/xrmc/xrmc/src/photon \
/home/golosio/progetti/xrmc/xrmc/src/randmt \
/home/golosio/progetti/xrmc/xrmc/src/sample \
/home/golosio/progetti/xrmc/xrmc/src/source \
/home/golosio/progetti/xrmc/xrmc/src/spectrum \
/home/golosio/progetti/xrmc/xrmc/src/xrmc_algo \
/home/golosio/progetti/xrmc/xrmc/src/xrmc_math \
/usr/local/include/xraylib/

LIBS += -LDebugOrReleasePath -lxrmc -lxrl

CONFIG += console
