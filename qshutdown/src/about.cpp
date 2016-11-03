/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
 * Copyright (C) 2010-2016 Christian Metscher <hakaishi@web.de>

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

     textBrowser_2->setHtml(tr("<p >Special thanks to:<br /></p>"
                               "<p >Fabian Deuchler for helping here and "
                               "there.<br /><br />And Brian Nelson for "
                               "sponsoring the uploads to Debian.<br /><br />"
                               "As well as to Miquel Banchs i Piqué for the idea of "
                               "implementing a routine allowing custom settings for "
                               "each day of the week.</p>"));
     textBrowser->setText(tr("<p >qshutdown, a time and countdown based shutdown tool</p>"
                             "<p >Author: Christian Metscher &lt;hakaishi@web.de&gt;</p>"
                             "<p >Copyright &copy; 2010-2016, by Christian Metscher</p>"
                             "<p ><a href=\"https://launchpad.net/~hakaishi\">"
                             "<span style=\" text-decoration: underline; "
                             "color:#0000ff;\">https://launchpad.net/~hakaishi</span></a></p>"
                             "<p >Please use <a href=\"https://bugs.launchpad.net/qt-"
                             "shutdown-p\"><span style=\" text-decoration: underline; "
                             "color:#0000ff;\">https://bugs.launchpad.net/qt-shutdown-p</span></a>"
                             " or <a href=\"http://www.debian.org/Bugs/Reporting\">"
                             "<span style=\" text-decoration: underline; "
                             "color:#0000ff;\">http://www.debian.org/Bugs/Reporting</span>"
                             "</a> to report bugs.</p>"));

   //Versioning
     QFile versionFile(":version");
     versionFile.open(QIODevice::ReadOnly | QIODevice::Text);
     QTextStream in(&versionFile);
     QString string = in.readLine();
     version->setText(tr("Version ") + string);
     versionFile.close();

     icon = QIcon(":red_glasses_image");
     QPixmap pixmap = icon.pixmap(QSize(60,60), QIcon::Normal, QIcon::On);
     label->setPixmap(pixmap);
}

About::~About(){ }
