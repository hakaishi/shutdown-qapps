!win32{
QT += dbus
}

TEMPLATE = app
TARGET = bin/qshutdown
DEPENDPATH = . src src/translations
INCLUDEPATH = . src
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

system(lrelease qshutdown.pro)

QMAKE_DISTCLEAN = src/translations/*.qm

# Input
HEADERS = src/gui.h src/power.h src/info.h\
          src/calendar.h src/preferences.h\
          src/ch_passwd.h src/passwd.h src/editor.h\
          src/about.h
SOURCES = src/gui.cpp src/main.cpp src/info.cpp\
          src/preferences.cpp src/calendar.cpp\
          src/ch_passwd.cpp src/passwd.cpp\
          src/editor.cpp src/about.cpp
RESOURCES = ../qshutdown.qrc
TRANSLATIONS = src/translations/qshutdown_de.ts
FORMS = src/ui/gui.ui src/ui/preferences.ui\
        src/ui/calendar.ui src/ui/ch_passwd.ui\
        src/ui/passwd.ui src/ui/editor.ui\
        src/ui/about.ui

!win32{
# install
target.path = /usr/bin
icon.files = src/pixmap/red_glasses.xpm
icon.path = /usr/share/pixmaps
translation.files = src/translations/*.qm
translation.path = /usr/share/qshutdown/translations
autostart1.files = autostart/qshutdown.desktop
autostart1.path = /usr/share/applications
autostart2.files = autostart/99qshutdown
autostart2.path = /usr/share/qshutdown/autostart

INSTALLS = target icon translation autostart1 autostart2

deinstall.depends = uninstall FORCE
deinstall.commands = rm -R /usr/share/qshutdown
QMAKE_EXTRA_TARGETS = deinstall
}
