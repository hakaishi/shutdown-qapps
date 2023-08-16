/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
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
#ifndef PASSWD_H
#define PASSWD_H

#include "ui_passwd.h"
#include <QMessageBox>
#include <QSettings>

class ChangePassword;

class PassWord : public QDialog, public Ui::PassWord {
    Q_OBJECT
 
    public:
     PassWord(QWidget *parent = 0);
     ~PassWord();
     bool getClosed();

    signals:
     void success();
     void starting();
     void finishing();

    private:
     QSettings      *settings;
     QString        file;
     QMessageBox    *msgBox;
     ChangePassword *chPW;
     bool           isClosed;

    private slots:
     void checkPW();
     void update();

    protected:
     virtual void showEvent(QShowEvent* show_pw);
     virtual void closeEvent(QCloseEvent* close_pw);
};

#endif //PASSWD_H
