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

#include "preferences.h"
#include <QDir>
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <QDesktopServices>

Preferences::Preferences(QWidget *parent): QDialog(parent){

     setupUi(this);

     isClosed = true;

     setWindowFlags(Qt::Window);    //always in front

/***************** load settings from the conf file *****************/

#ifdef Q_OS_WIN32
     lockS->setDisabled(true); //if there is a command for locking the display in Windows, remove this line
                               //and add the command to power.cpp
     file = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/qshutdown/qshutdown.conf";
#else //!Q_OS_WIN32
     file = QDir::homePath() + "/.qshutdown/qshutdown.conf";
#endif //Q_OS_WIN32
     settings = new QSettings(file, QSettings::NativeFormat);

     fonts = "Times New Roman";
     fontS1 = 13;
     fontS2 = 18;
     fontS3 = 11;

     msgBox = new QMessageBox(this);
     msgBox->setWindowTitle("Error");
     msgBox->setIcon(QMessageBox::Warning);
     msgBox->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
     msgBox->setInformativeText(tr("The File \"") + file + tr("\" is not writable!\n"
     "Maybe you just don't have the permissions to do so."));

     connect(buttonBox, SIGNAL(accepted()), this, SLOT(saveToConfFile()));
     connect(reset, SIGNAL(clicked(bool)), this, SLOT(resetSettings()));
     connect(font1Spin, SIGNAL(valueChanged(int)), this, SLOT(fontSize1Changed(int)));
     connect(font2Spin, SIGNAL(valueChanged(int)), this, SLOT(fontSize2Changed(int)));
     connect(font3Spin, SIGNAL(valueChanged(int)), this, SLOT(fontSize3Changed(int)));
     connect(fontComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(fontChanged(QString)));
     connect(buttonBox, SIGNAL(rejected()), this, SLOT(resetFont()));
     connect(confEditButton, SIGNAL(clicked(bool)), this, SIGNAL(editConf()));
     connect(this, SIGNAL(rejected()), this, SLOT(close()));

     loadSettings();
}

Preferences::~Preferences(){ delete settings; }

void Preferences::showEvent(QShowEvent* show_pref){
     isClosed = false;
     starting(); //sends SIGNAL starting()
     if(!settings->isWritable()){
       QTimer::singleShot(15000, msgBox, SLOT(close()));
       msgBox->show();
     }
     loadSettings();
     QDialog::showEvent(show_pref);
}

void Preferences::loadSettings(){
     if(settings->contains("PrefWindowSize/size"))
       resize(settings->value("PrefWindowSize/size").toSize());
     comboBox->setCurrentIndex(settings->value("Power/comboBox").toInt());
     timeEdit->setTime(QTime(settings->value("Time/time_hour").toInt(),settings->value("Time/time_minute").toInt()));
     spin->setValue(settings->value("Time/countdown_minutes").toInt());
     stopHide->setChecked(settings->value("Quit_on_close").toBool());
     countdown->setChecked(settings->value("Time/countdown_at_startup").toBool());
     hideMe->setChecked(settings->value("Hide_at_startup").toBool());
     fontComboBox->setCurrentFont(settings->value("Fonts/font_type").toString());
     font1Spin->setValue(settings->value("Fonts/font1").toInt());
     font2Spin->setValue(settings->value("Fonts/font2").toInt());
     font3Spin->setValue(settings->value("Fonts/font3").toInt());
     spinBox->setValue(settings->value("Logfile/size").toDouble());
     radio1->setChecked(settings->value("CheckBoxes/target_time").toBool());
     radio2->setChecked(settings->value("CheckBoxes/countdown").toBool());
     lock->setChecked(settings->value("CheckBoxes/lock").toBool());
     warn->setChecked(settings->value("CheckBoxes/warnings").toBool());
     log->setChecked(settings->value("Logfile/logging").toBool());
     lockS->setChecked(settings->value("Lock_screen").toBool());
     autostart->setChecked(settings->value("Autostart").toBool());

     lockMyScreen = settings->value("Lock_screen").toBool();
}

void Preferences::saveToConfFile(){
     if(settings->isWritable()){
       settings->setValue("Power/comboBox", comboBox->currentIndex());
       settings->setValue("Time/time_hour", timeEdit->time().hour());
       settings->setValue("Time/time_minute", timeEdit->time().minute());
       settings->setValue("Quit_on_close", stopHide->isChecked());
       settings->setValue("Time/countdown_at_startup", countdown->isChecked());
       settings->setValue("Hide_at_startup", hideMe->isChecked());
       settings->setValue("Time/countdown_minutes", spin->value());
       settings->setValue("Fonts/font_type", fontComboBox->currentText());
       settings->setValue("Fonts/font1", font1Spin->value());
       settings->setValue("Fonts/font2", font2Spin->value());
       settings->setValue("Fonts/font3", font3Spin->value());
       settings->setValue("Logfile/size", spinBox->value());
       settings->setValue("CheckBoxes/target_time", radio1->isChecked());
       settings->setValue("CheckBoxes/countdown", radio2->isChecked());
       settings->setValue("CheckBoxes/lock", lock->isChecked());
       settings->setValue("CheckBoxes/warnings", warn->isChecked());
       settings->setValue("Logfile/logging", log->isChecked());
       settings->setValue("Lock_screen", lockS->isChecked());
       settings->setValue("Autostart", autostart->isChecked());
     }
     autostartFile(); //to create or to delete the autostart file
     lockScreen();    //set lockMyScreen to true or false according to lockS
}

void Preferences::resetSettings(){
     if(settings->isWritable()){
       comboBox->setCurrentIndex(0);
       timeEdit->setTime(QTime(22,00));
       countdown->setChecked(false);
       stopHide->setChecked(false);
       hideMe->setChecked(false);
       spin->setValue(60);
       fontComboBox->setCurrentFont(QFont("Times New Roman"));
       font1Spin->setValue(13);
       font2Spin->setValue(18);
       font3Spin->setValue(11);
       spinBox->setValue(1.5);
       radio1->setChecked(false);
       radio2->setChecked(true);
       lock->setChecked(true);
       warn->setChecked(true);
       log->setChecked(false);
       lockS->setChecked(true);
     }
}

void Preferences::closeEvent(QCloseEvent* window_close){
     isClosed = true;
     finishing(); //sends SIGNAL finishing()
     if(settings->isWritable())
       settings->setValue("PrefWindowSize/size", size());

     QDialog::closeEvent(window_close);
}

bool Preferences::getClosed(){ return isClosed; }

bool Preferences::getQuitOnClose(){ return settings->value("Quit_on_close").toBool(); }

void Preferences::fontChanged(QString font){ fonts = font; changeFont(); }

void Preferences::fontSize1Changed(int f1){ fontS1 = f1; changeFont(); }

void Preferences::fontSize2Changed(int f2){ fontS2 = f2; changeFont(); }

void Preferences::fontSize3Changed(int f3){ fontS3 = f3; changeFont(); }

void Preferences::resetFont(){
     fonts = settings->value("Fonts/font_type").toString();
     fontS1 = settings->value("Fonts/font1").toInt();
     fontS2 = settings->value("Fonts/font2").toInt();
     fontS3 = settings->value("Fonts/font3").toInt();
     changeFont();
}

void Preferences::autostartFile(){
    #ifndef Q_OS_WIN32
     QFile autostartFile(QDir::homePath() + "/.config/autostart/qshutdown.desktop");
     if(settings->value("Autostart").toBool() && !autostartFile.exists()){
       if(!QDir(QDir::homePath() + "/.config/autostart").exists()){
         QDir dir(QDir::homePath() + "/.config/autostart");
         dir.mkdir(QDir::homePath() + "/.config/autostart");
       }
       if(!autostartFile.open(QIODevice::ReadWrite | QIODevice::Text)){
         QTextStream myOutput(stdout);
         myOutput << "E: Can not open qshutdown.conf!" << endl;
         return;
       }
         QString autostartContent("[Desktop Entry]\nName=qshutdown\n"
           "Name[de_DE]=qshutdown\nExec=qshutdown\nTerminal=false\n"
           "Type=Application\nIcon=red_glasses\nCategories=Utility");
         QTextStream out(&autostartFile);
         out << autostartContent;
         autostartFile.close();
     }
     if(autostartFile.exists() && !settings->value("Autostart").toBool())
       autostartFile.remove();
    #endif
}

void Preferences::lockScreen(){ lockMyScreen = lockS->isChecked(); }
