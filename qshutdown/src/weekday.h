/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
 * Copyright (C) 2010-2020 Christian Metscher <hakaishi@web.de>

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
#ifndef WEEKDAY_H
#define WEEKDAY_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QFrame>

class WeekDay : public QFrame{
    Q_OBJECT
 
    public:
     WeekDay(QWidget *parent = 0);
     ~WeekDay();
     QSpinBox *spin;
     QLabel *label;

    private:
     //QFrame *frame;
     QHBoxLayout *dayL;
     QSpacerItem *h;
};

#endif //WEEKDAY_H
