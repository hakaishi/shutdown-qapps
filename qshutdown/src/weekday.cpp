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

#include "weekday.h"

WeekDay::WeekDay(QWidget *parent) : QFrame(parent){
     this->setFrameShape(QFrame::Panel);
     this->setFrameShadow(QFrame::Raised);
     dayL = new QHBoxLayout(this);
     dayL->setContentsMargins(0,0,0,0);
     label = new QLabel(this);
     h = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
     spin = new QSpinBox(this);
     spin->setRange(0,5);

     dayL->addWidget(label);
     dayL->addItem(h);
     dayL->addWidget(spin);
}

WeekDay::~WeekDay(){;}
