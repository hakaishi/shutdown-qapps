/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
 * Copyright (C) 2010-2011 Christian Metscher <hakaishi@web.de>

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

#include "passwd.h"
#include "ch_passwd.h"
#include <QDir>
#include <QCryptographicHash>
#include <QDesktopServices>

PassWord::PassWord(QWidget *parent): QDialog(parent){

     setupUi(this);

     isClosed = true;

     setWindowFlags(Qt::Window);    //always in front

#ifdef Q_OS_WIN32
     file = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/qshutdown/qshutdown.conf";
#else //!Q_OS_WIN32
     file = QDir::homePath() + "/.qshutdown/qshutdown.conf";
#endif //Q_OS_WIN32
     settings = new QSettings(file, QSettings::IniFormat);

     msgBox = new QMessageBox(this);
     msgBox->setWindowTitle("Error");
     msgBox->setIcon(QMessageBox::Warning);
     msgBox->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
     msgBox->setInformativeText(tr("The password is not correct!"));

     chPW = new ChangePassword(this);

     update(); //enable password line if a password was set

     passwdLineEdit->setFocus();

     connect(passwdLineEdit, SIGNAL(returnPressed()), this, SLOT(checkPW()));
     connect(buttonBox, SIGNAL(accepted()), this, SLOT(checkPW()));
     connect(changePasswdButton, SIGNAL(clicked(bool)), chPW, SLOT(show()));
     connect(chPW, SIGNAL(updatePasswordGui()), this, SLOT(update()));
}

PassWord::~PassWord(){ delete settings; }

void PassWord::checkPW(){
     if(settings->value("Password").toByteArray() == 
         QCryptographicHash::hash(passwdLineEdit->text().toUtf8(), QCryptographicHash::Sha1)){
                                   //check if the entered password matches the saved one
       success();
       passwdLineEdit->clear();
       close();
     }
     else
       msgBox->show();
}

void PassWord::update(){
     if(settings->contains("Password")){
       label->setEnabled(true);
       passwdLineEdit->setEnabled(true);
       changePasswdButton->setText(tr("&Change password"));
     }
}

void PassWord::showEvent(QShowEvent* show_pw){
     isClosed = false;
     starting();
     QWidget::showEvent(show_pw);
}

void PassWord::closeEvent(QCloseEvent* close_pw){
     passwdLineEdit->clear();
     isClosed = true;
     finishing();
     QWidget::closeEvent(close_pw);
}

bool PassWord::getClosed(){ return isClosed; }
