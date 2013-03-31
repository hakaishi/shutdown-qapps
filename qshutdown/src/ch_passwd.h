/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
 * Copyright (C) 2010-2013 Christian Metscher <hakaishi@web.de>

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
#ifndef CH_PASSWD_H
#define CH_PASSWD_H

#include "ui_ch_passwd.h"
#include <QMessageBox>
#include <QSettings>

class ChangePassword : public QDialog, public Ui::ChangePassword {
    Q_OBJECT
 
    public:
     ChangePassword(QWidget *parent = 0);
     ~ChangePassword();

    signals:
     void updatePasswordGui();

    private:
     QSettings   *settings;
     QString     file;
     QMessageBox *msgBox1, *msgBox2;

    private slots:
     void checkOldPW();
     void checkNewPW();
     void savePW();

    protected:
     virtual void closeEvent(QCloseEvent* close_ch_pw);

};

#endif //CH_PASSWD_H
