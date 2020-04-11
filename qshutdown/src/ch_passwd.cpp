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

#include "ch_passwd.h"
#include <QDir>
#include <QCryptographicHash>
#include <QDesktopServices>

ChangePassword::ChangePassword(QWidget *parent): QDialog(parent){

     setupUi(this);

     setWindowFlags(Qt::Window);    //always in front

     settings = new QSettings(this);

     if(settings->contains("Password")){
       oldPasswd->setEnabled(true);
       oldL->setEnabled(true);
     }

     msgBox1 = new QMessageBox(this);
     msgBox1->setWindowTitle("Error");
     msgBox1->setIcon(QMessageBox::Warning);
     msgBox1->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
     msgBox1->setInformativeText(tr("The current password is not correct!"));

     msgBox2 = new QMessageBox(this);
     msgBox2->setWindowTitle("Error");
     msgBox2->setIcon(QMessageBox::Warning);
     msgBox2->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
     msgBox2->setInformativeText(tr("The retyped password doesn't match!"));

     connect(buttonBox, SIGNAL(accepted()), this, SLOT(checkOldPW()));
}

ChangePassword::~ChangePassword(){ delete settings; }


void ChangePassword::checkOldPW(){
     if(settings->contains("Password")){
       if(settings->value("Password").toByteArray() == 
           QCryptographicHash::hash(oldPasswd->text().toUtf8(), QCryptographicHash::Sha1))
         checkNewPW();
       else
         msgBox1->exec();
     }
     else
       checkNewPW();
}

void ChangePassword::checkNewPW(){
     if(newPasswd->text() == retypedNewPasswd->text()){
       savePW();
       accept();
     }
     else
       msgBox2->exec();
}

void ChangePassword::savePW(){
     settings->setValue("Password", QCryptographicHash::hash(retypedNewPasswd->text().toUtf8(),
       QCryptographicHash::Sha1));
     updatePasswordGui();
     if(settings->contains("Password")){
       oldPasswd->setEnabled(true);
       oldL->setEnabled(true);
     }
     oldPasswd->clear();
     newPasswd->clear();
     retypedNewPasswd->clear();
}

void ChangePassword::closeEvent(QCloseEvent* close_ch_pw){
     oldPasswd->clear();
     newPasswd->clear();
     retypedNewPasswd->clear();
     QDialog::closeEvent(close_ch_pw);
}
