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

QT += widgets gui

system(lrelease qprogram-starter.pro)

QMAKE_DISTCLEAN = src/translations/*.qm

# Input
HEADERS = src/gui.h src/preferences.h
FORMS = src/ui/gui.ui src/ui/preferences.ui
SOURCES = src/main.cpp src/gui.cpp src/preferences.cpp
RESOURCES = ../qprogram-starter.qrc
TRANSLATIONS = src/translations/qprogram-starter-ast.ts\
               src/translations/qprogram-starter-bs.ts\
               src/translations/qprogram-starter-de.ts\
               src/translations/qprogram-starter-en_GB.ts\
               src/translations/qprogram-starter-es.ts\
               src/translations/qprogram-starter-gl.ts\
               src/translations/qprogram-starter-hr.ts\
               src/translations/qprogram-starter-it.ts\
               src/translations/qprogram-starter-ms.ts\
               src/translations/qprogram-starter-pl.ts\
               src/translations/qprogram-starter-ro.ts\
               src/translations/qprogram-starter-uk.ts

# install
target.path = /usr/bin
translation.files = src/translations/*.qm
translation.path = /usr/share/qprogram-starter/translations
autostart.files = autostart/qprogram-starter.desktop
autostart.path = /usr/share/applications
icon.files = src/pixmap/qprogram-starter.xpm
icon.path = /usr/share/icons/hicolor/32x32/apps

INSTALLS = target translation autostart icon

deinstall.depends = uninstall FORCE
deinstall.commands = rmdir /usr/share/qprogram-starter
QMAKE_EXTRA_TARGETS = deinstall
