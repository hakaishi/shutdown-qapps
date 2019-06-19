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
#ifndef WEEKDAYITEM_H
#define WEEKDAYITEM_H

#include <QWidget>
#include <QTimeEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QSpacerItem>

class WeekDayItem : public QWidget{
    Q_OBJECT
 
    public:
     WeekDayItem(QWidget *parent = 0);
     ~WeekDayItem();
     QTimeEdit *timeEdit;
     QComboBox *comboBox;

    private:
     QSpacerItem *h2;
     QHBoxLayout *itemL;
};

#endif //WEEKDAYITEM_H
