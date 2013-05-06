/* qprogram-starter, a program to start programs or commands, with
   the option to log output and errors and to shutdown the system.
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

#include "preferences.h"
#include <QDir>
#include <QTimer>
#include <QFile>
#include <QDesktopServices>

Preferences::Preferences(QWidget *parent): QDialog(parent){

     setupUi(this);

     setupMsgBoxes();

     loadSettings();

     connect(buttonBox, SIGNAL(accepted()), this, SLOT(saveToConfFile()));
}

void Preferences::setupMsgBoxes(){
     msgBox = new QMessageBox(this);
     msgBox->setWindowTitle("Error");
     msgBox->setIcon(QMessageBox::Warning);
     msgBox->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
     msgBox->setInformativeText(tr("The File \"%1\" is not writable!\n"
       "Maybe you just don't have the permissions to do so.").arg(QSettings().fileName()));

     if(QSettings().value("first_start", true).toBool())
     {
       infoBox = new QMessageBox(this);
       infoBox->setWindowTitle("Please read this carefully!");
       infoBox->setIcon(QMessageBox::Information);
       infoBox->setInformativeText(tr("Welcome to qprogram-starter!\n"
         "If you want qprogram-starter to automatically shutdown the system "
         "and you are using the Gnome Shell, then you are likely to get a "
         "shutdown dialog from there. If you want a direct shutdown, then "
         "please consider going into the preferences and setting the shutdown "
         "method to ConsoleKit or something else.\n\nPlease feel free to visit "
         "https://launchpad.net/~hakaishi to report bugs or for anyting "
         "concerning translations."));
       infoBox->setStandardButtons(QMessageBox::Ok);
     }
}

void Preferences::showEvent(QShowEvent* show_pref){
     if(!QSettings().isWritable())
     {
       QTimer::singleShot(15000, msgBox, SLOT(close()));
       msgBox->show();
     }
     loadSettings();
     QDialog::showEvent(show_pref);
}

void Preferences::loadSettings(){
     if(QSettings().value("first_start", true).toBool())
     {
       infoBox->show();
       QSettings().setValue("first_start", false);
     }

     if(!QSettings().contains("shutdown_method"))
       QSettings().setValue("shutdown_method", 0);
     if(!QSettings().contains("CheckBoxes/atDate"))
       QSettings().setValue("CheckBoxes/atDate", false);
     if(!QSettings().contains("CheckBoxes/logging"))
       QSettings().setValue("CheckBoxes/logging", false);
     if(!QSettings().contains("CheckBoxes/shutdown"))
       QSettings().setValue("CheckBoxes/shutdown", false);
     if(!QSettings().contains("CheckBoxes/quitWithLastProcess"))
       QSettings().setValue("CheckBoxes/quitWithLastProcess", false);
     if(!QSettings().contains("CheckBoxes/text1"))
       QSettings().setValue("Text/text1", QString());
     if(!QSettings().contains("CheckBoxes/text2"))
       QSettings().setValue("Text/text2", QString());

//read settings
     comboBox->setCurrentIndex(QSettings().value("shutdown_method", 0).toInt());
}

void Preferences::saveToConfFile(){
     QSettings().setValue("shutdown_method",comboBox->currentIndex());
}
