/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
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

#include "calendar.h"
#include <QPushButton>

Calendar::Calendar(QWidget *parent): QDialog(parent){

     setupUi(this);

     isClosed = true;

     setWindowFlags(Qt::Window);

     calendarWidget->setMinimumDate(QDate::currentDate());

     connect(calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(getDate(QDate)));
     connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(setDate()));
}

Calendar::~Calendar(){;}

void Calendar::getDate(QDate date){ calendarDate = date; }

void Calendar::setDate(){
     if(!calendarDate.isNull()){ //if a day was selected
       setCalendarDate = calendarDate;
       aDateWasSet();
     }
}

void Calendar::showEvent(QShowEvent* show_calendar){
     isClosed = false;
     starting();
     QWidget::showEvent(show_calendar);
}

void Calendar::closeEvent(QCloseEvent* close_calendar){
     isClosed = true;
     finishing();
     QWidget::closeEvent(close_calendar);
}

bool Calendar::getClosed(){ return isClosed; }
