/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
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
#ifndef GUI_H
#define GUI_H

#include "ui_gui.h"
#include <QtGlobal>
#include <QSystemTrayIcon>
#if QT_VERSION < 0x060000
#include <QDesktopWidget>
#endif
#include <QTextDocumentFragment>
#include <QDir>
#include <QElapsedTimer>

#if defined(Q_OS_LINUX)
  #include <QtDBus>
#endif

#define SERVICE_NAME  "org.qshutdown"
#define OBJECT_NAME "/org/qshutdown"

class Preferences;
class Info;
class Calendar;
class PassWord;
class Editor;
class About;

class Gui : public QMainWindow, public Ui::Gui {
     Q_OBJECT // important for creating own singals and slots
 
    public:
     Gui();
     ~Gui();
     void loadSettings();
     void center();
     QString information;
 
    private:
     bool            timeRunning;
     bool            aWeeklyTimeWasSet;
     QPushButton     *minim;
     QTimer          *timer, *ti;
     QDateTime       localDatetime, futureDateTime;
     QTime           oldTime;
     QElapsedTimer   elapsedTime;
     QPixmap         icon;
     QSystemTrayIcon *TIcon;
     QMenu           *menu;
     QActionGroup    *power_actions;
     QAction         *shutdown_action, *reboot_action,
                     *suspend_action, *hibernate_action;
     QAction         *minimize_restore_action, *quit_action,
                     *reset_action, *info_action, *log_action, *pref_action;
     int             i; //number of seconds left
     int             oldComboBoxIndex;
     double          bigI; //for more precise display
     const static int n = 30; //to check if i==0 was skipped
     QFont           *font1, *font2, *font3;
     double          logFileSize;
     Preferences     *pref;
     Info            *infoBox;
     Calendar        *cal;
     PassWord        *checkPassword;
     Editor          *editor;
     About           *about;
     //QLabel          *parentalLockL, *customL;

     // defining signals and slots
 
    private slots:
     void tray_actions();
     void warnings_on();
     void iconActivated(QSystemTrayIcon::ActivationReason reason);
     void showW();
     void updateT();
     bool Time();
     void power_action(int action);
     void power(QAction *action);
     void reset();
     void finished_();
     void beforeQuit();
     void setInfoText();
     void getFonts();
     void showCalendarBox();
     void saveOldTime(QTime time);
     void saveOldComboBoxIndex(int i);
     void setDate();
     void lockEverything(bool actual);
     void updateLock();
     void showEditor();
     void staticProportions(bool var);
     void saveLog();
     void saveLast();
     void hideTrayIcon(bool dontShowTray);
    public slots:
     Q_SCRIPTABLE void showRunningProgram();
     Q_SCRIPTABLE void set();
    protected:
     void keyPressEvent(QKeyEvent* kEvent);
     virtual void closeEvent(QCloseEvent* window_close);
     virtual void showEvent(QShowEvent* window_show);
     virtual void hideEvent(QHideEvent* window_hide);
};

#endif //GUI_H
