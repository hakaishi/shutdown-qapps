/* qprogram-starter, a program to start programs or commands, with
   the option to log output and errors and to shutdown the system.
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

#include "gui.h"
#include "preferences.h"
#include "power.h"
#include <QMessageBox>
#include <QSettings>
#include <QFile>

#ifndef Q_OS_WIN32
  #include <QtDBus>
#endif

Gui::Gui(){

     setupUi(this);

     pref = new Preferences(this);

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

     aborted = false;

     dateEdit->setMinimumDate(QDate::currentDate());
     dateTimeTimer = new QTimer(this);
     dateTimeTimer->start(1000);

     timer = new QTimer(this);

     logBox = new QTextEdit;
     logBox->setReadOnly(true);
     logBox->resize(520,450);
     logBox->setWindowTitle("error log 1");
     logBox->setWindowModality(Qt::NonModal);

     hintMsgBox = new QTextEdit;
     hintMsgBox->setReadOnly(true);
     hintMsgBox->resize(520,450);
     hintMsgBox->setWindowTitle("Info");
     hintMsgBox->setWindowModality(Qt::NonModal);
     hintMsgBox->setHtml(tr("The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.<br/>To start a program just type i.e. \"firefox\" or \"firefox www.google.com\" and then click on Start. Commands etc. can be linked by \"&&\" etc. <br/><br/>If the process is \"finished\" although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.<br/><br/>When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).<br/><br/>make examples:<br/>&nbsp;make -C /path/to/project<br/>&nbsp;make clean -C /path/to/project<br/><br/>About Errors:<br/>Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at <i>~/.qprogram-starter/</i>.<br/><br/>If the shutdown won't work, it means that \"sudo shutdown -P now\" is used. This needs root permissions. You can do the this:<br/><br/>Post the following in a terminal:<pre>EDITOR=nano sudo -E visudo</pre> and add this line:<pre>* ALL = NOPASSWD:/sbin/shutdown</pre> whereas * replaces the username or %groupname.<br/><br/>The configuration-file can be found at <i>~/.qprogram-starter/</i>."));
     
     historyList = new QListWidget;

     connect(action_Configure, SIGNAL(triggered(bool)), pref, SLOT(show()));
     connect(dateTimeTimer, SIGNAL(timeout()), this, SLOT(currentDateAndTime()));
     connect(startB, SIGNAL(clicked(bool)), this, SLOT(run()));
     connect(abortB, SIGNAL(clicked(bool)), this, SLOT(abortProcesses()));
     connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveData()));
     connect(timer, SIGNAL(timeout()), this, SLOT(check()));
     connect(browse, SIGNAL(clicked(bool)), this, SLOT(getProgram()));
     connect(this, SIGNAL(finished()), this, SLOT(shutdown_or_message()));
     connect(action_Hints, SIGNAL(triggered(bool)), this, SLOT(info_hint()));
     connect(showLogsButton, SIGNAL(clicked(bool)), this, SLOT(showLogs()));
     connect(historyBtn, SIGNAL(clicked(bool)), this, SLOT(showHistory()));
     connect(historyList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
        this, SLOT(replaceEditorContent(QListWidgetItem*)));
     connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setQuit(int)));
}

Gui::~Gui(){ delete hintMsgBox; delete historyList; delete logBox;}

void Gui::setQuit(int idx) {quitCheckBox->setDisabled(idx > 0); }

void Gui::closeEvent(QCloseEvent* window_close){
     if(!pref->settings->isWritable())
       *myOutput << "W: qprogram-starter.conf is not writable!" << endl;
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
       if(processes->length() > 0) processes->first()->start(processArgs->first());
     }
}

void Gui::getProgram(){
     program = QFileDialog::getOpenFileName(this, tr("Select a program"), "/usr/bin");
     plainTextEdit->insertPlainText(program);
     plainTextEdit->setFocus();
}

void Gui::run(){ //To start either the timer or start the process
     if(!plainTextEdit->toPlainText().isEmpty()){
       nextDate = dateEdit->dateTime();
       timeInTheFuture = nextDate.addSecs(timeEdit->time().hour()*3600 + timeEdit->time().minute()*60 + timeEdit->time().second());
       plainTextEdit->setDisabled(true);
       atDateCheckBox->setDisabled(true);
       dateEdit->setDisabled(true);
       timeEdit->setDisabled(true);

       QStringList list = plainTextEdit->toPlainText().split("\n", QString::SkipEmptyParts);
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
            
       processes = new QList<QProcess* >;
       processArgs = new QStringList;
         
       foreach(QString p, cmd){
          QProcess* proc = new QProcess(this);
          connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(output()));
          connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(errorOutput()));
          connect(proc, SIGNAL(error(QProcess::ProcessError)), this, SLOT(message()));
          connect(proc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(next()));
          *processes << proc;
            
          *processArgs << p;
       }

       if(atDateCheckBox->isChecked())
         timer->start(1000);
       else
         if(processes->length() > 0) processes->first()->start(processArgs->first());
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
     outputProcess = "";
     errProcess = "";
}

void Gui::next(){
    //bool isLast = processes->length() == 1;
    if(processes->length() > 1 && processes->first()->exitCode()==0 && processes->first()->exitStatus()==0){
        processes->removeFirst();
        processArgs->removeFirst();
        processes->first()->start(processArgs->first());
    }
    else shutdown_or_message();
    
}

void Gui::abortProcesses(){
     timer->stop();
     aborted = true;
     
     foreach(QProcess *p, *processes) p->close();

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
     plainTextEdit->setEnabled(true);

     aborted = false;
}

void Gui::output(){ //write output into a file if loggingCheckBox is checked
     QString string = QString::fromLocal8Bit(processes->first()->readAllStandardOutput());
     outputProcess += string;

     if(loggingCheckBox->isChecked()){
       QFile outputLog(QDir::homePath() + "/.qprogram-starter/outputLog.txt");
       if(!outputLog.open(QIODevice::Append))
         return;
       QTextStream str(&outputLog);
       str << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
           << ": " << processArgs->first() << ":" << endl << string << endl;
       outputLog.close();
     }
}

void Gui::errorOutput(){ //write error output into a file if loggingCheckBox is checked
     QString string = QString::fromLocal8Bit(processes->first()->readAllStandardError());
     errProcess += string;

     if(loggingCheckBox->isChecked()){
       QFile errorLog(QDir::homePath() + "/.qprogram-starter/errorLog.txt");
       if(!errorLog.open(QIODevice::Append))
         return;
       QTextStream str(&errorLog);
       str << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
           << ": " << processArgs->first() << ":" << endl << string << endl;
       errorLog.close();
     }
}

void Gui::showLogs(){
     if(!outputProcess.isEmpty() || !errProcess.isEmpty()){
       if(!outputProcess.isEmpty())
         logBox->append(outputProcess);
       if(!errProcess.isEmpty())
         logBox->append(errProcess);
       logBox->show();
     }
}     

void Gui::shutdown_or_message(){
     saveHistory();
     
     if(comboBox->currentIndex() == 0 || aborted)
     {
        message();
        return;
     }
     else
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

     processes->clear();
     processArgs->clear();
     qApp->quit(); //otherwise some systems might prompt to quit the program
}

void Gui::message(){
     const QProcess *p = processes->first();
     if(!aborted){
       QMessageBox msgBox;
       if(p->exitCode()==0 && p->exitStatus()==0 && p->error()==QProcess::UnknownError){
           msgBox.setWindowTitle(tr("Information"));
           msgBox.setIcon(QMessageBox::Information);
           msgBox.setInformativeText(tr("<b>process finished!</b>"));
       }

       if(p->exitCode()!=0 || p->error()!=QProcess::UnknownError){
         msgBox.setWindowTitle(tr("Error"));
         msgBox.setIcon(QMessageBox::Critical);
         if(p->error()==0){
           msgBox.setInformativeText(tr("<b>Failed to start!</b><br/>"
            "No such program or command."));
           if(loggingCheckBox->isChecked()){
             if(p->error()==0){
               QFile errorLog(QDir::homePath() + "/.qprogram-starter/errorLog.txt");
               if(!errorLog.open(QIODevice::Append))
                 return;
               QTextStream err(&errorLog);
               err << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")
                   << ": " << processArgs->first() << ":" << endl
                   << tr("\"%1\": Failed to start! No such program or "
                          "command.\n").arg(plainTextEdit->toPlainText())
                   << endl;
               errorLog.close();
             }
           }
         }
         else if(p->error()==1 || p->exitCode()==1)
           msgBox.setInformativeText(tr("<b>process crashed!</b><br/>"
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
     plainTextEdit->setEnabled(true);

     if(quitCheckBox->isChecked() && !aborted)
       close();

     processes->clear();
     processArgs->clear();
}

void Gui::showHistory(){
    QJsonDocument json = QJsonDocument::fromJson(pref->settings->value("History/text", QString()).toByteArray());
    QJsonArray jsonArr = json.array();
    
    historyList->clear();
    
    for(int i = 0; i < jsonArr.size(); i++){
        historyList->addItem(jsonArr[i].toString().replace(QString("\n"), QString("\\n")));
    }
    historyList->show();   

}

void Gui::replaceEditorContent(QListWidgetItem *item){
    plainTextEdit->setPlainText(item->text().replace(QString("\\n"), QString("\n")));
}

void Gui::saveHistory(){
    QJsonDocument json = QJsonDocument::fromJson(pref->settings->value("History/text", QString()).toByteArray());
    QJsonArray jsonArr = json.array();
    jsonArr << plainTextEdit->toPlainText();
    
    int max = pref->settings->value("History/max", 10).toInt();
    
    while(jsonArr.size() >= max) jsonArr.removeFirst();
    
    pref->settings->setValue("History/text", QJsonDocument(jsonArr).toJson(QJsonDocument::Compact));
}

void Gui::saveData(){
     pref->settings->setValue("Text/text", plainTextEdit->toPlainText());
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
