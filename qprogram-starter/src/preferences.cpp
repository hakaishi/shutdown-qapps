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

#include "preferences.h"
#include <QDir>
#include <QTimer>
#include <QFile>
#include <QDesktopServices>

Preferences::Preferences(QWidget *parent): QDialog(parent){

     setupUi(this);

     QString file;

     settings = new QSettings(this);

     setupMsgBoxes();

     loadSettings();

     connect(buttonBox, SIGNAL(accepted()), this, SLOT(saveToConfFile()));
     connect(clearHistBtn, SIGNAL(clicked(bool)), this, SLOT(clearHistory()));
}

Preferences::~Preferences(){ delete settings; }

void Preferences::setupMsgBoxes(){
     msgBox = new QMessageBox(this);
     msgBox->setWindowTitle(tr("Error"));
     msgBox->setIcon(QMessageBox::Warning);
     msgBox->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
     msgBox->setInformativeText(tr("The File \"%1\" is not writable!\n"
       "Maybe you just don't have the permissions to do so.").arg(settings->fileName()));

     if(settings->value("first_start", true).toBool())
     {
       infoBox = new QMessageBox(this);
       infoBox->setWindowTitle(tr("Please read this carefully!"));
       infoBox->setIcon(QMessageBox::Information);
       infoBox->setInformativeText(tr("Welcome to qprogram-starter!\n"
         "If you want qprogram-starter to automatically shutdown the system "
         "and you are using the Gnome Shell, then you are likely to get a "
         "shutdown dialog from there. If you want a direct shutdown, then "
         "please consider going into the preferences and setting the shutdown "
         "method to ConsoleKit or something else.\n\nPlease feel free to visit "
         "https://launchpad.net/~hakaishi to report bugs or for anything "
         "concerning translations."));
       infoBox->setStandardButtons(QMessageBox::Ok);
     }
}

void Preferences::showEvent(QShowEvent* show_pref){
     if(!settings->isWritable())
     {
       QTimer::singleShot(15000, msgBox, SLOT(close()));
       msgBox->show();
     }
     loadSettings();
     QDialog::showEvent(show_pref);
}

void Preferences::loadSettings(){
     if(settings->value("first_start", true).toBool())
     {
       infoBox->show();
       settings->setValue("first_start", false);
     }

     if(!settings->contains("shutdown_method"))
       settings->setValue("shutdown_method", 0);
     if(!settings->contains("reboot_method"))
       settings->setValue("reboot_method", 0);
     if(!settings->contains("suspend_method"))
       settings->setValue("suspend_method", 0);
     if(!settings->contains("hibernate_method"))
       settings->setValue("hibernate_method", 0);
     if(!settings->contains("countdown_before_action"))
       settings->setValue("countdown_before_action", 10);
     if(!settings->contains("CheckBoxes/atDate"))
       settings->setValue("CheckBoxes/atDate", false);
     if(!settings->contains("CheckBoxes/logging"))
       settings->setValue("CheckBoxes/logging", false);
     if(!settings->contains("CheckBoxes/shutdown"))
       settings->setValue("CheckBoxes/shutdown", false);
     if(!settings->contains("CheckBoxes/no_quit_action_or_shutdown_on_error"))
       settings->setValue("CheckBoxes/no_quit_action_or_shutdown_on_error", false);
     if(!settings->contains("CheckBoxes/quitWithLastProcess"))
       settings->setValue("CheckBoxes/quitWithLastProcess", false);
     if(!settings->contains("Text/text"))
       settings->setValue("Text/text", QString());
     if(!settings->contains("History/max"))
        settings->setValue("History/max", 10);

//read settings
     shutdownCB->setCurrentIndex(settings->value("shutdown_method", 0).toInt());
     rebootCB->setCurrentIndex(settings->value("reboot_method", 0).toInt());
     suspendCB->setCurrentIndex(settings->value("suspend_method", 0).toInt());
     hibernateCB->setCurrentIndex(settings->value("hibernate_method", 0).toInt());
     maxHistSpin->setValue(settings->value("History/max", 10).toInt());
     countdownSpin->setValue(settings->value("countdown_before_action", 10).toInt());
     noActionCB->setChecked(settings->value("CheckBoxes/no_quit_action_or_shutdown_on_error", false).toBool());
}

void Preferences::saveToConfFile(){
     settings->setValue("shutdown_method",shutdownCB->currentIndex());
     settings->setValue("reboot_method",rebootCB->currentIndex());
     settings->setValue("suspend_method",suspendCB->currentIndex());
     settings->setValue("hibernate_method",hibernateCB->currentIndex());
     settings->setValue("History/max", maxHistSpin->value());
     settings->setValue("countdown_before_action", countdownSpin->value());
     settings->setValue("CheckBoxes/no_quit_action_or_shutdown_on_error", noActionCB->isChecked());
}

void Preferences::clearHistory(){
    settings->setValue("History/text", QString()); 
    
    histBox = new QMessageBox(this);
    histBox->setWindowTitle(tr("Information"));
    histBox->setIcon(QMessageBox::Information);
    histBox->setInformativeText(tr("History cleared!"));
    histBox->setWindowModality(Qt::NonModal);
    histBox->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
    QTimer::singleShot(10000, histBox, SLOT(close()));
    histBox->show();
}
