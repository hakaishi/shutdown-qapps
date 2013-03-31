/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
 * Copyright (C) 2010-2013 Christian Metscher <hakaishi@web.de>

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

#include "info.h"

Info::Info(QWidget *parent): QTextEdit(parent){

     isClosed = true;

     setWindowFlags(Qt::Window);
     setReadOnly(true);
     resize(500,450);
     setWindowTitle(tr("Info"));
}

Info::~Info(){ }

void Info::showEvent(QShowEvent* show_Info){
     isClosed = false;
     starting();
     QWidget::showEvent(show_Info);
}

void Info::closeEvent(QCloseEvent* close_Info){
     isClosed = true;
     finishing();
     QWidget::closeEvent(close_Info);
}

bool Info::getClosed(){ return isClosed; }
