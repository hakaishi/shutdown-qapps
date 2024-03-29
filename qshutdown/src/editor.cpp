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

#include "editor.h"
#include <QDir>
#include <QPushButton>
#include <QTextStream>

Editor::Editor(QWidget *parent): QDialog(parent){

     setupUi(this);

     isClosed = true;

     setWindowFlags(Qt::Window);    //always in front

     confFile = new QFile(QSettings().fileName());

     plainTextEdit->setFocus();

     connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(saveChanges()));
     connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(close()));
     connect(buttonBox->button(QDialogButtonBox::Save), SIGNAL(clicked(bool)), this, SLOT(saveChanges()));
     connect(buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked(bool)), this, SLOT(close()));
     connect(this, SIGNAL(rejected()), this, SLOT(close()));
}

Editor::~Editor(){ delete confFile; }

void Editor::showEvent(QShowEvent* show_editor){
     isClosed = false;
     if(!confFile->open(QIODevice::ReadWrite | QIODevice::Text)){
       QTextStream myOutput(stdout);
       myOutput << "E: Can not open qshutdown settings file!" << Qt::endl;
       return;
     }
     QString text;                      //reading content of qshutdown settings
     QTextStream in(confFile);
     text = in.readAll();
     plainTextEdit->setPlainText(text);
     confFile->close();

     starting();

     QDialog::showEvent(show_editor);
}

void Editor::closeEvent(QCloseEvent* close_editor){
     isClosed = true;
     finishing();
     QDialog::closeEvent(close_editor);
}

bool Editor::getClosed(){ return isClosed; }

bool Editor::getLockAll(){
     QSettings settings(this);
     return settings.value("Lock_all").toBool();
}

void Editor::keyPressEvent(QKeyEvent *kEvent){
     if((kEvent->modifiers() == Qt::ControlModifier) && (kEvent->key() == Qt::Key_S))
       saveChanges();
     if(((kEvent->modifiers() == Qt::ControlModifier) && (kEvent->key() == Qt::Key_Q))
         || (kEvent->key() == Qt::Key_Escape))
       reject();
}

void Editor::saveChanges(){
     if(!confFile->open(QIODevice::ReadWrite | QIODevice::Text)){
       QTextStream myOutput(stdout);
       myOutput << "E: Can not open qshutdown settings file!";
       return;
     }
     QString newContent;                //writing content of editor to qshutdown settings
     newContent = plainTextEdit->toPlainText();
     QTextStream out(confFile);
     out << newContent;
     confFile->close();
     saved();  //Signal that changes have been saved
}
