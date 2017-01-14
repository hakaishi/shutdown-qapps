/* qshutdown, a program to shutdown/reboot/suspend/hibernate the system
 * Copyright (C) 2010-2017 Christian Metscher <hakaishi@web.de>

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
#ifndef EDITOR_H
#define EDITOR_H

#include "ui_editor.h"
#include <QFile>
#include <QSettings>

class Editor : public QDialog, public Ui::Editor {
    Q_OBJECT
 
    public:
     Editor(QWidget *parent = 0);
     ~Editor();
     bool getClosed();

    signals:
     void saved();
     void starting();
     void finishing();

    private:
     QFile     *confFile;
     QSettings *settings;
     bool      isClosed;

    private slots:
     void saveChanges();

    public slots:
     bool getLockAll();

    protected:
     virtual void showEvent(QShowEvent* show_editor);
     virtual void closeEvent(QCloseEvent* close_editor);
     void keyPressEvent(QKeyEvent* kEvent);

};

#endif //EDITOR_H
