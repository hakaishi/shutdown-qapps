/* qprogram-starter, a program to start programs or commands, with
   the option to log output and errors and to shutdown the system.
 * Copyright (C) 2010-2023 Christian Metscher <hakaishi@web.de>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gui.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QSettings>

int main (int argc, char *argv[]){
     QApplication app(argc, argv);
     app.setApplicationName("qprogram-starter");
     app.setOrganizationName("shutdown_qapps");
     
     QSettings::setDefaultFormat(QSettings::IniFormat);

     //Qt translations
     QTranslator qtTranslator;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
     bool qtLanguageLoaded = qtTranslator.load("qt_" + QLocale::system().name(),
       QLibraryInfo::path(QLibraryInfo::TranslationsPath));
#else
     bool qtLanguageLoaded = qtTranslator.load("qt_" + QLocale::system().name(),
       QLibraryInfo::location(QLibraryInfo::TranslationsPath));
#endif
     app.installTranslator(&qtTranslator);
     Q_UNUSED(qtLanguageLoaded);

     //My translations
     QTranslator translator;
     QString trDir = "/usr/share/qprogram-starter/translations/";
     bool languageLoaded = translator.load(trDir + "qprogram-starter-" + QLocale::system().name());
     app.installTranslator(&translator);
     Q_UNUSED(languageLoaded);

     Gui window;
     window.loadSettings();
     window.show();
     return app.exec();
}
