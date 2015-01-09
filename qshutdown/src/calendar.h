/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
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
#ifndef CALENDAR_H
#define CALENDAR_H

#include "ui_calendar.h"
#include <QDate>

class Calendar : public QDialog, public Ui::Calendar {
     Q_OBJECT
 
    public:
     Calendar(QWidget *parent = 0);
     ~Calendar();
     QDate setCalendarDate, calendarDate;
     bool getClosed();

    private:
     bool isClosed;

    private slots:
     void getDate(QDate date);
     void setDate();

    signals:
     void aDateWasSet();
     void starting();
     void finishing();

    protected:
     virtual void showEvent(QShowEvent* show_calendar);
     virtual void closeEvent(QCloseEvent* close_calendar);

};

#endif //CALENDAR_H
