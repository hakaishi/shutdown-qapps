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
#ifndef GUI_H
#define GUI_H

#include "ui_gui.h"
#include <QFileDialog>
#include <QtGlobal>
#include <QSettings>
#include <QProcess>
#include <QTextStream>


class Gui : public QWidget, public Ui::Gui {
     Q_OBJECT // important for creating own singals and slots
 
     public:
      Gui(QWidget *parent = 0);
      ~Gui();
      void loadSettings();

     private:
      QTimer         *dateTimeTimer, *timer;
      QProcess       *process1, *process2;
      QDateTime      nextDate, timeInTheFuture;
      double         secondsToTimeInTheFuture;
      QTextEdit      *hintMsgBox, *logBox1, *logBox2;
      QString        file, errProcess1, errProcess2,
                     outputProcess1, outputProcess2;
      QSettings      *settings; 
      QString        program1, program2;
      bool           process2Started;
      bool           aborted;
      QTextStream    *myOutput;

     private slots:
      void currentDateAndTime(); //for the current minimum date and time
      void check();       //checks if the time that was set is reached
      void getProgram1();
      void getProgram2();
      void run();         //runs the process
      void abortProcesses();       //aborts all running processes
      void output1();      //prints output into a file if loggingCheckBox is checked
      void output2();
      void errorOutput1(); //prints errorOutput into a file if loggingCheckBox is checked
      void errorOutput2();
      void message();     //shows a messageBox if the process is finished, or if errors occured
      void checkForProcess2(); //if textEdit2 !=0 a second process will be started
      void shutdown_or_message(); //either shuts down the system or shows if the process is finished
      void info_hint();   //shows a InfoMessageBox
      void saveData();
      void showLogs();

     signals:
      void finished();

     protected:
      virtual void closeEvent(QCloseEvent* window_close);
};

#endif
