/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
 * Copyright (C) 2010-2019 Christian Metscher <hakaishi@web.de>

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
#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "ui_preferences.h"
#include <QSettings>
#include <QMessageBox>

class Preferences : public QDialog, public Ui::Preferences {
     Q_OBJECT
 
    public:
     Preferences(QWidget *parent = 0);
     ~Preferences();
     QString fonts;
     QString myShutdown, myReboot, mySuspend, myHibernate;
     QString userDef1S, userDef2S, userDef3S, userDef4S;
     int fontS1, fontS2, fontS3;
     bool getClosed();
     bool lockMyScreen;

    private:
     bool        isClosed;
     QString     file;
     QSettings   *settings;
     QMessageBox *msgBox, *infoBox;

    private slots:
     void loadSettings();
     void saveToConfFile();
     void resetSettings();
     void fontChanged(QString font);
     void resetFont();
     void fontSize1Changed(int f1);
     void fontSize2Changed(int f2);
     void fontSize3Changed(int f3);
     void lockScreen();
     void enableUserDef1();
     void enableUserDef2();
     void enableUserDef3();
     void enableUserDef4();
     void setFocusToUserDef();

    public slots:
     void autostartFile();

    signals:
     void starting();
     void finishing();
     void changeFont();
     void editConf();
     void removeTrayIcon(bool);

    protected:
     virtual void showEvent(QShowEvent* show_pref);
     virtual void closeEvent(QCloseEvent* close_pref);
};

#endif //PREFERENCES_H
