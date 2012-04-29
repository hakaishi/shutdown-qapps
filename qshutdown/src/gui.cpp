/* qshutdown, a program to shutdown the shutdown/reboot/suspend/hibernate
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
#include "preferences.h"
#include "info.h"
#include "calendar.h"
#include "passwd.h"
#include "editor.h"
#include "about.h"
#include "power.h"
#include <QTextStream>
#include <QTimer>

Gui::Gui(){

     setupUi(this);

   //Seconds won't be recognized, thus removing them (just in case).
     QString timeEditFormat;
     timeEditFormat = timeEdit->displayFormat();
     if(timeEditFormat.contains(":ss"))
       timeEditFormat.replace(QString(":ss"), QString(""));
     if(timeEditFormat.contains(":s"))
       timeEditFormat.replace(QString(":s"), QString(""));
     timeEdit->setDisplayFormat(timeEditFormat);

     timeRunning = false;
     logFileSize = 1.5;

     datetime = QDateTime::currentDateTime();
     elapsedTime.start();

   //Preferences
     pref = new Preferences(this);

   //CalendarBox
     cal = new Calendar(this);

   //InfoMessageBox
     infoBox = new Info(this);

   //ChangePassword
     checkPassword = new PassWord(this);

   //Editor
     editor = new Editor(this);

   //Versioning
     QFile versionFile(":version");
     versionFile.open(QIODevice::ReadOnly | QIODevice::Text);
     QTextStream in(&versionFile);
     statusBar()->showMessage(tr("Version ") + in.readLine(),15000);
     versionFile.close();

/* //Parental lock label for the statusbar
     parentalLockL = new QLabel(tr("locked"));
     parentalLockL->setFrameShape(QFrame::Box);
     parentalLockL->setFrameShadow(QFrame::Sunken);
     parentalLockL->setToolTip(tr("Parental lock is activated"));

   //Custom mode label for the statusbar
     customL = new QLabel(tr("custom"));
     customL->setFrameShape(QFrame::Box);
     customL->setFrameShadow(QFrame::Sunken);
     customL->setToolTip(tr("Using user defined command"));*/

   //About
     about = new About(this);

   //TrayIcon
     icon = QIcon(":red_glasses");
     TIcon = new QSystemTrayIcon(this);
     TIcon->setIcon(icon);
     TIcon->show();

   //TrayIconContextMenu
     menu = new QMenu(this);
     minimize_restore_action = new QAction(tr("&Minimize"),this);
     reset_action = new QAction(tr("R&eset"),this);
     quit_action = new QAction(tr("&Quit"),this);
     info_action = new QAction(tr("&Info"),this);
     log_action = new QAction(tr("&Logfile"),this);
     log_action->setCheckable(true);
     pref_action = new QAction(tr("&Preferences"),this);

     power_actions = new QActionGroup(this);
     shutdown_action = new QAction(tr("&Shutdown"),this);
     shutdown_action->setCheckable(true);
     reboot_action = new QAction(tr("&Reboot"),this);
     reboot_action->setCheckable(true);
     suspend_action = new QAction(tr("S&uspend"),this);
     suspend_action->setCheckable(true);
     hibernate_action = new QAction(tr("&Hibernate"),this);
     hibernate_action->setCheckable(true);
     power_actions->addAction(shutdown_action);
     power_actions->addAction(reboot_action);
     power_actions->addAction(suspend_action);
     power_actions->addAction(hibernate_action);

     menu->addAction(info_action);
     menu->addAction(reset_action);
     menu->addAction(pref_action);
     menu->addAction(log_action);
     menu->addSeparator();
     menu->addAction(shutdown_action);
     menu->addAction(reboot_action);
     menu->addAction(suspend_action);
     menu->addAction(hibernate_action);
     reset_action->setEnabled(false);
     menu->addSeparator();
     menu->addAction(minimize_restore_action);
     menu->addAction(quit_action);
     
     TIcon->setContextMenu(menu);  //setting contextmenu for the systray

   //PushButton Minimize
     minim = new QPushButton(this); //to minimize
     minim->setText(tr("&Minimize!"));
     minim->setHidden(true); //not yet visible
     QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Preferred);
     sizePolicy6.setHorizontalStretch(0);
     sizePolicy6.setVerticalStretch(1);
     sizePolicy6.setHeightForWidth(ok->sizePolicy().hasHeightForWidth());
     minim->setSizePolicy(sizePolicy6);
     gridLayout5->addWidget(minim,0,1,3,1);

   //Fonts
     font1 = new QFont;
     font1->setBold(true);

     font2 = new QFont;
     font2->setBold(true);

     font3 = new QFont;

   //Timer
     timer = new QTimer(this); //for updating countdown display and check if time is over
     ti = new QTimer(this); //for displaying the window, till the OK-Button is clicked
     ti->start(30000); //gives every 30 seconds a timeout()-signal

   //Connect signals with slots (actions with funktions)
     connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(power_action(int)));
     connect(ti, SIGNAL(timeout()), this, SLOT(showW())); //set window state for ti
     connect(ok, SIGNAL(clicked(bool)), this, SLOT(set())); //starts timers and time calculations
     connect(timer, SIGNAL(timeout()), this, SLOT(updateT()));    //runs updateT() every second
     connect(now, SIGNAL(clicked(bool)), this, SLOT(finished_()));//closes the program & starts the shutdown immediately
     connect(minim, SIGNAL(clicked(bool)), this, SLOT(showMinimized())); //minimizes window
     connect(TIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
       this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason))); //handles systray-symbol
     connect(power_actions, SIGNAL(triggered(QAction*)), this, SLOT(power(QAction*)));
     connect(reset_action, SIGNAL(triggered()), this, SLOT(reset()));
     connect(action_Reset, SIGNAL(triggered()), this, SLOT(reset()));
     connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(beforeQuit())); //save window size / logs and unregister qshutdown
     connect(minimize_restore_action, SIGNAL(triggered()), this, SLOT(tray_actions()));
     connect(quit_action, SIGNAL(triggered()), qApp, SLOT(quit())); //contextmenu "Quit" for the systray quits Programm
     connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

     connect(action_Configure, SIGNAL(triggered()), pref, SLOT(show()));
     connect(pref_action, SIGNAL(triggered()), pref, SLOT(show()));
     connect(pref, SIGNAL(starting()), ti, SLOT(stop()));
     connect(pref, SIGNAL(finishing()), this, SLOT(warnings_on())); //start the Qtimer ti if timeRunning == false
     connect(pref, SIGNAL(changeFont()), this, SLOT(getFonts()));
     connect(pref, SIGNAL(editConf()), checkPassword, SLOT(show()));  //ask for password when button was pressed at preferences

     connect(action_Info, SIGNAL(triggered()), this, SLOT(setInfoText()));
     connect(action_Info, SIGNAL(triggered()), infoBox, SLOT(show()));
     connect(info_action, SIGNAL(triggered()), this, SLOT(setInfoText()));
     connect(info_action, SIGNAL(triggered()), infoBox, SLOT(show()));
     connect(infoBox, SIGNAL(starting()), ti, SLOT(stop()));
     connect(infoBox, SIGNAL(finishing()), this, SLOT(warnings_on()));

     connect(toolButton, SIGNAL(clicked(bool)), this, SLOT(showCalendarBox()));
     connect(cal, SIGNAL(aDateWasSet()), this, SLOT(setDate()));
     connect(cal, SIGNAL(starting()), ti, SLOT(stop()));
     connect(cal, SIGNAL(finishing()), this, SLOT(warnings_on()));

     connect(checkPassword, SIGNAL(success()), pref, SLOT(saveToConfFile()));
     connect(checkPassword, SIGNAL(success()), this, SLOT(showEditor())); //if correct password was entered open editor
     connect(checkPassword, SIGNAL(starting()), ti, SLOT(stop()));
     connect(checkPassword, SIGNAL(finishing()), this, SLOT(warnings_on()));

     connect(editor, SIGNAL(saved()), this, SLOT(updateLock()));      //update to see if Lock_all was (de)activated
     connect(editor, SIGNAL(saved()), pref, SLOT(loadSettings()));
     connect(editor, SIGNAL(starting()), ti, SLOT(stop()));
     connect(editor, SIGNAL(finishing()), this, SLOT(warnings_on()));
     connect(editor, SIGNAL(finishing()), pref, SLOT(loadSettings()));

     connect(actionLog_file, SIGNAL(toggled(bool)), log_action, SLOT(setChecked(bool)));
     connect(log_action, SIGNAL(toggled(bool)), actionLog_file, SLOT(setChecked(bool)));

     connect(action_About, SIGNAL(triggered()), about, SLOT(show()));
     connect(actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

     connect(actionKeep_window_proportions, SIGNAL(toggled(bool)), this, SLOT(staticProportions(bool)));
}

Gui::~Gui(){
     delete font1;
     delete font2;
     delete font3;
//     delete parentalLockL;
//     delete customL;
}

void Gui::showEvent(QShowEvent* show_window){
     minimize_restore_action->setText(tr("&Minimize"));
     QWidget::showEvent(show_window);
}

void Gui::tray_actions(){
     if(isMinimized() || isHidden())  //in case that the window is minimized or hidden
       showNormal();
     else
       hide();
}

void Gui::setInfoText(){ infoBox->setHtml(information); }

void Gui::warnings_on(){
     if(pref->getClosed() && cal->getClosed() && infoBox->getClosed() && checkPassword->getClosed()
        && editor->getClosed() && !timeRunning)
       ti->start();
}

void Gui::setDate(){ toolButton->setText(cal->setCalendarDate.toString(Qt::SystemLocaleShortDate)); }

void Gui::center(){
     QDesktopWidget *desktop = qApp->desktop();
     QPoint pos((desktop->width() - frameGeometry().width()) / 2,
                (desktop->height() - frameGeometry().height()) / 2);
     move(pos);
}

void Gui::iconActivated(QSystemTrayIcon::ActivationReason reason){
     if(reason == QSystemTrayIcon::Trigger){
       tray_actions(); //hide or show
     }
}

void Gui::power_action(int action){
     QList<QAction*> actions = power_actions->actions();
     actions[action]->setChecked(true);
     switch(action){
       case 0:
         targetTime->setText(tr("Shutdown-time:"));
         minutes->setText(tr("Minutes till shutdown:"));
         break;
       case 1:
         targetTime->setText(tr("Reboot-time:"));
         minutes->setText(tr("Minutes till reboot:"));
         break;
       case 2:
         targetTime->setText(tr("Suspend-time:"));
         minutes->setText(tr("Minutes till suspend:"));
         break;
       case 3:
         targetTime->setText(tr("Hibernate-time:"));
         minutes->setText(tr("Minutes till hibernate:"));
         break;
       default:;
     }
}

void Gui::power(QAction *action){
     if(action == shutdown_action)
       comboBox->setCurrentIndex(0);
     if(action == reboot_action)
       comboBox->setCurrentIndex(1);
     if(action == suspend_action)
       comboBox->setCurrentIndex(2);
     if(action == hibernate_action)
       comboBox->setCurrentIndex(3);
}

void Gui::showW(){
     if(warnings->isChecked()){ //warnings is checked
       if(timeRunning){
         QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(3);
         TIcon->showMessage(tr("Warning"), tr("Action imminent!"), icon, 5000);
         showRunningProgram();
       }
       else{
         QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(1);
         TIcon->showMessage(tr("Information"), tr("Countdown is not running!"), icon, 5000);
       }
     }
}

void Gui::showRunningProgram(){
     center();
     if(isMinimized() || isHidden())
       showNormal();
     else
       activateWindow();
}

void Gui::keyPressEvent(QKeyEvent *kEvent){
     if(kEvent->modifiers() == Qt::ControlModifier){
       if(!timeRunning && !editor->getLockAll()){
         if(kEvent->key() == Qt::Key_S){
           shutdown_action->setChecked(true);
           comboBox->setCurrentIndex(0);
         }
         if(kEvent->key() == Qt::Key_R){
           reboot_action->setChecked(true);
           comboBox->setCurrentIndex(1);
         }
         if(kEvent->key() == Qt::Key_U){
           suspend_action->setChecked(true);
           comboBox->setCurrentIndex(2);
         }
         if(kEvent->key() == Qt::Key_H){
           hibernate_action->setChecked(true);
           comboBox->setCurrentIndex(3);
         }
       }
       if(!editor->getLockAll()){
         if(kEvent->key() == Qt::Key_E && timeRunning)
           reset();
         if(kEvent->key() == Qt::Key_L){
           if(log_action->isChecked()){
             log_action->setChecked(false);
             actionLog_file->setChecked(false);
           }
           else{
             log_action->setChecked(true);
             actionLog_file->setChecked(true);
           }
         }
         if(kEvent->key() == Qt::Key_Q)
           qApp->quit();
       }
       if(kEvent->key() == Qt::Key_I){
         setInfoText();
         infoBox->show();
       }
       if(kEvent->key() == Qt::Key_P)
         pref->show();
     }
     if(kEvent->modifiers() == Qt::ShiftModifier){
       if(kEvent->key() == Qt::Key_E)
         checkPassword->show(); //ask for password to edit qshutdown.conf
     }
}

void Gui::updateT(){
     QDate myDate;
     QString tip1, tip2;

     if(shutdown_action->isChecked())
       tip1 = (tr("shutdown in "));
     if(reboot_action->isChecked())
       tip1 = (tr("reboot in "));
     if(suspend_action->isChecked())
       tip1 = (tr("suspend in "));
     if(hibernate_action->isChecked())
       tip1 = (tr("hibernate in "));

     if(QDate::currentDate().daysTo(cal->setCalendarDate) > 1){ //if the date difference between today and the selected day
                                                           //in the calendar is greater than one
     //if more than one year
       if(QDate::currentDate().daysTo(cal->setCalendarDate) > myDate.daysInYear()){
         tip2 = (QString::number(QDate::currentDate().daysTo(cal->setCalendarDate)/myDate.daysInYear()) + " " + tr("years"));
         lcdL->setText(tr("years"));
         lcd->setNumDigits(4);
         lcd->display((double)QDate::currentDate().daysTo(cal->setCalendarDate)/myDate.daysInYear());
       }
     //if more than one month
       if(QDate::currentDate().daysTo(cal->setCalendarDate) > myDate.daysInMonth()
           && QDate::currentDate().daysTo(cal->setCalendarDate) <= myDate.daysInYear()){
         tip2 = (QString::number(QDate::currentDate().daysTo(cal->setCalendarDate)/myDate.daysInMonth()) + " " + tr("months"));
         lcdL->setText(tr("months"));
         if((double)QDate::currentDate().daysTo(cal->setCalendarDate)/myDate.daysInMonth() >= 10)
           lcd->setNumDigits(4);
         else
           lcd->setNumDigits(3);
         lcd->display((double)QDate::currentDate().daysTo(cal->setCalendarDate)/myDate.daysInMonth());
       }
     //if less than days in Month
       if(QDate::currentDate().daysTo(cal->setCalendarDate) <= myDate.daysInMonth()){
         tip2 = (QString::number(QDate::currentDate().daysTo(cal->setCalendarDate)) + " " + tr("days"));
         lcdL->setText(tr("days"));
         if((double)QDate::currentDate().daysTo(cal->setCalendarDate) >= 10)
           lcd->setNumDigits(4);
         else
           lcd->setNumDigits(3);
         lcd->display((double)QDate::currentDate().daysTo(cal->setCalendarDate));
       }
     }
     if(QDate::currentDate().daysTo(cal->setCalendarDate) == 1){ //if there is one more day to go

       Time();

       if(i>=86400){ //if one day and some time to go
         tip2 = (">= 1 " + tr("day"));
         lcd->setNumDigits(3);
         lcd->display(bigI/86400);
         if(lcd->value() > 1.1)
           lcdL->setText(tr("days"));
         else
           lcdL->setText(tr("day"));
       }
       if(i<86400 && i>3600){ //if there is less than one day, show hours
         tip2 = (QString::number(i/3600) + " " + tr("hours"));
         lcdL->setText(tr("hours"));
         if(bigI/3600 >= 10)
           lcd->setNumDigits(4);
         else
           lcd->setNumDigits(3);
         lcd->display(bigI/3600);
       }
       if(i<=3600 && i>60){ //if less than one hour
         tip2 = (QString::number(i/60) + " " + tr("minutes"));
         lcdL->setText(tr("minutes"));
         if(bigI/60 >= 10){
           lcd->setNumDigits(4);
           lcd->display(bigI/60);
         }
         else
           lcd->setNumDigits(3);
         lcd->display(bigI/60);
       }
       if(i<=60){
         tip2 = (QString::number(i) + " " + tr("seconds"));
         lcdL->setText(tr("seconds"));
         lcd->display(i);
       }
     }
     if(QDate::currentDate()==cal->setCalendarDate || cal->setCalendarDate.isNull()){ //if there was no date
                                             //set in the calendar or the set day is the current day
       Time();

       if(warnings->isChecked() && (((i<=100) && (i>95)) || ((i<=40) && (i>35))) && !ti->isActive())
         ti->start(30000);

       if(i > 3600){ //Display hours and minutes
         tip2 = (QString::number(i/3600) + " " + tr("hours") + " + "
                + QString::number(i/60 - (i/3600)*60) + " " + tr("minutes"));
         lcdL->setText(tr("hours"));
         if(bigI/3600 >= 10)
           lcd->setNumDigits(4);
         else
           lcd->setNumDigits(3);
         lcd->display(bigI/3600);
       }
       if(i<=3600 && i>=60){ //Display only minutes
         tip2 = (QString::number(i/60) + " " + tr("minutes"));
         lcdL->setText(tr("minutes"));
         if(bigI/60 >= 10)
           lcd->setNumDigits(4);
         else
           lcd->setNumDigits(3);
         lcd->display(bigI/60);
       }
       if(i<=60){ //Display only seconds
         tip2 = (QString::number(i) + " " + tr("seconds"));
         lcdL->setText(tr("seconds"));
         lcd->display(i);
       }

     //this will ensure that the shutdown-type will be executed in case a few seconds were skipped
       if(i<=86390)
         n = 10; //any number to keep i in check
       if((i==0) || ((i>n) && (i>86390)))
         finished_(); //execute shutdown-type
     }
     setWindowTitle(tip1 + tip2);
     TIcon->setToolTip(tip1 + tip2);
}

void Gui::set(){
     timeRunning = true;

     ti->stop();
     timer->start(1000);

     localTime = QTime::currentTime(); //the time now
     if(radio2->isChecked()) //if minute-countdown
       futureTime = localTime.addSecs(spin->value()*60); //add spinbox-value to the current time
     else
       futureTime = timeEdit->time(); //else the future time is the time of the timeEdit
     n = 86400; // any number bigger than i - just for initializing

     if(lock->isChecked() || editor->getLockAll()){       //when OK-button is clicked and lock is checked
       QList<QWidget*> list;
       list << spin << radio1 << radio2 << lock << timeEdit << comboBox << targetTime
            << minutes << pref->tab2;
       foreach(QWidget * ptr, list)
         ptr->setDisabled(true);
       power_actions->setDisabled(true);
       ok->hide();
       minim->show();
       minim->setFocus();
       minim->setAutoDefault(true);         //minimize-button will accept the return key
     }
     if(!editor->getLockAll()){
       reset_action->setEnabled(true);
       action_Reset->setEnabled(true);
     }

/*   if((comboBox->currentIndex() == 0 && pref->shutdownM->currentIndex() == 6)
        || (comboBox->currentIndex() == 1 && pref->rebootM->currentIndex() == 6)
        || (comboBox->currentIndex() == 2 && pref->suspendM->currentIndex() == 5)
        || (comboBox->currentIndex() == 3 && pref->hibernateM->currentIndex() == 5)){
       if(!customL->isVisible())
         customL->show();
       statusBar()->addPermanentWidget(customL);
     }
     else
       statusBar()->removeWidget(customL);*/
}

void Gui::Time(){
     localTime = QTime::currentTime();
     i = localTime.secsTo(futureTime); //the difference of the localTime and the future time
     if(radio2->isChecked() && (QDate::currentDate().daysTo(cal->setCalendarDate) == 1))
       i = ((23-localTime.hour())*3600 + (59-localTime.minute())*60 + spin->value()*60);
     if(radio1->isChecked() && (QDate::currentDate().daysTo(cal->setCalendarDate) == 1))
       i = ((23-localTime.hour())*3600 + (59-localTime.minute())*60 + timeEdit->time().hour()*3600
           + timeEdit->time().minute()*60);
     if(i<0)                           //if the date is on the next day
       i += 86400; //add 1 day in seconds
     bigI = i; //for more precise display with LCD
}

void Gui::saveLog(){
   #ifdef Q_OS_WIN32
     QString file(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/qshutdown/qshutdown.conf");
   #else //!Q_OS_WIN32
     QString file(QDir::homePath() + "/.qshutdown/qshutdown.conf");
   #endif //Q_OS_WIN32
     QSettings settings(file, QSettings::IniFormat);

     settings.setValue("MainWindow/size",size());
     settings.setValue("MainWindow/keep_proportions",actionKeep_window_proportions->isChecked());

     if(log_action->isChecked()){ //if logfile is set in the icon contextmenu
     #ifdef Q_OS_WIN32
       QFile logfile(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/qshutdown/log.txt");
     #else //!Q_OS_WIN32
       QFile logfile(QDir::homePath() + "/.qshutdown/log.txt");
     #endif //Q_OS_WIN32
       if(!logfile.open(QIODevice::ReadWrite | QIODevice::Text)){
         QTextStream myOutput;
         myOutput << "E: Can not open log.txt!" << endl;
         return;
       }

/******* writing log to log.txt *******/
       QTextStream out(&logfile);
       while(!logfile.atEnd())
         out.readLine();
       out << "[" << datetime.toString("yyyy.MM.dd hh:mm") << "] "
           << 1/(60000.0/elapsedTime.elapsed()) << " minutes uptime\n";
       logfile.close();

/******* if log.txt is bigger than set in preferences, delete first line *******/
       bool isBigger;
       if(logfile.size()>logFileSize*1000)
         isBigger = true;
       else
         isBigger = false;
       while(isBigger){
         logfile.open(QIODevice::ReadWrite | QIODevice::Text);
         QTextStream out(&logfile);
         out.readLine();
         QString content = out.readAll();
         logfile.resize(0);
         out << content;
         logfile.close();
         if(logfile.size()<=logFileSize*1000)
           isBigger = false;
       }
     }
}

void Gui::finished_(){
     if(!pref->quitAfterCountdown->isChecked())
       reset();
     switch(comboBox->currentIndex()){
       case 0:
         if(pref->shutdownM->currentIndex()==0) { Power::automatic = true; }
         if(pref->shutdownM->currentIndex()==1) { Power::gnome = true; }
         if(pref->shutdownM->currentIndex()==2) { Power::kde = true; }
         if(pref->shutdownM->currentIndex()==3) { Power::hal_ = true; }
         if(pref->shutdownM->currentIndex()==4) { Power::consolekit = true; }
         if(pref->shutdownM->currentIndex()==5) { Power::sudo = true; }
         if(pref->shutdownM->currentIndex()==6) {
           Power::user = true;
           Power::myShutdown = pref->myShutdown;
         }
         saveLog();
         Power::shutdown();
         break;
       case 1:
         if(pref->rebootM->currentIndex()==0) { Power::automatic = true; }
         if(pref->rebootM->currentIndex()==1) { Power::gnome = true; }
         if(pref->rebootM->currentIndex()==2) { Power::kde = true; }
         if(pref->rebootM->currentIndex()==3) { Power::hal_ = true; }
         if(pref->rebootM->currentIndex()==4) { Power::consolekit = true; }
         if(pref->rebootM->currentIndex()==5) { Power::sudo = true; }
         if(pref->rebootM->currentIndex()==6) {
           Power::user = true;
           Power::myReboot = pref->myReboot;
         }
         saveLog();
         Power::reboot();
         break;
       case 2:
         if(pref->suspendM->currentIndex()==0) { Power::automatic = true; }
         if(pref->suspendM->currentIndex()==1) { Power::gnome = true; }
         if(pref->suspendM->currentIndex()==2) { Power::hal_ = true; }
         if(pref->suspendM->currentIndex()==3) { Power::upower_ = true; }
         if(pref->suspendM->currentIndex()==4) { Power::devicekit = true; }
         if(pref->suspendM->currentIndex()==5) {
           Power::user = true;
           Power::mySuspend = pref->mySuspend;
         }
         if(pref->lockMyScreen){ Power::lockMyScreen = true; }
         Power::suspend();
         break;
       case 3:
         if(pref->hibernateM->currentIndex()==0) { Power::automatic = true; }
         if(pref->hibernateM->currentIndex()==1) { Power::gnome = true; }
         if(pref->hibernateM->currentIndex()==2) { Power::hal_ = true; }
         if(pref->hibernateM->currentIndex()==3) { Power::upower_ = true; }
         if(pref->hibernateM->currentIndex()==4) { Power::devicekit = true; }
         if(pref->hibernateM->currentIndex()==5) {
           Power::user = true;
           Power::myHibernate = pref->myHibernate;
         }
         if(pref->lockMyScreen){ Power::lockMyScreen = true; }
         Power::hibernate();
         break;
       default:;
     }
     if(pref->quitAfterCountdown->isChecked())
       qApp->quit();
}

void Gui::hideEvent(QHideEvent* window_hide){
     minimize_restore_action->setText(tr("Res&tore"));
     QWidget::hideEvent(window_hide);
}

void Gui::closeEvent(QCloseEvent* window_close){
     if(!pref->getQuitOnClose())
       hide();
     else if(!editor->getLockAll())
       qApp->quit();
     QWidget::closeEvent(window_close);
}

void Gui::beforeQuit(){
     saveLog();
  #ifndef Q_OS_WIN32
     QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME, QDBusConnection::UnregisterNode);
     QDBusConnection::sessionBus().unregisterService(SERVICE_NAME);
  #endif //Q_OS_WIN32
}

void Gui::loadSettings(){
/***************** create file and it's entries *****************/
#ifdef Q_OS_WIN32
     QString file(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/qshutdown/qshutdown.conf");
#else //!Q_OS_WIN32
     QString file(QDir::homePath() + "/.qshutdown/qshutdown.conf");
#endif //Q_OS_WIN32
     QSettings settings(file, QSettings::IniFormat);

     if(!settings.isWritable()){
       QTextStream myOutput;
       myOutput << "W: qshutdown.conf is not writable!" << endl;
     }

     if(!settings.contains("Lock_all"))
       settings.setValue("Lock_all",false);
     if(!settings.contains("MainWindow/keep_proportions"))
       settings.setValue("MainWindow/keep_proportions",true);
    #ifndef Q_OS_WIN32
     QFile autostartFile(QDir::homePath() + "/.config/autostart/qshutdown.desktop");
     if(autostartFile.exists())
       settings.setValue("Autostart",true);
     else
       settings.setValue("Autostart",false);
    #endif

     pref->autostartFile();


/***************** read files entries *****************/
     timeEdit->setTime(QTime(settings.value("Time/time_hour",22).toInt(),settings.value("Time/time_minute",00).toInt()));
     spin->setValue(settings.value("Time/countdown_minutes",60).toInt());
     resize(settings.value("MainWindow/size",QSize(290,280)).toSize());
     actionKeep_window_proportions->setChecked(settings.value("MainWindow/keep_proportions",true).toBool());
     font1->setFamily(settings.value("Fonts/font_type","Times New Roman").toString());
     font2->setFamily(settings.value("Fonts/font_type","Times New Roman").toString());
     font3->setFamily(settings.value("Fonts/font_type","Times New Roman").toString());
     font1->setPointSize(settings.value("Fonts/font1",13).toInt());
     font2->setPointSize(settings.value("Fonts/font2",18).toInt());
     font3->setPointSize(settings.value("Fonts/font3",11).toInt());


     radio1->setChecked(settings.value("CheckBoxes/target_time",false).toBool());
     radio2->setChecked(settings.value("CheckBoxes/countdown",true).toBool());
     lock->setChecked(settings.value("CheckBoxes/lock",true).toBool());
     comboBox->setCurrentIndex(settings.value("Power/comboBox",0).toInt());
     warnings->setChecked(settings.value("CheckBoxes/warnings",true).toBool());
     log_action->setChecked(settings.value("Logfile/logging",false).toBool());
     logFileSize = settings.value("Logfile/size",1.5).toDouble();

     if(settings.value("Time/countdown_at_startup",false).toBool()){
       set();
       if(settings.value("Hide_at_startup",false).toBool())
         QTimer::singleShot(2000, this, SLOT(hide()));
     }

     staticProportions(settings.value("MainWindow/keep_proportions",true).toBool());

     lockEverything(settings.value("Lock_all",false).toBool());

     QList<QWidget*> list;
     list << lcdL << comboBox << targetTime
          << minutes << spin << timeEdit;
     foreach(QWidget * ptr, list)
       ptr->setFont(*font1);
     ok->setFont(*font2);
     minim->setFont(*font2);
     warnings->setFont(*font3);
     lock->setFont(*font3);
     now->setFont(*font3);
     toolButton->setFont(*font3);

     switch(settings.value("Power/comboBox").toInt()){
       case 0:
         targetTime->setText(tr("Shutdown-time:"));
         minutes->setText(tr("Minutes till shutdown:"));
         shutdown_action->setChecked(true);
         break;
       case 1:
         targetTime->setText(tr("Reboot-time:"));
         minutes->setText(tr("Minutes till reboot:"));
         reboot_action->setChecked(true);
         break;
       case 2:
         targetTime->setText(tr("Suspend-time:"));
         minutes->setText(tr("Minutes till suspend:"));
         suspend_action->setChecked(true);
         break;
       case 3:
         targetTime->setText(tr("Hibernate-time:"));
         minutes->setText(tr("Minutes till hibernate:"));
         hibernate_action->setChecked(true);
         break;
       default:;
     }
}

void Gui::lockEverything(bool actual){
     if(radio1->isChecked())
       timeEdit->setDisabled(actual);
     else
       spin->setDisabled(actual);

     quit_action->setDisabled(actual);
     actionQuit->setDisabled(actual);
     log_action->setDisabled(actual);
     actionLog_file->setDisabled(actual);
     power_actions->setDisabled(actual);

     QList<QWidget*> widgetList;
     widgetList << radio1 << radio2 << lock << comboBox << targetTime
                << minutes << pref->comboBox << pref->timeEdit << pref->spin
                << pref->radio1 << pref->radio2 << pref->stopHide
                << pref->autostart << pref->lock << pref->countdown
                << pref->log << pref->reset << pref->spinBox << pref->tab2;
     foreach(QWidget * widgetPtr, widgetList)
       widgetPtr->setDisabled(actual);

     if(lock->isChecked() && timeRunning && !actual){
       QList<QWidget*> widgetList2;
       widgetList2 << timeEdit << spin << radio1  << radio2 << comboBox
                   << targetTime << minutes << pref->tab2;
       foreach(QWidget * widgetPtr2, widgetList2)
             widgetPtr2->setDisabled(true);
     }
     if(timeRunning){
       reset_action->setDisabled(actual);
       action_Reset->setDisabled(actual);
     }
     else{
       reset_action->setDisabled(true);
       action_Reset->setDisabled(true);
     }

/*   if(actual){
       if(!parentalLockL->isVisible())
         parentalLockL->show();
       statusBar()->addPermanentWidget(parentalLockL);
     }
     if(!actual && parentalLockL->isVisible())
       statusBar()->removeWidget(parentalLockL);*/
}
void Gui::reset(){
     timer->stop();
     setWindowTitle("'qshutdown'");
     toolButton->setText("Calendar");
     lcd->display(0);
     TIcon->setToolTip(NULL);
     lcdL->setText(tr("minutes"));
     cal->setCalendarDate = QDate();
     cal->calendarDate = QDate();
     showNormal();
     if(!ti->isActive())
       ti->start(30000);
     timeRunning = false;
     minim->hide();
     ok->show();
     pref->tab2->setEnabled(true);
     if(!editor->getLockAll())
       lockEverything(false);
     else loadSettings();
     action_Reset->setDisabled(true);
     reset_action->setDisabled(true);
     //statusBar()->removeWidget(customL);
}

void Gui::getFonts(){
     font1->setFamily(pref->fonts);
     font1->setPointSize(pref->fontS1);
     font2->setFamily(pref->fonts);
     font2->setPointSize(pref->fontS2);
     font3->setFamily(pref->fonts);
     font3->setPointSize(pref->fontS3);

     QList<QWidget*> list;
     list << lcdL << comboBox << targetTime
          << minutes << spin << timeEdit;
     foreach(QWidget * ptr, list)
       ptr->setFont(*font1);
     ok->setFont(*font2);
     minim->setFont(*font2);
     warnings->setFont(*font3);
     lock->setFont(*font3);
     now->setFont(*font3);
     toolButton->setFont(*font3);
}

void Gui::showCalendarBox(){
     if(cal->setCalendarDate.isNull())
       cal->calendarWidget->setSelectedDate(QDate::currentDate());
     else
       cal->calendarWidget->setSelectedDate(cal->setCalendarDate);
     if(editor->getLockAll() || (timeRunning && lock->isChecked()))
       cal->calendarWidget->blockSignals(true);
     else
       cal->calendarWidget->blockSignals(false);
     cal->show();
}

void Gui::updateLock(){
     if(editor->getLockAll())
       lockEverything(true);
     else
       lockEverything(false);
}

void Gui::showEditor(){ QTimer::singleShot(250, editor, SLOT(show())); } //using singleShot because of focus problems...

void Gui::staticProportions(bool var){
     if(var)
       frame->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
     else
       frame->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}
