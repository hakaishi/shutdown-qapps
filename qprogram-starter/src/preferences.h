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
     QSettings *settings;

    private:
     QMessageBox *msgBox;
     QMessageBox *infoBox;
     QMessageBox *histBox;

    private slots:
     void setupMsgBoxes();
     void loadSettings();
     void saveToConfFile();
     void clearHistory();

    protected:
     virtual void showEvent(QShowEvent* show_pref);
};

#endif //PREFERENCES_H
