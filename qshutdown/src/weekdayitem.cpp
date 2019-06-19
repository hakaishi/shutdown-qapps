/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
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

#include "weekdayitem.h"
#include <QCoreApplication>

WeekDayItem::WeekDayItem(QWidget *parent) : QWidget(parent){
     itemL = new QHBoxLayout(this);
     itemL->setContentsMargins(0,0,0,0);
     h2 =  new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

     timeEdit = new QTimeEdit(this);
     QString timeEditFormat = timeEdit->displayFormat();
     if(timeEditFormat.contains(":ss"))
       timeEditFormat.replace(QString(":ss"), QString(""));
     if(timeEditFormat.contains(":s"))
       timeEditFormat.replace(QString(":s"), QString(""));
     timeEdit->setDisplayFormat(timeEditFormat);
     timeEdit->setTime(QTime(22,0,0));

     comboBox = new QComboBox(this);
     comboBox->insertItems(0, QStringList()
         << QCoreApplication::translate("Gui", "Shutdown", 0)
         << QCoreApplication::translate("Gui", "Reboot", 0)
         << QCoreApplication::translate("Gui", "Suspend", 0)
         << QCoreApplication::translate("Gui", "Hibernate", 0)
        );

     itemL->addItem(h2);
     itemL->addWidget(timeEdit);
     itemL->addWidget(comboBox);
}

WeekDayItem::~WeekDayItem(){;}
