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
#include <QDateTime>
#include <QSettings>
#include "weekday.h"
#include "weekdayitem.h"

class Calendar : public QDialog, public Ui::Calendar {
     Q_OBJECT
 
    public:
     Calendar(QWidget *parent = 0);
     ~Calendar();
     bool timeRunning;
     QDateTime setCalendarDate, calendarDate, setWeeklyDate;
     bool getClosed();
     WeekDay     *mon, *tue, *wed, *thu, *fri,
                 *sat, *sun;
     WeekDayItem *mon1, *mon2, *mon3, *mon4, *mon5,
                 *tue1, *tue2, *tue3, *tue4, *tue5,
                 *wed1, *wed2, *wed3, *wed4, *wed5,
                 *thu1, *thu2, *thu3, *thu4, *thu5,
                 *fri1, *fri2, *fri3, *fri4, *fri5,
                 *sat1, *sat2, *sat3, *sat4, *sat5,
                 *sun1, *sun2, *sun3, *sun4, *sun5;

    private:
     QVBoxLayout *scrollArea_layout;
     bool isClosed;
     QList<WeekDayItem* > *mondayItems;
     QList<WeekDayItem* > *tuesdayItems;
     QList<WeekDayItem* > *wednesdayItems;
     QList<WeekDayItem* > *thursdayItems;
     QList<WeekDayItem* > *fridayItems;
     QList<WeekDayItem* > *saturdayItems;
     QList<WeekDayItem* > *sundayItems;
     QSettings *settings;
     QString file;

    private slots:
     void getDate(QDate date);
     void getSortedAndActivatedDays();
     void getNearestTime(QList<int> calculatedDay);
     QList<QTime> getSortedTimes();
     void loadSettings();
     void saveToConfFile();
     void monday_addTimeEditAndActionBox(int i);
     void tuesday_addTimeEditAndActionBox(int i);
     void wednesday_addTimeEditAndActionBox(int i);
     void thursday_addTimeEditAndActionBox(int i);
     void friday_addTimeEditAndActionBox(int i);
     void saturday_addTimeEditAndActionBox(int i);
     void sunday_addTimeEditAndActionBox(int i);

    public slots:
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
