!win32{
QT += dbus
}
TEMPLATE = app
TARGET = bin/qprogram-starter
DEPENDPATH = . src src/translations
INCLUDEPATH = . src
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

system(lrelease qprogram-starter.pro)

QMAKE_DISTCLEAN = src/translations/*.qm

# Input
HEADERS = src/gui.h
FORMS = src/ui/gui.ui
SOURCES = src/main.cpp src/gui.cpp
RESOURCES = ../qprogram-starter.qrc
TRANSLATIONS = src/translations/qprogram-starter_de.ts

# install
target.path = /usr/bin
translation.files = src/translations/*.qm
translation.path = /usr/share/qprogram-starter/translations
autostart.files = autostart/qprogram-starter.desktop
autostart.path = /usr/share/applications
icon.files = src/pixmap/qprogram-starter.xpm
icon.path = /usr/share/pixmaps

INSTALLS = target translation autostart icon

deinstall.depends = uninstall FORCE
deinstall.commands = rmdir /usr/share/qprogram-starter
QMAKE_EXTRA_TARGETS = deinstall
