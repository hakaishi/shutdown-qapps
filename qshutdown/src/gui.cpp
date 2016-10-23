/* qshutdown, a program to shutdown the shutdown/reboot/suspend/hibernate
 * Copyright (C) 2010-2015 Christian Metscher <hakaishi@web.de>

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
     aWeeklyTimeWasSet = false;
     logFileSize = 1.5;
     oldComboBoxIndex = comboBox->currentIndex();
     oldTime = timeEdit->time();

     datetime = QDateTime::currentDateTimeUtc();
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
     connect(pref, SIGNAL(finishing()), this, SLOT(warnings_on())); //start the QTimer ti if timeRunning == false
     connect(pref, SIGNAL(changeFont()), this, SLOT(getFonts()));
     connect(pref, SIGNAL(editConf()), checkPassword, SLOT(show()));  //ask for password when button was pressed at preferences
     connect(pref, SIGNAL(removeTrayIcon(bool)), this, SLOT(hideTrayIcon(bool)));

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

     connect(checkPassword, SIGNAL(success()), this, SLOT(showEditor())); //if correct password was entered open editor
     connect(checkPassword, SIGNAL(starting()), ti, SLOT(stop()));
     connect(checkPassword, SIGNAL(starting()), pref, SLOT(accept()));
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

     connect(timeEdit, SIGNAL(timeChanged(QTime)), this, SLOT(saveOldTime(QTime)));
     connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(saveOldComboBoxIndex(int)));
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
     QMainWindow::showEvent(show_window);
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

void Gui::saveOldTime(QTime time){
     if(!aWeeklyTimeWasSet)
       oldTime = time;
}

void Gui::saveOldComboBoxIndex(int i){
     if(!aWeeklyTimeWasSet)
       oldComboBoxIndex = i;
}

void Gui::setDate(){
     if(!cal->weekly->isChecked() && !timeRunning) {
       if(cal->setCalendarDate.date() != QDate())
         toolButton->setText(cal->setCalendarDate.date().toString(Qt::SystemLocaleShortDate));
     }
     else if(!cal->setWeeklyDate.time().isNull() && !timeRunning){
       toolButton->setText(cal->setWeeklyDate.date().toString("ddd"));
       aWeeklyTimeWasSet = true;
       timeEdit->setTime(cal->setWeeklyDate.time());

       QDateTime myTime = cal->setWeeklyDate; //just for convenience
       QList<WeekDayItem *> item; // get the objects of the matching day
       if(myTime.date().dayOfWeek() == Qt::Monday)
         item << cal->mon1 << cal->mon2 << cal->mon3 << cal->mon4 << cal->mon5;
       else if(myTime.date().dayOfWeek() == Qt::Tuesday)
         item << cal->tue1 << cal->tue2 << cal->tue3 << cal->tue4 << cal->tue5;
       else if(myTime.date().dayOfWeek() == Qt::Wednesday)
         item << cal->wed1 << cal->wed2 << cal->wed3 << cal->wed4 << cal->wed5;
       else if(myTime.date().dayOfWeek() == Qt::Thursday)
         item << cal->thu1 << cal->thu2 << cal->thu3 << cal->thu4 << cal->thu5;
       else if(myTime.date().dayOfWeek() == Qt::Friday)
         item << cal->fri1 << cal->fri2 << cal->fri3 << cal->fri4 << cal->fri5;
       else if(myTime.date().dayOfWeek() == Qt::Saturday)
         item << cal->sat1 << cal->sat2 << cal->sat3 << cal->sat4 << cal->sat5;
       else if(myTime.date().dayOfWeek() == Qt::Sunday)
         item << cal->sun1 << cal->sun2 << cal->sun3 << cal->sun4 << cal->sun5;
       while(item[0]->timeEdit->time() != myTime.time()) //get the correct time from the object
         item.removeAt(0); //just leave the matching time
       if(item.count() != 0)
         comboBox->setCurrentIndex(item[0]->comboBox->currentIndex());

       radio1->setChecked(true);
       radio2->setDisabled(true);
       radio1->setDisabled(true);
       timeEdit->setDisabled(true);
       comboBox->setDisabled(true);
     }
     if((cal->setCalendarDate == QDateTime()) && (cal->setWeeklyDate == QDateTime()))
       if(!timeRunning){
          timeEdit->setTime(oldTime);
          comboBox->setCurrentIndex(oldComboBoxIndex);
          aWeeklyTimeWasSet = false;
          radio2->setDisabled(false);
          radio1->setDisabled(false);
          if(radio1->isChecked())
            timeEdit->setDisabled(false);
          else
            spin->setDisabled(false);
          comboBox->setDisabled(false);
          toolButton->setText(tr("Calendar"));
       }
}

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
     QDateTime myDate = QDateTime::currentDateTimeUtc();
     QString tip1, tip2;

     if(shutdown_action->isChecked())
       tip1 = (tr("shutdown in "));
     else if(reboot_action->isChecked())
       tip1 = (tr("reboot in "));
     else if(suspend_action->isChecked())
       tip1 = (tr("suspend in "));
     else if(hibernate_action->isChecked())
       tip1 = (tr("hibernate in "));

     int dayDiff = myDate.date().daysTo(futureDateTime.date());

     if(dayDiff < 0){ //reset if targeted date is already in the past.
       reset();
       return;
     } //end

     else if(dayDiff > 1){ //if the date difference between today and the selected day
                                                           //in the calendar is greater than one
     //if more than one year
       if(dayDiff > myDate.date().daysInYear()){
         tip2 = (QString::number(dayDiff/myDate.date().daysInYear()) + " " + tr("years"));
         lcdL->setText(tr("years"));
         lcd->setDigitCount(4);
         lcd->display((double)dayDiff/myDate.date().daysInYear());
       }
     //if more than one month
       else if(dayDiff > myDate.date().daysInMonth()
           && dayDiff <= myDate.date().daysInYear()){
         tip2 = (QString::number(dayDiff/myDate.date().daysInMonth()) + " " + tr("months"));
         lcdL->setText(tr("months"));
         if((double)dayDiff/myDate.date().daysInMonth() >= 10)
           lcd->setDigitCount(4);
         else
           lcd->setDigitCount(3);
         lcd->display((double)dayDiff/myDate.date().daysInMonth());
       }
     //if less than days in Month
       else if(dayDiff <= myDate.date().daysInMonth()){
         tip2 = (QString::number(dayDiff) + " " + tr("days"));
         lcdL->setText(tr("days"));
         if((double)dayDiff >= 10)
           lcd->setDigitCount(4);
         else
           lcd->setDigitCount(3);
         lcd->display((double)dayDiff);
       }
     } //end of year/month

     else if(dayDiff == 1){ //if there is one more day to go
       if(!Time())
         return;

       if(i>=86400){ //if one day and some time to go
         tip2 = (">= 1 " + tr("day"));
         lcd->setDigitCount(3);
         lcd->display(bigI/86400);
         if(lcd->value() > 1.1)
           lcdL->setText(tr("days"));
         else
           lcdL->setText(tr("day"));
       }
       else if(i<86400 && i>3600){ //if there is less than one day, show hours
         tip2 = (QString::number(i/3600) + " " + tr("hours"));
         lcdL->setText(tr("hours"));
         if(bigI/3600 >= 10)
           lcd->setDigitCount(4);
         else
           lcd->setDigitCount(3);
         lcd->display(bigI/3600);
       }
       else if(i<=3600 && i>60){ //if less than one hour
         tip2 = (QString::number(i/60) + " " + tr("minutes"));
         lcdL->setText(tr("minutes"));
         if(bigI/60 >= 10){
           lcd->setDigitCount(4);
           lcd->display(bigI/60);
         }
         else
           lcd->setDigitCount(3);
         lcd->display(bigI/60);
       }
       else if(i<=60){
         tip2 = (QString::number(i) + " " + tr("seconds"));
         lcdL->setText(tr("seconds"));
         lcd->display(i);
       }
     }
     else if(dayDiff == 0){
       if(!Time())
         return;

       if(warnings->isChecked() && (((i<=100) && (i>95)) || ((i<=40) && (i>35))) && !ti->isActive())
         ti->start(30000);

       if(i > 3600){ //Display hours and minutes
         tip2 = (QString::number(i/3600) + " " + tr("hours") + " + "
                + QString::number(i/60 - (i/3600)*60) + " " + tr("minutes"));
         lcdL->setText(tr("hours"));
         if(bigI/3600 >= 10)
           lcd->setDigitCount(4);
         else
           lcd->setDigitCount(3);
         lcd->display(bigI/3600);
       }
       else if(i<=3600 && i>=60){ //Display only minutes
         tip2 = (QString::number(i/60) + " " + tr("minutes"));
         lcdL->setText(tr("minutes"));
         if(bigI/60 >= 10)
           lcd->setDigitCount(4);
         else
           lcd->setDigitCount(3);
         lcd->display(bigI/60);
       }
       else if(i<=60 && i > 0){ //Display only seconds
         tip2 = (QString::number(i) + " " + tr("seconds"));
         lcdL->setText(tr("seconds"));
         lcd->display(i);
       }

     //this will ensure that the shutdown-type will be executed in case a few seconds were skipped
       else if((i<=0) && !(i<-n))
         finished_(); //execute shutdown-type
     }
     setWindowTitle(tip1 + tip2);
     TIcon->setToolTip(tip1 + tip2);
}

void Gui::set(){
     QDateTime dateTime = QDateTime::currentDateTime();
     futureDateTime = dateTime; //initializing
     timeRunning = true;
     cal->timeRunning = true;
     ti->stop();
     bool noCalendarDate = cal->setCalendarDate.isNull();
     bool noWeeklyDate = cal->setWeeklyDate.isNull();
     if(!noCalendarDate)
       futureDateTime = cal->setCalendarDate;
     if(!noWeeklyDate)
       futureDateTime = cal->setWeeklyDate;

     if(noWeeklyDate){
       futureDateTime.setTime(dateTime.time());
       if(radio2->isChecked()) //if minute-countdown
         futureDateTime = futureDateTime.addSecs(spin->value()*60);
       else if(radio1->isChecked()){ //if timeEdit
         if(QDateTime(futureDateTime.date(),timeEdit->time(), Qt::LocalTime) > dateTime) //set time is greater than current time
           futureDateTime = QDateTime(futureDateTime.date(),timeEdit->time(),Qt::LocalTime);
         else if(noCalendarDate && (timeEdit->time() <= dateTime.time()))
           futureDateTime = QDateTime(futureDateTime.date().addDays(1),timeEdit->time(),Qt::LocalTime); //add 1 day
       }
     }

     updateT(); //Just updating time/interface for immediate display of remaining time.
     timer->start(1000); //Update time/interface every second

     if(lock->isChecked() || editor->getLockAll()){       //when OK-button is clicked and lock is checked
       QList<QWidget*> list;
       list << spin << radio1 << radio2 << lock << timeEdit << comboBox << targetTime
            << minutes << pref->tab2 << cal->weekly << cal->scrollAreaWidgetContents;
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

bool Gui::Time(){
     localDateTime = QDateTime::currentDateTimeUtc();
     QDateTime futureDateTime10s = futureDateTime; //adding n (10 seconds) in case of hardware delay.
     futureDateTime10s.addSecs(n);

     if(QDateTime::currentDateTimeUtc() > futureDateTime10s){ //if targeted time for action is
                          //already over 10 seconds in the past.
       reset();
       return false;
     }
     else{
       i = localDateTime.secsTo(futureDateTime); //the difference of the localTime and the future time
       bigI = i; //for more precise display with LCD
       return true;
     }
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
       case 1:
         switch(pref->shutdownM->currentIndex()){
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
            case 7:
                Power::user = true;
                if(comboBox->currentIndex() == 0)
                    Power::myShutdown = pref->myShutdown;
                else if(comboBox->currentIndex() == 1)
                    Power::myReboot = pref->myReboot;
                break;
            default:;
         }
         saveLog();
         if(comboBox->currentIndex() == 0)
            Power::shutdown();
         else if(comboBox->currentIndex() == 1)
            Power::reboot();
         Power::shutdown();
         break;
       case 2:
       case 3:
         switch(pref->shutdownM->currentIndex()){
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
            case 6:
                Power::user = true;
                if(comboBox->currentIndex() == 2)
                    Power::mySuspend = pref->mySuspend;
                else if(comboBox->currentIndex() == 3)
                    Power::myHibernate = pref->myHibernate;
                break;
            default:;
         }
         if(pref->lockMyScreen){ Power::lockMyScreen = true; }
         else Power::lockMyScreen = false;
         if(comboBox->currentIndex() == 2)
            Power::suspend();
         else if(comboBox->currentIndex() == 3)
            Power::hibernate();
         break;

       default:;
     }
     if(pref->quitAfterCountdown->isChecked())
       qApp->quit();
}

void Gui::hideEvent(QHideEvent* window_hide){
     minimize_restore_action->setText(tr("Res&tore"));
     QMainWindow::hideEvent(window_hide);
}

void Gui::closeEvent(QCloseEvent* window_close){
     if(!pref->quitOnCloseMain->isChecked() && pref->disableTray->isChecked())
       showMinimized();
     if(!pref->quitOnCloseMain->isChecked() && !pref->disableTray->isChecked())
       hide();
     if(pref->quitOnCloseMain->isChecked() && !editor->getLockAll())
       qApp->quit();
     QMainWindow::closeEvent(window_close);
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

#ifdef Q_OS_WIN32
     QString fonts = "Times New Roman";
     int fontS1 = 13;
     int fontS2 = 18;
     int fontS3 = 11;
#else
     QString fonts = "DejaVu Sans";
     int fontS1 = 11;
     int fontS2 = 15;
     int fontS3 = 9;
#endif



/***************** read files entries *****************/
     timeEdit->setTime(QTime(settings.value("Time/time_hour",22).toInt(),settings.value("Time/time_minute",00).toInt()));
     spin->setValue(settings.value("Time/countdown_minutes",60).toInt());
     resize(settings.value("MainWindow/size",QSize(290,280)).toSize());
     actionKeep_window_proportions->setChecked(settings.value("MainWindow/keep_proportions",true).toBool());
     font1->setFamily(settings.value("Fonts/font_type",fonts).toString());
     font2->setFamily(settings.value("Fonts/font_type",fonts).toString());
     font3->setFamily(settings.value("Fonts/font_type",fonts).toString());
     font1->setPointSize(settings.value("Fonts/font1",fontS1).toInt());
     font2->setPointSize(settings.value("Fonts/font2",fontS2).toInt());
     font3->setPointSize(settings.value("Fonts/font3",fontS3).toInt());

     radio1->setChecked(settings.value("CheckBoxes/target_time",false).toBool());
     radio2->setChecked(settings.value("CheckBoxes/countdown",true).toBool());
     lock->setChecked(settings.value("CheckBoxes/lock",true).toBool());
     comboBox->setCurrentIndex(settings.value("Power/comboBox",0).toInt());
     warnings->setChecked(settings.value("CheckBoxes/warnings",true).toBool());
     log_action->setChecked(settings.value("Logfile/logging",false).toBool());
     logFileSize = settings.value("Logfile/size",1.5).toDouble();

     //if(settings.contains("Weekly_is_set") && settings.value("Weekly_is_set").toBool())
       cal->setDate();

     if(settings.value("Time/countdown_at_startup",false).toBool()){
       set();
       if(settings.value("Hide_at_startup",false).toBool())
         QTimer::singleShot(2000, this, SLOT(hide()));
     }

     hideTrayIcon(settings.value("CheckBoxes/Disable_tray_icon", false).toBool());

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
                << pref->radio1 << pref->radio2 << pref->quitOnCloseMain
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
     
     if(aWeeklyTimeWasSet){
       radio1->setChecked(true);
       radio2->setDisabled(true);
       radio1->setDisabled(true);
       timeEdit->setDisabled(true);
       comboBox->setDisabled(true);
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
     cal->setWeeklyDate = QDateTime();
     setWindowTitle("'qshutdown'");
     if(!aWeeklyTimeWasSet)
       toolButton->setText(tr("Calendar"));
     lcd->display(0);
     TIcon->setToolTip(NULL);
     lcdL->setText(tr("minutes"));
     cal->setCalendarDate.setDate(QDate());
     cal->calendarDate.setDate(QDate());
     cal->weekly->setEnabled(true);
     cal->scrollAreaWidgetContents->setEnabled(true);
     showNormal();
     if(!ti->isActive())
       ti->start(30000);
     timeRunning = false;
     cal->timeRunning = false;
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
       cal->calendarWidget->setSelectedDate(cal->setCalendarDate.date());
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

void Gui::hideTrayIcon(bool dontShowTray){ //or only minimize if not
     if(!dontShowTray)
       TIcon->show();
     else
       TIcon->hide();
}
