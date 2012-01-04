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

#include "about.h"
#include <QFile>
#include <QTextStream>

About::About(QWidget *parent): QDialog(parent){

     setupUi(this);

     textBrowser->setOpenExternalLinks(true);

   //Versioning
     QFile versionFile(":version");
     versionFile.open(QIODevice::ReadOnly | QIODevice::Text);
     QTextStream in(&versionFile);
     QString string = in.readLine();
     version->setText(string);
     versionFile.close();

     icon = QIcon(":red_glasses_image");
     QPixmap pixmap = icon.pixmap(QSize(60,60), QIcon::Normal, QIcon::On);
     label->setPixmap(pixmap);
}

About::~About(){ }
