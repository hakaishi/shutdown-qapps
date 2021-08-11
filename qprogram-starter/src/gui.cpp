/* qprogram-starter, a program to start programs or commands, with
   the option to log output and errors and to shutdown the system.
 * Copyright (C) 2010-2020 Christian Metscher <hakaishi@web.de>

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
#include "preferences.h"
#include "history.h"
#include "power.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>

#ifndef Q_OS_WIN32
  #include <QtDBus>
#endif

Gui::Gui(){

     setupUi(this);

     pref = new Preferences(this);
     
     history = new History(this);

     myOutput = new QTextStream(stdout);

     if(!QProcessEnvironment().isEmpty())
        shell = QProcess::systemEnvironment().filter("SHELL").first().remove("SHELL=");
     if(shell.isEmpty() && QFile("/bin/bash").exists())
        shell = "/bin/bash";
     else
       *myOutput << "E: No shells found! qprogram-starter might not work as expected...";

   //Versioning
     QFile versionFile(":version");
     versionFile.open(QIODevice::ReadOnly | QIODevice::Text);
     QTextStream in(&versionFile);
     statusBar()->showMessage(tr("Version ") + in.readLine(),15000);
     versionFile.close();
     
     processes = new QList<QProcess* >;
     processArgs = new QStringList;
     
     messages = new QMessageBox;
     connect(messages, SIGNAL(finished(int)), this, SLOT(handleMessageEvent(int)));

     dateEdit->setMinimumDate(QDate::currentDate());
     dateTimeTimer = new QTimer(this);
     dateTimeTimer->start(1000);

     timer = new QTimer(this);
     
     countdown = new QTimer(this);
     countdown->setSingleShot(true);
     updCountdown = new QTimer(this);
     countdownInt = 0;

     logBox = new QTextEdit;
     logBox->setReadOnly(true);
     logBox->resize(600,400);
     logBox->setWindowTitle(tr("Log"));
     logBox->setWindowModality(Qt::NonModal);

     hintMsgBox = new QTextEdit;
     hintMsgBox->setReadOnly(true);
     hintMsgBox->resize(600,400);
     hintMsgBox->setWindowTitle(tr("Info"));
     hintMsgBox->setWindowModality(Qt::NonModal);
     hintMsgBox->setHtml(tr("<b>General:</b><br/>Each line in the text editor will be executed as one separate process. Put a backslash at the end of the line for a multiline command.<br/><br/>The message boxes will close themselves after 10 seconds.<br/>To start a program just type i.e. \"firefox\" or \"firefox www.google.com\" and then click on Start. Commands etc. can be linked by \"&&\" etc. <br/><br/>If the process is \"finished\" although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occur for some programs like gedit, firefox or gnome-terminal if they are already running.<br/><br/>When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).<br/><br/><b>Files:</b><br/>The configuration-file can be found at <i>%2</i>.<br/>The log files can be found at <i>%1</i>.<br/><br/><b>make examples:</b><br/>&nbsp;make -C /path/to/project<br/>&nbsp;make clean -C /path/to/project<br/><br/><b>About Errors:</b><br/>Because almost every program gives a different error code, it is impossible to say what happened. So just log the output and see what kind of error occurred. The output files can be found at <i>%1</i>.<br/><br/>If the shutdown won't work, it might mean that \"sudo shutdown -P now\" is used. This needs admin permissions. You can do the this:<br/><br/>Post the following in a terminal:<pre>EDITOR=nano sudo -E visudo</pre> and add this line:<pre>* ALL = NOPASSWD:/sbin/shutdown</pre> whereas * replaces the username or %groupname.")
                    #if QT_VERSION >= 0x060000
     .arg(QDir().toNativeSeparators(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first()))
                    #else
                         .arg(QDir().toNativeSeparators(QStandardPaths::standardLocations(QStandardPaths::DataLocation).first()))
                    #endif
     .arg(QSettings().fileName()));

     connect(action_Configure, SIGNAL(triggered(bool)), pref, SLOT(show()));
     connect(dateTimeTimer, SIGNAL(timeout()), this, SLOT(currentDateAndTime()));
     connect(startB, SIGNAL(clicked(bool)), this, SLOT(run()));
     connect(abortB, SIGNAL(clicked(bool)), this, SLOT(abortProcesses()));
     connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveData()));
     connect(timer, SIGNAL(timeout()), this, SLOT(check()));
     connect(browse, SIGNAL(clicked(bool)), this, SLOT(getProgram()));
     connect(action_Hints, SIGNAL(triggered(bool)), this, SLOT(info_hint()));
     connect(showLogsButton, SIGNAL(clicked(bool)), this, SLOT(showLogs()));
     connect(historyBtn, SIGNAL(clicked(bool)), this, SLOT(showHistory()));
     connect(history->historyList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
        this, SLOT(replaceEditorContent(QListWidgetItem*)));
     connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setQuit(int)));
}

Gui::~Gui(){ delete hintMsgBox; delete logBox; delete messages; delete processes; delete processArgs; }

void Gui::handleMessageEvent(int a){
    Q_UNUSED(a);
    singleShot->stop();
    delete singleShot;
}

void Gui::setQuit(int idx) {quitCheckBox->setDisabled(idx > 0); }

void Gui::closeEvent(QCloseEvent* window_close){
     if(!pref->settings->isWritable())
       *myOutput << "W: qprogram-starter settings file is not writable!" << Qt::endl;
     else
       saveSettings();
     //qApp->quit();
     QMainWindow::closeEvent(window_close);
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
       timer->stop();
       if(processes->length() > 0) processes->first()->start(shell, QStringList() << "-c" << processArgs->first());
     }
}

void Gui::getProgram(){
     program = QFileDialog::getOpenFileName(this, tr("Select a program"), "/usr/bin");
     plainTextEdit->insertPlainText(program);
     plainTextEdit->setFocus();
}

void Gui::run(){ //To start either the timer or start the process
     aborted = false;
     if(!plainTextEdit->toPlainText().isEmpty()){
       saveHistory();
       nextDate = dateEdit->dateTime();
       timeInTheFuture = nextDate.addSecs(timeEdit->time().hour()*3600 + timeEdit->time().minute()*60 + timeEdit->time().second());
       plainTextEdit->setDisabled(true);
       atDateCheckBox->setDisabled(true);
       dateEdit->setDisabled(true);
       timeEdit->setDisabled(true);
       startB->setDisabled(true);

       #if QT_VERSION >= 0x060000
       QStringList list = plainTextEdit->toPlainText().split("\n", Qt::SkipEmptyParts);
#else
       QStringList list = plainTextEdit->toPlainText().split("\n", QString::SkipEmptyParts);
#endif
       QStringList cmd;
       QStringList pices;
       foreach( QString line, list ) {
         line = line.trimmed();
         if(line.right(1) == "\\"){
           line.chop(1);
           pices << line;
         }
         else{
           if(pices.length() > 0){
             pices << line;
             cmd << pices.join(" ");
             pices.clear();
           }
           else cmd << line;
         }
       }
         
       foreach(QString p, cmd){
          QProcess* proc = new QProcess(this);
          connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(output()));
          connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(errorOutput()));
          connect(proc, SIGNAL(error(QProcess::ProcessError)), this, SLOT(errorOutput()));
          connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(next()));
          *processes << proc;
            
          *processArgs << p;
       }

       if(atDateCheckBox->isChecked())
         timer->start(1000);
       else
         if(processes->length() > 0) processes->first()->start(shell, QStringList() << "-c" << processArgs->first());
     }
     else{
       messages->setWindowTitle("Error");
       messages->setIcon(QMessageBox::Warning);
       messages->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Window);
       messages->setInformativeText(tr("The text edit is empty!"));
       singleShot = new QTimer(this);
       singleShot->setSingleShot(true);
       connect(singleShot, SIGNAL(timeout()), messages, SLOT(hide()));
       singleShot->start(10000);
       messages->show();
     }
     outputProcess = "";
     errProcess = "";
}

void Gui::next(){
    bool force = false;
    if(processes->length() > 1 && processes->first()->exitCode()==0
        && processes->first()->exitStatus()==0
        && processes->first()->error()==QProcess::UnknownError){
        processes->first()->disconnect();
        processes->removeFirst();
        processArgs->removeFirst();
        processes->first()->start(shell, QStringList() << "-c" << processArgs->first());
    }
    else{
        message();

        if(quitCheckBox->isChecked() || comboBox->currentIndex() != 0){
            if(pref->settings->value("CheckBoxes/no_quit_action_or_shutdown_on_error", false).toBool()
                && (processes->first()->exitCode() != 0 || processes->first()->exitStatus() != 0
                || processes->first()->error() != QProcess::UnknownError)){
                
                cleanUp(force);
            }
            else{
                processes->first()->disconnect();
                countdown->setInterval(
                    1000 * pref->settings->value("countdown_before_action", 10).toInt());
                connect(countdown, SIGNAL(timeout()), this, SLOT(shutdown_or_message()));
                countdown->start();
                //timeout after 1 sec ==> minus 1 sec.
                countdownInt = pref->settings->value("countdown_before_action", 10).toInt() - 1; //seconds
                updCountdown->start(1000);
                connect(updCountdown, SIGNAL(timeout()), this, SLOT(displayCountdown()));
            }
        }
        else{
            cleanUp(force);
        }
    }
}

void Gui::cleanUp(bool force){
    foreach(QProcess *p, *processes){
        if(force)
            p->kill();
        else
            p->terminate();
        p->disconnect();
    }
    processes->clear();
    processArgs->clear();
        
    atDateCheckBox->setEnabled(true);
    if(atDateCheckBox->isChecked()){
        dateEdit->setEnabled(true);
        timeEdit->setEnabled(true);
    }
    plainTextEdit->setEnabled(true);
    startB->setEnabled(true);
}

void Gui::displayCountdown(){
    if(countdownInt >= 0) statusBar()->showMessage(QString::number(countdownInt--), 0);
}

void Gui::abortProcesses(){
     if(processes->length() == 0){
        messages->setWindowTitle(tr("Information"));
        messages->setIcon(QMessageBox::Information);
        messages->setInformativeText(tr("No running processes"));
        messages->setWindowModality(Qt::NonModal);
        messages->setWindowFlags(Qt::WindowStaysOnTopHint);
        singleShot = new QTimer(this);
        singleShot->setSingleShot(true);
        connect(singleShot, SIGNAL(timeout()), messages, SLOT(hide()));
        singleShot->start(10000);
        messages->show();
        return;
     }
     aborted = true;
     timer->stop();
     countdown->stop();
     countdown->disconnect();
     updCountdown->stop();
     updCountdown->disconnect();
     countdownInt = 0;
     
     statusBar()->clearMessage();

     messages->setWindowTitle(tr("Information"));
     messages->setIcon(QMessageBox::Information);
     messages->setInformativeText(tr("Processes aborted"));
     messages->setWindowModality(Qt::NonModal);
     messages->setWindowFlags(Qt::WindowStaysOnTopHint);
     singleShot = new QTimer(this);
     singleShot->setSingleShot(true);
     connect(singleShot, SIGNAL(timeout()), messages, SLOT(hide()));
     singleShot->start(10000);
     messages->show();
     
     bool force = true;

     cleanUp(force);
}

void Gui::output(){ //write output into a file if loggingCheckBox is checked
     QString string = QString::fromLocal8Bit(processes->first()->readAllStandardOutput());
     outputProcess += string;

     if(loggingCheckBox->isChecked()){
       QString path = QDir().toNativeSeparators(
         QStandardPaths::standardLocations(
                #if QT_VERSION >= 0x060000
            QStandardPaths::AppDataLocation).first());
#else
                       QStandardPaths::DataLocation).first());
                #endif
       if(!QDir(path).exists()) QDir().mkpath(path);
       QFile outputLog(QDir().toNativeSeparators(path + QDir::separator() + "outputLog.txt"));
       if(!outputLog.open(QIODevice::Append))
         return;
       QTextStream str(&outputLog);
       str << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
           << ": " << processArgs->first() << ":" << Qt::endl << string << Qt::endl;
       outputLog.close();
     }
}

void Gui::errorOutput(){ //write error output into a file if loggingCheckBox is checked
     QString string = QString::fromLocal8Bit(processes->first()->readAllStandardError());
     errProcess += string;
     
     if(loggingCheckBox->isChecked()){
       QString path = QDir().toNativeSeparators(
         QStandardPaths::standardLocations(
                #if QT_VERSION >= 0x060000
            QStandardPaths::AppDataLocation).first());
#else
                       QStandardPaths::DataLocation).first());
                #endif
       if(!QDir(path).exists()) QDir().mkpath(path);
       QFile errorLog(QDir().toNativeSeparators(path + QDir::separator() + "errorLog.txt"));
       if(!errorLog.open(QIODevice::Append))
         return;
       QTextStream str(&errorLog);
       str << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
           << ": " << processArgs->first() << ":" << Qt::endl
           << (string.isEmpty() ? "Unknown error. No such program?" : string)
           << Qt::endl << Qt::endl;
       errorLog.close();
     }
     
     //next();
}

void Gui::showLogs(){
     if(!outputProcess.isEmpty() || !errProcess.isEmpty()){
       logBox->setPlainText("");
       if(!outputProcess.isEmpty())
         logBox->append(outputProcess);
       if(!errProcess.isEmpty())
         logBox->append(errProcess);
       logBox->show();
     }
     else{
        messages->setWindowTitle(tr("Information"));
        messages->setIcon(QMessageBox::Information);
        messages->setInformativeText(tr("<b>No Output!</b><br/>"
           "There is still no data in the output or error stream"));
        messages->setWindowModality(Qt::NonModal);
        messages->setWindowFlags(Qt::WindowStaysOnTopHint);
        singleShot = new QTimer(this);
        singleShot->setSingleShot(true);
        connect(singleShot, SIGNAL(timeout()), messages, SLOT(hide()));
        singleShot->start(10000);
        messages->show();
     }
}     

void Gui::shutdown_or_message(){
    countdown->stop();
    countdown->disconnect();
    updCountdown->stop();
    updCountdown->disconnect();
    countdownInt = 0;
    statusBar()->clearMessage();
    
    cleanUp(false);

    if(comboBox->currentIndex() > 0)
    {
       saveSettings();

       switch(comboBox->currentIndex()){
         case 1: //shutdown
           switch(pref->shutdownCB->currentIndex()){ //shutdown method settings
              case 0:
                  Power::automatic = true;
                  break;
              case 1:
                  Power::login1 = true;
                  break;
              case 2:
                  Power::gnome = true;
                  break;
              case 3:
                  Power::kde = true;
                  break;
              case 4:
                  Power::hal_ = true;
                  break;
              case 5:
                  Power::consolekit = true;
                  break;
              case 6:
                  Power::sudo = true;
                  break;
              //case 7:
              //    Power::user = true;
              //    Power::myShutdown = pref->myShutdown;
              //    break;
              default:;
           }
           Power::shutdown();
           break;

         case 2: //reboot
           switch(pref->rebootCB->currentIndex()){ //reboot method settings
              case 0:
                  Power::automatic = true;
                  break;
              case 1:
                  Power::login1 = true;
                  break;
              case 2:
                  Power::gnome = true;
                  break;
              case 3:
                  Power::kde = true;
                  break;
              case 4:
                  Power::hal_ = true;
                  break;
              case 5:
                  Power::consolekit = true;
                  break;
              case 6:
                  Power::sudo = true;
                  break;
              //case 7:
              //    Power::user = true;
              //    Power::myReboot = pref->myReboot;
              //    break;
              default:;
           }
           Power::reboot();
           break;
         
         case 3: //sleep
           switch(pref->suspendCB->currentIndex()){ //sleep method settings
              case 0:
                  Power::automatic = true;
                  break;
              case 1:
                  Power::login1 = true;
                  break;
              case 2:
                  Power::gnome = true;
                  break;
              case 3:
                  Power::hal_ = true;
                  break;
              case 4:
                  Power::upower_ = true;
                  break;
              case 5:
                  Power::devicekit = true;
                  break;
              //case 6:
              //    Power::user = true;
              //    Power::mySuspend = pref->mySuspend;
              //    break;
              default:;
           }
           Power::lockMyScreen = true;
           Power::suspend();
           break;
         
         case 4: //hibernate
           switch(pref->hibernateCB->currentIndex()){ //hibernate method settings
              case 0:
                  Power::automatic = true;
                  break;
              case 1:
                  Power::login1 = true;
                  break;
              case 2:
                  Power::gnome = true;
                  break;
              case 3:
                  Power::hal_ = true;
                  break;
              case 4:
                  Power::upower_ = true;
                  break;
              case 5:
                  Power::devicekit = true;
                  break;
              //case 6:
              //    Power::user = true;
              //    Power::myHibernate = pref->myHibernate;
              //    break;
              default:;
           }
           Power::lockMyScreen = true;
           Power::hibernate();
           break;
         
         default:;
       }
    }
    if(quitCheckBox->isChecked() || comboBox->currentIndex() > 0){
        qApp->quit();
    }
}

void Gui::message(){
     const QProcess *p = processes->first();
     if(!aborted){
       if(p->exitCode()==0 && p->exitStatus()==0 && p->error()==QProcess::UnknownError){
           messages->setWindowTitle(tr("Information"));
           messages->setIcon(QMessageBox::Information);
           messages->setInformativeText(tr("<b>process finished!</b>"));
       }

       if(p->exitCode()!=0 || p->error()!=QProcess::UnknownError){
         messages->setWindowTitle(tr("Error"));
         messages->setIcon(QMessageBox::Critical);
         if(p->error()==0){
           messages->setInformativeText(tr("<b>Failed to start!</b><br/>"
            "No such program or command."));
           /*if(loggingCheckBox->isChecked()){
             QString path = QDir().toNativeSeparators(
               QStandardPaths::standardLocations(
                  QStandardPaths::DataLocation).first());
             if(!QDir(path).exists()) QDir().mkpath(path);
             QFile errorLog(QDir().toNativeSeparators(path + QDir::separator() + "errorLog.txt"));
             if(!errorLog.open(QIODevice::Append))
               return;
             QTextStream err(&errorLog);
             err << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
                 << ": " << processArgs->first() << ":" << endl
                 << tr("\"%1\": Failed to start! No such program or "
                        "command.\n").arg(plainTextEdit->toPlainText())
                 << endl;
             errorLog.close();
           }*/
         }
         else if(p->error()==1 || p->exitCode()==1)
           messages->setInformativeText(tr("<b>process crashed!</b><br/>"
           "This could be caused by invalid parameters or options."));
         else
           messages->setInformativeText(tr("<b>Unknown error!</b><br/>"
           "This could be caused by invalid parameters or options."));
       }
       messages->setWindowModality(Qt::NonModal);
       messages->setWindowFlags(Qt::WindowStaysOnTopHint);
       singleShot = new QTimer(this);
       singleShot->setSingleShot(true);
       connect(singleShot, SIGNAL(timeout()), messages, SLOT(hide()));
       singleShot->start(10000);
       messages->show();
     }
}

void Gui::showHistory(){
    QJsonDocument json = QJsonDocument::fromJson(pref->settings->value("History/text", QString()).toByteArray());
    QJsonArray jsonArr = json.array();
    
    history->historyList->clear();
    
    for(int i = 0; i < jsonArr.size(); i++){
        history->historyList->addItem(jsonArr[i].toString().replace(QString("\n"), QString("\\n")));
    }
    history->show();   

}

void Gui::replaceEditorContent(QListWidgetItem *item){
    plainTextEdit->setPlainText(item->text().replace(QString("\\n"), QString("\n")));
}

void Gui::saveHistory(){
    QJsonDocument json = QJsonDocument::fromJson(pref->settings->value("History/text", QString()).toByteArray());
    QJsonArray jsonArr = json.array();
    jsonArr.prepend(plainTextEdit->toPlainText());
    
    int max = pref->settings->value("History/max", 10).toInt();
    
    while(jsonArr.size() >= max) jsonArr.removeLast();
    
    pref->settings->setValue("History/text", QJsonDocument(jsonArr).toJson(QJsonDocument::Compact));
}

void Gui::saveData(){
    pref->settings->setValue("Text/text", plainTextEdit->toPlainText());

    messages->setWindowTitle(tr("Information"));
    messages->setIcon(QMessageBox::Information);
    messages->setInformativeText(tr("Content saved for future startups."));
    messages->setWindowModality(Qt::NonModal);
    messages->setWindowFlags(Qt::WindowStaysOnTopHint);
    singleShot = new QTimer(this);
    singleShot->setSingleShot(true);
    connect(singleShot, SIGNAL(timeout()), messages, SLOT(hide()));
    singleShot->start(10000);
    messages->show();
}

void Gui::saveSettings(){
     pref->settings->setValue("CheckBoxes/atDate", atDateCheckBox->isChecked());
     pref->settings->setValue("CheckBoxes/logging", loggingCheckBox->isChecked());
     pref->settings->setValue("CheckBoxes/shutdown", comboBox->currentIndex());
     pref->settings->setValue("CheckBoxes/quitWithLastProcess", quitCheckBox->isChecked());
}

void Gui::loadSettings(){
     atDateCheckBox->setChecked(pref->settings->value("CheckBoxes/atDate").toBool());
     loggingCheckBox->setChecked(pref->settings->value("CheckBoxes/logging").toBool());
     comboBox->setCurrentIndex(pref->settings->value("CheckBoxes/shutdown").toInt());
     quitCheckBox->setChecked(pref->settings->value("CheckBoxes/quitWithLastProcess").toBool());
     plainTextEdit->setPlainText(pref->settings->value("Text/text").toString());
}
