/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
 * Copyright (C) 2010-2014 Christian Metscher <hakaishi@web.de>

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

     setWindowFlags(Qt::Window);

   //Seconds won't be recognized, thus removing them (just in case).
     QString timeEditFormat;
     timeEditFormat = timeEdit->displayFormat();
     if(timeEditFormat.contains(":ss"))
       timeEditFormat.replace(QString(":ss"), QString(""));
     if(timeEditFormat.contains(":s"))
       timeEditFormat.replace(QString(":s"), QString(""));
     timeEdit->setDisplayFormat(timeEditFormat);

/***************** load settings from the conf file *****************/

#ifdef Q_OS_WIN32
     lockS->setDisabled(true); //if there is a command for locking the display in Windows, remove this line
                               //and add the command to power.cpp
     file = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/qshutdown/qshutdown.conf";
#else //!Q_OS_WIN32
     file = QDir::homePath() + "/.qshutdown/qshutdown.conf";
#endif //Q_OS_WIN32
     settings = new QSettings(file, QSettings::IniFormat);

#ifdef Q_OS_WIN32
     fonts = "Times New Roman";
     fontS1 = 13;
     fontS2 = 18;
     fontS3 = 11;
#else
     fonts = "DejaVu Sans";
     fontS1 = 11;
     fontS2 = 15;
     fontS3 = 9;
#endif

     userDef1S = tr("Please input an user specified command for shutdown here");
     userDef2S = tr("Please input an user specified command for reboot here");
     userDef3S = tr("Please input an user specified command for suspend here");
     userDef4S = tr("Please input an user specified command for hibernate here");

     msgBox = new QMessageBox(this);
     msgBox->setWindowTitle(tr("Error"));
     msgBox->setIcon(QMessageBox::Warning);
     msgBox->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
     msgBox->setInformativeText(tr("The File \"%1\" is not writable!\n"
     "Maybe you just don't have the permissions to do so.").arg(file));

     if(QSettings().value("first_start", true).toBool())
     {
       infoBox = new QMessageBox(this);
       infoBox->setWindowTitle(tr("Please read this carefully!"));
       infoBox->setIcon(QMessageBox::Information);
       infoBox->setInformativeText(tr("Welcome to qshutdown!\n"
         "If you want qshutdown e.g. to shutdown the system "
         "and you are using the Gnome Shell, then you are likely to get a "
         "shutdown dialog from there. If you want a direct shutdown, then "
         "please consider going into the preferences and setting the shutdown "
         "method to ConsoleKit or something else.\n\nPlease feel free to visit "
         "https://launchpad.net/~hakaishi to report bugs or for anyting "
         "concerning translations."));
       infoBox->setStandardButtons(QMessageBox::Ok);
       infoBox->show();
       QSettings().setValue("first_start", false);
     }

     connect(this, SIGNAL(accepted()), this, SLOT(saveToConfFile()));
     connect(reset, SIGNAL(clicked(bool)), this, SLOT(resetSettings()));
     connect(font1Spin, SIGNAL(valueChanged(int)), this, SLOT(fontSize1Changed(int)));
     connect(font2Spin, SIGNAL(valueChanged(int)), this, SLOT(fontSize2Changed(int)));
     connect(font3Spin, SIGNAL(valueChanged(int)), this, SLOT(fontSize3Changed(int)));
     connect(fontComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(fontChanged(QString)));
     connect(confEditButton, SIGNAL(clicked(bool)), this, SIGNAL(editConf()));
     connect(shutdownM, SIGNAL(currentIndexChanged(int)), this, SLOT(enableUserDef1()));
     connect(rebootM, SIGNAL(currentIndexChanged(int)), this, SLOT(enableUserDef2()));
     connect(suspendM, SIGNAL(currentIndexChanged(int)), this, SLOT(enableUserDef3()));
     connect(hibernateM, SIGNAL(currentIndexChanged(int)), this, SLOT(enableUserDef4()));
     connect(disableTray, SIGNAL(toggled(bool)), this, SIGNAL(removeTrayIcon(bool)));

     loadSettings();

     if(!QFile::exists(file))
       saveToConfFile();

     if(userDef1->isEnabled())
       myShutdown = userDef1->toPlainText();
     if(userDef2->isEnabled())
       myReboot = userDef2->toPlainText();
     if(userDef3->isEnabled())
       mySuspend = userDef3->toPlainText();
     if(userDef4->isEnabled())
       myHibernate = userDef4->toPlainText();
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

void Preferences::setFocusToUserDef(){
     if(userDef4->isEnabled())
       userDef4->setFocus();
     if(userDef3->isEnabled())
       userDef3->setFocus();
     if(userDef2->isEnabled())
       userDef2->setFocus();
     if(userDef1->isEnabled())
       userDef1->setFocus();
}

void Preferences::enableUserDef1(){
     if(shutdownM->currentIndex() == 6){
       userDef1->setEnabled(true);
       userDef1->setFocus();
       if(userDef1->toPlainText() == userDef1S)
         userDef1->clear();
     }
     else{
       userDef1->setEnabled(false);
       if(userDef1->toPlainText() == "")
         userDef1->setPlainText(userDef1S);
       setFocusToUserDef();
     }
}

void Preferences::enableUserDef2(){
     if(rebootM->currentIndex() == 6){
       userDef2->setEnabled(true);
       userDef2->setFocus();
       if(userDef2->toPlainText() == userDef2S)
         userDef2->clear();
     }
     else{
       userDef2->setEnabled(false);
       if(userDef2->toPlainText() == "")
         userDef2->setPlainText(userDef2S);
       setFocusToUserDef();
     }
}

void Preferences::enableUserDef3(){
     if(suspendM->currentIndex() == 5){
       userDef3->setEnabled(true);
       userDef3->setFocus();
       if(userDef3->toPlainText() == userDef3S)
         userDef3->clear();
     }
     else{
       userDef3->setEnabled(false);
       if(userDef3->toPlainText() == "")
         userDef3->setPlainText(userDef3S);
       setFocusToUserDef();
     }
}

void Preferences::enableUserDef4(){
     if(hibernateM->currentIndex() == 5){
       userDef4->setEnabled(true);
       userDef4->setFocus();
       if(userDef4->toPlainText() == userDef4S)
         userDef4->clear();
     }
     else{
       userDef4->setEnabled(false);
       if(userDef4->toPlainText() == "")
         userDef4->setPlainText(userDef4S);
       setFocusToUserDef();
     }
}

void Preferences::loadSettings(){
     if(settings->contains("PrefWindowSize/size"))
       resize(settings->value("PrefWindowSize/size").toSize());
     comboBox->setCurrentIndex(settings->value("Power/comboBox",0).toInt());
     timeEdit->setTime(QTime(settings->value("Time/time_hour",22).toInt(),settings->value("Time/time_minute",00).toInt()));
     spin->setValue(settings->value("Time/countdown_minutes",60).toInt());
     quitOnCloseMain->setChecked(settings->value("Quit_on_close",false).toBool());
     countdown->setChecked(settings->value("Time/countdown_at_startup",false).toBool());
     hideMe->setChecked(settings->value("Hide_at_startup",false).toBool());
     fontComboBox->setCurrentFont(settings->value("Fonts/font_type",fonts).toString());
     font1Spin->setValue(settings->value("Fonts/font1",fontS1).toInt());
     font2Spin->setValue(settings->value("Fonts/font2",fontS2).toInt());
     font3Spin->setValue(settings->value("Fonts/font3",fontS3).toInt());
     spinBox->setValue(settings->value("Logfile/size",1.5).toDouble());
     disableTray->setChecked(settings->value("CheckBoxes/Disable_tray_icon", false).toBool());
     radio1->setChecked(settings->value("CheckBoxes/target_time",false).toBool());
     radio2->setChecked(settings->value("CheckBoxes/countdown",true).toBool());
     lock->setChecked(settings->value("CheckBoxes/lock",true).toBool());
     warn->setChecked(settings->value("CheckBoxes/warnings",true).toBool());
     log->setChecked(settings->value("Logfile/logging",false).toBool());
     lockS->setChecked(settings->value("Lock_screen",true).toBool());
     autostart->setChecked(settings->value("Autostart").toBool());
     shutdownM->setCurrentIndex(settings->value("Methods/shutdown",0).toInt());
     userDef1->setPlainText(settings->value("Methods/myShutdown",userDef1S).toString());
     rebootM->setCurrentIndex(settings->value("Methods/reboot",0).toInt());
     userDef2->setPlainText(settings->value("Methods/myReboot",userDef2S).toString());
     suspendM->setCurrentIndex(settings->value("Methods/suspend",0).toInt());
     userDef3->setPlainText(settings->value("Methods/mySuspend",userDef3S).toString());
     hibernateM->setCurrentIndex(settings->value("Methods/hibernate",0).toInt());
     userDef4->setPlainText(settings->value("Methods/myHibernate",userDef4S).toString());
     lockMyScreen = settings->value("Lock_screen").toBool();
     quitAfterCountdown->setChecked(settings->value("Quit_after_countdown_ended",false).toBool());
}

void Preferences::saveToConfFile(){
     if(settings->isWritable()){
       settings->setValue("Power/comboBox",comboBox->currentIndex());
       settings->setValue("Time/time_hour",timeEdit->time().hour());
       settings->setValue("Time/time_minute",timeEdit->time().minute());
       settings->setValue("Quit_on_close",quitOnCloseMain->isChecked());
       settings->setValue("Time/countdown_at_startup",countdown->isChecked());
       settings->setValue("Hide_at_startup",hideMe->isChecked());
       settings->setValue("Time/countdown_minutes",spin->value());
       settings->setValue("Fonts/font_type",fontComboBox->currentText());
       settings->setValue("Fonts/font1",font1Spin->value());
       settings->setValue("Fonts/font2",font2Spin->value());
       settings->setValue("Fonts/font3",font3Spin->value());
       settings->setValue("Logfile/size",spinBox->value());
       settings->setValue("CheckBoxes/Disable_tray_icon",disableTray->isChecked());
       settings->setValue("CheckBoxes/target_time",radio1->isChecked());
       settings->setValue("CheckBoxes/countdown",radio2->isChecked());
       settings->setValue("CheckBoxes/lock",lock->isChecked());
       settings->setValue("CheckBoxes/warnings",warn->isChecked());
       settings->setValue("Logfile/logging",log->isChecked());
       settings->setValue("Lock_screen",lockS->isChecked());
       settings->setValue("Autostart",autostart->isChecked());
       settings->setValue("Methods/shutdown",shutdownM->currentIndex());
       settings->setValue("Methods/myShutdown",userDef1->toPlainText());
       settings->setValue("Methods/reboot",rebootM->currentIndex());
       settings->setValue("Methods/myReboot",userDef2->toPlainText());
       settings->setValue("Methods/suspend",suspendM->currentIndex());
       settings->setValue("Methods/mySuspend",userDef3->toPlainText());
       settings->setValue("Methods/hibernate",hibernateM->currentIndex());
       settings->setValue("Methods/myHibernate",userDef4->toPlainText());
       settings->setValue("Quit_after_countdown_ended",quitAfterCountdown->isChecked());
     }
     autostartFile(); //to create or to delete the autostart file
     lockScreen();    //set lockMyScreen to true or false according to lockS

     if(userDef1->isEnabled())
       myShutdown = userDef1->toPlainText();
     else myShutdown = "";
     if(userDef2->isEnabled())
       myReboot = userDef2->toPlainText();
     else myReboot = "";
     if(userDef3->isEnabled())
       mySuspend = userDef3->toPlainText();
     else mySuspend = "";
     if(userDef4->isEnabled())
       myHibernate = userDef4->toPlainText();
     else mySuspend = "";

     this->close();
}

void Preferences::resetSettings(){
     if(settings->isWritable()){
       comboBox->setCurrentIndex(0);
       timeEdit->setTime(QTime(22,00));
       countdown->setChecked(false);
       disableTray->setChecked(false);
       quitOnCloseMain->setChecked(false);
       hideMe->setChecked(false);
       spin->setValue(60);
       fontComboBox->setCurrentFont(QFont(fonts));
       font1Spin->setValue(fontS1);
       font2Spin->setValue(fontS2);
       font3Spin->setValue(fontS3);
       spinBox->setValue(1.5);
       radio1->setChecked(false);
       radio2->setChecked(true);
       lock->setChecked(true);
       warn->setChecked(true);
       log->setChecked(false);
       lockS->setChecked(true);
       shutdownM->setCurrentIndex(0);
       rebootM->setCurrentIndex(0);
       suspendM->setCurrentIndex(0);
       hibernateM->setCurrentIndex(0);
       userDef1->setPlainText(userDef1S);
       userDef2->setPlainText(userDef2S);
       userDef3->setPlainText(userDef3S);
       userDef4->setPlainText(userDef4S);
       quitAfterCountdown->setChecked(false);
     }
}

void Preferences::closeEvent(QCloseEvent* close_pref){
     isClosed = true;
     finishing(); //sends SIGNAL finishing()
     if(settings->isWritable())
       settings->setValue("PrefWindowSize/size",size());
     resetFont();
     QDialog::closeEvent(close_pref);
}

bool Preferences::getClosed(){ return isClosed; }

void Preferences::fontChanged(QString font){ fonts = font; changeFont(); }

void Preferences::fontSize1Changed(int f1){ fontS1 = f1; changeFont(); }

void Preferences::fontSize2Changed(int f2){ fontS2 = f2; changeFont(); }

void Preferences::fontSize3Changed(int f3){ fontS3 = f3; changeFont(); }

void Preferences::resetFont(){
     fonts = settings->value("Fonts/font_type","Times New Roman").toString();
     fontS1 = settings->value("Fonts/font1",13).toInt();
     fontS2 = settings->value("Fonts/font2",18).toInt();
     fontS3 = settings->value("Fonts/font3",11).toInt();
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
