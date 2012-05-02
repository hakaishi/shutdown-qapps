/* qprogram-starter, a program to start programs or commands, with
   the option to log output and errors and to shutdown the system.
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

#include "gui.h"
#include <QMessageBox>
#include <QFile>

#ifndef Q_OS_WIN32
  #include <QtDBus>
#endif

Gui::Gui(QWidget *parent) : QWidget(parent){

     setupUi(this);

     myOutput = new QTextStream(stdout);

     shell = QProcess::systemEnvironment().filter("SHELL").first().remove("SHELL=");

     aborted = false;
     process2Started = false;

     dateEdit->setMinimumDate(QDate::currentDate());
     dateTimeTimer = new QTimer(this);
     dateTimeTimer->start(1000);

     timer = new QTimer(this);

     process1 = new QProcess(this);
     process2 = new QProcess(this);

     logBox1 = new QTextEdit;
     logBox1->setReadOnly(true);
     logBox1->resize(520,450);
     logBox1->setWindowTitle("error log 1");
     logBox1->setWindowModality(Qt::NonModal);

     logBox2 = new QTextEdit;
     logBox2->setReadOnly(true);
     logBox2->resize(520,450);
     logBox2->setWindowTitle("error log 2");
     logBox2->setWindowModality(Qt::NonModal);

   #ifdef Q_OS_WIN32
     file = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/qprogram-starter/qprogram-starter.conf";
   #else //!Q_OS_WIN32
     file = QDir::homePath() + "/.qprogram-starter/qprogram-starter.conf";
   #endif
     settings = new QSettings(file, QSettings::IniFormat);

     hintMsgBox = new QTextEdit;
     hintMsgBox->setReadOnly(true);
     hintMsgBox->resize(520,450);
     hintMsgBox->setWindowTitle("Info");
     hintMsgBox->setWindowModality(Qt::NonModal);
     hintMsgBox->setHtml(tr("The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.<br/>To start a program just type i.e. \"firefox\" or \"firefox www.google.com\" and then click on OK. Commands etc. can be linked by \"&&\" etc. <br/><br/>If the process is \"finished\" although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.<br/><br/>When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).<br/><br/>make examples:<br/>&nbsp;make -C /path/to/project<br/>&nbsp;make clean -C /path/to/project<br/><br/>About Errors:<br/>Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at <i>~/.qprogram-starter/</i>.<br/><br/>If the shutdown won't work, it means that \"sudo shutdown -P now\" is used. This needs root permissions. You can do the this:<br/><br/>Post the following in a terminal:<pre>EDITOR=nano sudo -E visudo</pre> and add this line:<pre>* ALL = NOPASSWD:/sbin/shutdown</pre> whereas * replaces the username or %groupname.<br/><br/>The configuration-file can be found at <i>~/.qprogram-starter/</i>."));

     connect(dateTimeTimer, SIGNAL(timeout()), this, SLOT(currentDateAndTime()));
     connect(startB, SIGNAL(clicked(bool)), this, SLOT(run()));
     connect(abortB, SIGNAL(clicked(bool)), this, SLOT(abortProcesses()));
     connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveData()));
     connect(timer, SIGNAL(timeout()), this, SLOT(check()));
     connect(browse1, SIGNAL(clicked(bool)), this, SLOT(getProgram1()));
     connect(browse2, SIGNAL(clicked(bool)), this, SLOT(getProgram2()));
     connect(process1, SIGNAL(readyReadStandardOutput()), this, SLOT(output1()));
     connect(process1, SIGNAL(readyReadStandardError()), this, SLOT(errorOutput1()));
     connect(process1, SIGNAL(finished(int)), this, SLOT(checkForProcess2()));
     connect(process1, SIGNAL(error(QProcess::ProcessError)), this, SLOT(message()));
     connect(process2, SIGNAL(readyReadStandardOutput()), this, SLOT(output2()));
     connect(process2, SIGNAL(readyReadStandardError()), this, SLOT(errorOutput2()));
     connect(process2, SIGNAL(finished(int)), this, SLOT(shutdown_or_message()));
     connect(process2, SIGNAL(error(QProcess::ProcessError)), this, SLOT(message()));
     connect(this, SIGNAL(finished()), this, SLOT(shutdown_or_message()));
     connect(hint, SIGNAL(clicked(bool)), this, SLOT(info_hint()));
     connect(showLogsButton, SIGNAL(clicked(bool)), this, SLOT(showLogs()));
}

Gui::~Gui(){ delete settings; delete hintMsgBox; }

void Gui::closeEvent(QCloseEvent* window_close){
     if(!settings->isWritable())
       *myOutput << "W: qprogram-starter.conf is not writable!" << endl;
     else
       settings->setValue("CheckBoxes/atDate", atDateCheckBox->isChecked());
       settings->setValue("CheckBoxes/logging", loggingCheckBox->isChecked());
       settings->setValue("CheckBoxes/shutdown", shutdownCheckBox->isChecked());
       settings->setValue("CheckBoxes/quitWithLasProcess", quitCheckBox->isChecked());
     qApp->quit();
     QWidget::closeEvent(window_close);
}

void Gui::currentDateAndTime(){
     if(dateEdit->date() == QDate::currentDate())
       timeEdit->setMinimumTime(QTime::currentTime());
     else
       timeEdit->setMinimumTime(QTime(00,00));
}

void Gui::info_hint(){ hintMsgBox->show(); }

void Gui::check(){ //To check if start time is reached
     secondsToTimeInTheFuture = QDateTime::currentDateTime().secsTo(timeInTheFuture);
     if(secondsToTimeInTheFuture <= 0){
       processArgs1 << "-c" << textEdit->toPlainText();
       process1->start(shell, processArgs1);
       timer->stop();
     }
}

void Gui::getProgram1(){
     program1 = QFileDialog::getOpenFileName(this, tr("Select a program"), "/usr/bin");
     textEdit->insertPlainText(program1);
     textEdit->setFocus();
}

void Gui::getProgram2(){
     program2 = QFileDialog::getOpenFileName(this, tr("Select a program"), "/usr/bin");
     textEdit2->insertPlainText(program2);
     textEdit2->setFocus();
}

void Gui::run(){ //To start either the timer or start the process
     if(!textEdit->toPlainText().isEmpty()){
       nextDate = dateEdit->dateTime();
       timeInTheFuture = nextDate.addSecs(timeEdit->time().hour()*3600 + timeEdit->time().minute()*60 + timeEdit->time().second());
       textEdit->setDisabled(true);
       atDateCheckBox->setDisabled(true);
       dateEdit->setDisabled(true);
       timeEdit->setDisabled(true);
       if(atDateCheckBox->isChecked())
         timer->start(1000);
       else{
         processArgs1 << "-c" << textEdit->toPlainText();
         process1->start(shell, processArgs1);
       }
     }
     else{
       QMessageBox msgBox;
       msgBox.setWindowTitle("Error");
       msgBox.setIcon(QMessageBox::Warning);
       msgBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
       msgBox.setInformativeText(tr("The first text edit is empty!"));
       QTimer::singleShot(6000, &msgBox, SLOT(close()));
       msgBox.exec();
     }
     outputProcess1 = "";
     outputProcess2 = "";
     errProcess1 = "";
     errProcess2 = "";
}

void Gui::abortProcesses(){
     timer->stop();
     aborted = true;

     process1->close();
     process2->close();

     processArgs1.clear();
     processArgs2.clear();

     QMessageBox msgBox;
     msgBox.setWindowTitle(tr("Information"));
     msgBox.setIcon(QMessageBox::Information);
     msgBox.setInformativeText(tr("Processes aborted"));
     msgBox.setWindowModality(Qt::NonModal);
     msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);
     QTimer::singleShot(10000, &msgBox, SLOT(close()));
     msgBox.exec();

     atDateCheckBox->setEnabled(true);
     if(atDateCheckBox->isChecked()){
       dateEdit->setEnabled(true);
       timeEdit->setEnabled(true);
     }
     textEdit->setEnabled(true);
     textEdit2->setEnabled(true);

     aborted = false;
}

void Gui::checkForProcess2(){ //check if there is a second command
     if(process1->exitCode()==0 && process1->exitStatus()==0 && process1->error()==5
       && !textEdit2->toPlainText().isEmpty() && !aborted){
       processArgs2 << "-c" << textEdit2->toPlainText();
       process2->start(shell, processArgs2);
       process2Started = true;
       textEdit2->setDisabled(true);
     }
     else
       finished();
}

void Gui::output1(){ //write output into a file if loggingCheckBox is checked
     QString string = QString::fromLocal8Bit(process1->readAllStandardOutput());
     outputProcess1 += string;

     if(loggingCheckBox->isChecked()){
       QFile outputLog1(QDir::homePath() + "/.qprogram-starter/outputLog1.txt");
       if(!outputLog1.open(QIODevice::Append))
         return;
       QTextStream str(&outputLog1);
       str << string;
       outputLog1.close();
     }
}

void Gui::output2(){ //write output into a file if loggingCheckBox is checked
     QString string = QString::fromLocal8Bit(process2->readAllStandardOutput());
     outputProcess2 += string;

     if(loggingCheckBox->isChecked()){
       QFile outputLog2(QDir::homePath() + "/.qprogram-starter/outputLog2.txt");
       if(!outputLog2.open(QIODevice::Append))
         return;
       QTextStream str(&outputLog2);
       str << string;
       outputLog2.close();
     }
}

void Gui::errorOutput1(){ //write error output into a file if loggingCheckBox is checked
     QString string = QString::fromLocal8Bit(process1->readAllStandardError());
     errProcess1 += string;

     if(loggingCheckBox->isChecked()){
       QFile errorLog1(QDir::homePath() + "/.qprogram-starter/errorLog1.txt");
       if(!errorLog1.open(QIODevice::Append))
         return;
       QTextStream str(&errorLog1);
       str << string;
       errorLog1.close();
     }
}

void Gui::errorOutput2(){ //write error output into a file if loggingCheckBox is checked
     QString string = QString::fromLocal8Bit(process2->readAllStandardError());
     errProcess2 += string;

     if(loggingCheckBox->isChecked()){
       QFile errorLog2(QDir::homePath() + "/.qprogram-starter/errorLog2.txt");
       if(!errorLog2.open(QIODevice::Append))
         return;
       QTextStream str(&errorLog2);
       str << string;
       errorLog2.close();
     }
}

void Gui::showLogs(){
     if(!outputProcess1.isEmpty() || !errProcess1.isEmpty()
       || !outputProcess2.isEmpty() || !errProcess2.isEmpty()){
       if(!outputProcess1.isEmpty())
         logBox1->append(outputProcess1);
       if(!errProcess1.isEmpty())
         logBox1->append(errProcess1);
       logBox1->show();

       if(process1->exitCode()==0 && process1->exitStatus()==0
         && process1->error()==5 && !textEdit2->toPlainText().isEmpty() && !aborted){
         if(!outputProcess2.isEmpty())
           logBox2->append(outputProcess2);
         if(!errProcess2.isEmpty())
           logBox2->append(errProcess2);
         logBox2->show();
       }
     }
}     

void Gui::shutdown_or_message(){
#ifndef Q_OS_WIN32
     if(shutdownCheckBox->isChecked() && !aborted){
       bool g = false; //gnome
       bool k = false; //kde
       bool g_pwr1 = false;
       bool g_pwr2 = false;
       bool hal = false;
       QDBusMessage response;

       QDBusInterface gnomeSessionManager("org.gnome.SessionManager",
         "/org/gnome/SessionManager", "org.gnome.SessionManager",
         QDBusConnection::sessionBus());
       response = gnomeSessionManager.call("RequestShutdown");
       if(response.type() == QDBusMessage::ErrorMessage){
         *myOutput << "W: " << response.errorName() << ": "
                   << response.errorMessage() << endl;
         g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh shutdown");
         g_pwr2 = QProcess::startDetached("gnome-power-cmd shutdown");
         if(!g_pwr1 && !g_pwr2)
           *myOutput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
                     << endl;
       }
       else
         g = true;

       if(!g && !g_pwr1 && !g_pwr2){
         QDBusInterface kdeSessionManager("org.kde.ksmserver", "/KSMServer",
           "org.kde.KSMServerInterface", QDBusConnection::sessionBus());
         response = kdeSessionManager.call("logout", 0, 2, 2);
         if(response.type() == QDBusMessage::ErrorMessage)
           *myOutput << "W: " << response.errorName() << ": "
                     << response.errorMessage() << endl;
         else
           k = true;
       }

       if(!g && !g_pwr1 && !g_pwr2 && !k){
         QDBusInterface powermanagement("org.freedesktop.Hal",
           "/org/freedesktop/Hal/devices/computer",
           "org.freedesktop.Hal.Device.SystemPowerManagement",
           QDBusConnection::systemBus());
         response = powermanagement.call("Shutdown");
         if(response.type() == QDBusMessage::ErrorMessage)
           *myOutput << "W: " << response.errorName() << ": "
                     << response.errorMessage() << endl;
         else
           hal = true;
       }

       if(!g && !g_pwr1 && !g_pwr2 && !k && !hal){
         QDBusInterface powermanagement("org.freedesktop.ConsoleKit",
           "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager",
           QDBusConnection::systemBus());
         response = powermanagement.call("Stop");
         if(response.type() == QDBusMessage::ErrorMessage){
           *myOutput << "W: " << response.errorName() << ": "
                     << response.errorMessage() << endl;
           QProcess::startDetached("sudo shutdown -P now");
         }
       }
     }
     else
       message();
#endif

     processArgs1.clear();
     processArgs2.clear();
}

void Gui::message(){
     if(!aborted){
       QMessageBox msgBox;
       if(process1->exitCode()==0 && process1->exitStatus()==0 && process1->error()==5){
         if(textEdit2->toPlainText().isEmpty()){
           msgBox.setWindowTitle(tr("Information"));
           msgBox.setIcon(QMessageBox::Information);
           msgBox.setInformativeText(tr("<b>process 1 finished!</b>"));
         }
       }
       if(process2Started && process2->exitCode()==0 && process2->exitStatus()==0 && process2->error()==5){
         msgBox.setWindowTitle(tr("Information"));
         msgBox.setIcon(QMessageBox::Information);
         msgBox.setInformativeText(tr("<b>process 1 & 2 finished!</b>"));
       }

       if((process1->exitCode()!=0 || process1->error()!=5) ||
          (process2->exitCode()!=0 || process2->error()!=5)){
         msgBox.setWindowTitle(tr("Error"));
         msgBox.setIcon(QMessageBox::Critical);
         if(process1->error()==0 || process2->error()==0){
           msgBox.setInformativeText(tr("<b>Failed to start!</b><br/>"
            "No such program or command."));
           if(loggingCheckBox->isChecked()){
             if(process1->error()==0){
               QFile errorLog1(QDir::homePath() + "/.qprogram-starter/errorLog1.txt");
               if(!errorLog1.open(QIODevice::Append))
                 return;
               QTextStream err1(&errorLog1);
               err1 << tr("\"%1\": Failed to start! No such program or "
                          "command.\n").arg(textEdit->toPlainText());
               errorLog1.close();
             }

             if(process2->error()==0){
               QFile errorLog2(QDir::homePath() + "/.qprogram-starter/errorLog2.txt");
               if(!errorLog2.open(QIODevice::Append))
                 return;
               QTextStream err2(&errorLog2);
               err2 << tr("\"%1\": Failed to start! No such program or "
                          "command.\n").arg(textEdit2->toPlainText());
               errorLog2.close();
             }
           }
         }
         else if(process1->error()==1 || process1->exitCode()==1)
           msgBox.setInformativeText(tr("<b>process 1 crashed!</b><br/>"
           "This could be caused by invalid parameters or options."));
         else if(process2->error()==1 || process2->exitCode()==1)
           msgBox.setInformativeText(tr("<b>process 2 crashed!</b><br/>"
           "This could be caused by invalid parameters or options."));
         else
           msgBox.setInformativeText(tr("<b>Unknown error!</b><br/>"
           "This could be caused by invalid parameters or options."));
       }
       msgBox.setWindowModality(Qt::NonModal);
       msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);
       QTimer::singleShot(10000, &msgBox, SLOT(close()));
       msgBox.exec();
     }

     atDateCheckBox->setEnabled(true);
     if(atDateCheckBox->isChecked()){
       dateEdit->setEnabled(true);
       timeEdit->setEnabled(true);
     }
     textEdit->setEnabled(true);
     textEdit2->setEnabled(true);

     if(quitCheckBox->isChecked() && !aborted)
       close();
}

void Gui::saveData(){
     settings->setValue("Text/text1", textEdit->toPlainText());
     settings->setValue("Text/text2", textEdit2->toPlainText());
}

void Gui::loadSettings(){
     if(!QFile::exists(file)){ //if path or file doesn't exist
       if(!settings->contains("CheckBoxes/atDate"))
         settings->setValue("CheckBoxes/atDate", false);
       if(!settings->contains("CheckBoxes/logging"))
         settings->setValue("CheckBoxes/logging", false);
       if(!settings->contains("CheckBoxes/shutdown"))
         settings->setValue("CheckBoxes/shutdown", false);
       if(!settings->contains("CheckBoxes/quitWithLasProcess"))
         settings->setValue("CheckBoxes/quitWithLasProcess", false);
       if(!settings->contains("CheckBoxes/text1"))
         settings->setValue("Text/text1", QString());
       if(!settings->contains("CheckBoxes/text2"))
         settings->setValue("Text/text2", QString());
     }

     atDateCheckBox->setChecked(settings->value("CheckBoxes/atDate").toBool());
     loggingCheckBox->setChecked(settings->value("CheckBoxes/logging").toBool());
     shutdownCheckBox->setChecked(settings->value("CheckBoxes/shutdown").toBool());
     quitCheckBox->setChecked(settings->value("CheckBoxes/quitWithLasProcess").toBool());
     textEdit->setText(settings->value("Text/text1").toString());
     textEdit2->setText(settings->value("Text/text2").toString());
}
