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

#include "calendar.h"
#include <QPushButton>
#include <QFile>
#include <QDir>
#include <QDesktopServices>

Calendar::Calendar(QWidget *parent): QDialog(parent){

     setupUi(this);

     isClosed = true;
     timeRunning = false;

     setWindowFlags(Qt::Window);

     settings = new QSettings(this);

     calendarWidget->setMinimumDate(QDate::currentDate());

     mondayItems = new QList<WeekDayItem* >;
     tuesdayItems = new QList<WeekDayItem* >;
     wednesdayItems = new QList<WeekDayItem* >;
     thursdayItems = new QList<WeekDayItem* >;
     fridayItems = new QList<WeekDayItem* >;
     saturdayItems = new QList<WeekDayItem* >;
     sundayItems = new QList<WeekDayItem* >;

     mon = new WeekDay(this);
     mon->label->setText(QDate::longDayName(Qt::Monday));
     mon1 = new WeekDayItem(this);
     mon2 = new WeekDayItem(this);
     mon3 = new WeekDayItem(this);
     mon4 = new WeekDayItem(this);
     mon5 = new WeekDayItem(this);
     *mondayItems << mon1 << mon2 << mon3 << mon4 << mon5;
     tue = new WeekDay(this);
     tue->label->setText(QDate::longDayName(Qt::Tuesday));
     tue1 = new WeekDayItem(this);
     tue2 = new WeekDayItem(this);
     tue3 = new WeekDayItem(this);
     tue4 = new WeekDayItem(this);
     tue5 = new WeekDayItem(this);
     *tuesdayItems << tue1 << tue2 << tue3 << tue4 << tue5;
     wed = new WeekDay(this);
     wed->label->setText(QDate::longDayName(Qt::Wednesday));
     wed1 = new WeekDayItem(this);
     wed2 = new WeekDayItem(this);
     wed3 = new WeekDayItem(this);
     wed4 = new WeekDayItem(this);
     wed5 = new WeekDayItem(this);
     *wednesdayItems << wed1 << wed2 << wed3 << wed4 << wed5;
     thu = new WeekDay(this);
     thu->label->setText(QDate::longDayName(Qt::Thursday));
     thu1 = new WeekDayItem(this);
     thu2 = new WeekDayItem(this);
     thu3 = new WeekDayItem(this);
     thu4 = new WeekDayItem(this);
     thu5 = new WeekDayItem(this);
     *thursdayItems << thu1 << thu2 << thu3 << thu4 << thu5;
     fri = new WeekDay(this);
     fri->label->setText(QDate::longDayName(Qt::Friday));
     fri1 = new WeekDayItem(this);
     fri2 = new WeekDayItem(this);
     fri3 = new WeekDayItem(this);
     fri4 = new WeekDayItem(this);
     fri5 = new WeekDayItem(this);
     *fridayItems << fri1 << fri2 << fri3 << fri4 << fri5;
     sat = new WeekDay(this);
     sat->label->setText(QDate::longDayName(Qt::Saturday));
     sat1 = new WeekDayItem(this);
     sat2 = new WeekDayItem(this);
     sat3 = new WeekDayItem(this);
     sat4 = new WeekDayItem(this);
     sat5 = new WeekDayItem(this);
     *saturdayItems << sat1 << sat2 << sat3 << sat4 << sat5;
     sun = new WeekDay(this);
     sun->label->setText(QDate::longDayName(Qt::Sunday));
     sun1 = new WeekDayItem(this);
     sun2 = new WeekDayItem(this);
     sun3 = new WeekDayItem(this);
     sun4 = new WeekDayItem(this);
     sun5 = new WeekDayItem(this);
     *sundayItems << sun1 << sun2 << sun3 << sun4 << sun5;

     verticalLayout_3->addWidget(mon,0,Qt::AlignTop);
     foreach(WeekDayItem *item, *mondayItems){
       verticalLayout_3->addWidget(item,0,Qt::AlignTop);
       item->setVisible(false);
       item->setEnabled(false);
     }
     verticalLayout_3->addWidget(tue,0,Qt::AlignTop);
     foreach(WeekDayItem *item, *tuesdayItems){
       verticalLayout_3->addWidget(item,0,Qt::AlignTop);
       item->setVisible(false);
       item->setEnabled(false);
     }
     verticalLayout_3->addWidget(wed,0,Qt::AlignTop);
     foreach(WeekDayItem *item, *wednesdayItems){
       verticalLayout_3->addWidget(item,0,Qt::AlignTop);
       item->setVisible(false);
       item->setEnabled(false);
     }
     verticalLayout_3->addWidget(thu,0,Qt::AlignTop);
     foreach(WeekDayItem *item, *thursdayItems){
       verticalLayout_3->addWidget(item,0,Qt::AlignTop);
       item->setVisible(false);
       item->setEnabled(false);
     }
     verticalLayout_3->addWidget(fri,0,Qt::AlignTop);
     foreach(WeekDayItem *item, *fridayItems){
       verticalLayout_3->addWidget(item,0,Qt::AlignTop);
       item->setVisible(false);
       item->setEnabled(false);
     }
     verticalLayout_3->addWidget(sat,0,Qt::AlignTop);
     foreach(WeekDayItem *item, *saturdayItems){
       verticalLayout_3->addWidget(item,0,Qt::AlignTop);
       item->setVisible(false);
       item->setEnabled(false);
     }
     verticalLayout_3->addWidget(sun,0,Qt::AlignTop);
     foreach(WeekDayItem *item, *sundayItems){
       verticalLayout_3->addWidget(item,0,Qt::AlignTop);
       item->setVisible(false);
       item->setEnabled(false);
     }

     verticalLayout_3->setSpacing(0);

     connect(calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(getDate(QDate)));
     connect(weekly, SIGNAL(toggled(bool)), scrollAreaWidgetContents, SLOT(setEnabled(bool)));
     connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(setDate()));
     connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(saveToConfFile()));
     connect(mon->spin, SIGNAL(valueChanged(int)), this, SLOT(monday_addTimeEditAndActionBox(int)));
     connect(tue->spin, SIGNAL(valueChanged(int)), this, SLOT(tuesday_addTimeEditAndActionBox(int)));
     connect(wed->spin, SIGNAL(valueChanged(int)), this, SLOT(wednesday_addTimeEditAndActionBox(int)));
     connect(thu->spin, SIGNAL(valueChanged(int)), this, SLOT(thursday_addTimeEditAndActionBox(int)));
     connect(fri->spin, SIGNAL(valueChanged(int)), this, SLOT(friday_addTimeEditAndActionBox(int)));
     connect(sat->spin, SIGNAL(valueChanged(int)), this, SLOT(saturday_addTimeEditAndActionBox(int)));
     connect(sun->spin, SIGNAL(valueChanged(int)), this, SLOT(sunday_addTimeEditAndActionBox(int)));

     if(!QFile::exists(file))
       saveToConfFile();
     else
       loadSettings();

}

Calendar::~Calendar(){ delete settings; }

void Calendar::getDate(QDate date){ calendarDate.setDate(date); }

void Calendar::setDate(){
     if(calendarWidget->selectedDate() != QDate::currentDate())
        calendarDate.setDate(calendarWidget->selectedDate());
     if(!weekly->isChecked() && calendarDate.isValid()
       && calendarDate.date() != QDate::currentDate()) //if a day was selected
       setCalendarDate = calendarDate; //don't touch calendarDate!
     else
       setCalendarDate = QDateTime();
     if(weekly->isChecked())
       getSortedAndActivatedDays();
     else
       setWeeklyDate = QDateTime();

     aDateWasSet();
}

void Calendar::getSortedAndActivatedDays(){
     int activatedDays[7] = {0, 0, 0, 0, 0, 0, 0}; //note that each day has at least the value 0!
     if(mon->spin->value() > 0) //check if an item is available for each day.
       activatedDays[0] = Qt::Monday; //Qt::Monday is int 1 etc.
     if(tue->spin->value() > 0)
       activatedDays[1] = Qt::Tuesday;
     if(wed->spin->value() > 0)
       activatedDays[2] = Qt::Wednesday;
     if(thu->spin->value() > 0)
       activatedDays[3] = Qt::Thursday;
     if(fri->spin->value() > 0)
       activatedDays[4] = Qt::Friday;
     if(sat->spin->value() > 0)
       activatedDays[5] = Qt::Saturday;
     if(sun->spin->value() > 0)
       activatedDays[6] = Qt::Sunday;

     int todaysDayOfWeek = QDate::currentDate().dayOfWeek();

     QList<int> calculatedDay;
     for(int i=0; i < 7; i++){
       if(activatedDays[i] != 0){ // if zero, then there were no items!
         int x = activatedDays[i] - todaysDayOfWeek;
         if(x < 0)
           x += 7;
         calculatedDay << x;
       }
     } //note that all calculated days are in the future. Only if it is today, the time can be in the past!

     if(calculatedDay.isEmpty()){
       setWeeklyDate = QDateTime();
       aDateWasSet();
       return;
     }

     qSort(calculatedDay);
     setWeeklyDate = QDateTime::currentDateTime().addDays(calculatedDay[0]);

     getNearestTime(calculatedDay);
}

void Calendar::getNearestTime(QList<int> calculatedDay){
     QList<QTime> times = getSortedTimes();

     if(QDateTime(setWeeklyDate.date(),times[0]) > QDateTime::currentDateTime())
       setWeeklyDate.setTime(times[0]);
     else{
       int i = 0; //first index for the list of the sorted times
       while((QDateTime(setWeeklyDate.date(),times[i]) <= QDateTime::currentDateTime())
             && (i < times.count())){ //as long as we have a next position and the time is in the past: i+1
         ++i;
       } //at this point we have either a matching time or nothing. Nothing would be bad...
       if(i < times.count()) //there has been a matching time...
         setWeeklyDate.setTime(times[i]);
       if(i >= times.count()){ //there was no matching time, but there still might be one on another day.
         if(calculatedDay.count() > 1){ //if there is at least another day...
           setWeeklyDate = QDateTime::currentDateTime().addDays(calculatedDay[1]); //take another day...
           times = getSortedTimes();      //and get the new times list.
           setWeeklyDate.setTime(times[0]); //the first time setting will do.
         }
         else{ // there is no other day => +7
           setWeeklyDate = QDateTime::currentDateTime().addDays(7);
           setWeeklyDate.setTime(times[0]);
         }
       }
     }
}

QList<QTime> Calendar::getSortedTimes(){
     QList<QTime> times;
     if(setWeeklyDate.date().dayOfWeek() == Qt::Monday) //Which day of week is the choosen day?
       foreach(WeekDayItem *item, *mondayItems)
         if(item->isEnabled()) //get all items if they are visible/enabled.
           times << item->timeEdit->time();
     if(setWeeklyDate.date().dayOfWeek() == Qt::Tuesday)
       foreach(WeekDayItem *item, *tuesdayItems)
         if(item->isEnabled())
           times << item->timeEdit->time();
     if(setWeeklyDate.date().dayOfWeek() == Qt::Wednesday)
       foreach(WeekDayItem *item, *wednesdayItems)
         if(item->isEnabled())
           times << item->timeEdit->time();
     if(setWeeklyDate.date().dayOfWeek() == Qt::Thursday)
       foreach(WeekDayItem *item, *thursdayItems)
         if(item->isEnabled())
           times << item->timeEdit->time();
     if(setWeeklyDate.date().dayOfWeek() == Qt::Friday)
       foreach(WeekDayItem *item, *fridayItems)
         if(item->isEnabled())
           times << item->timeEdit->time();
     if(setWeeklyDate.date().dayOfWeek() == Qt::Saturday)
       foreach(WeekDayItem *item, *saturdayItems)
         if(item->isEnabled())
           times << item->timeEdit->time();
     if(setWeeklyDate.date().dayOfWeek() == Qt::Sunday)
       foreach(WeekDayItem *item, *sundayItems)
         if(item->isEnabled())
           times << item->timeEdit->time();

     for(int i=0; i < times.count()-1; i++){   //sort all available times
       for(int x=0; x < times.count()-1; x++){
         if(times[x] > times[x+1])
           times.swap(x,x+1);
       }
     }

     return times;
}

void Calendar::showEvent(QShowEvent* show_calendar){
     isClosed = false;
     starting();
     loadSettings();
     QDialog::showEvent(show_calendar);
}

void Calendar::closeEvent(QCloseEvent* close_calendar){
     isClosed = true;
     finishing();
     QDialog::closeEvent(close_calendar);
}

bool Calendar::getClosed(){ return isClosed; }

void Calendar::monday_addTimeEditAndActionBox(int i){
     QList<WeekDayItem *> removeItemList;
     QList<WeekDayItem *> addItemList;

     switch(i){
       case 0:
         removeItemList << mon1 << mon2 << mon3 << mon4 << mon5;
         break;
       case 1:
         addItemList << mon1;
         removeItemList << mon2 << mon3 << mon4<< mon5;
         break;
       case 2:
         addItemList << mon1 << mon2;
         removeItemList << mon3 << mon4 << mon5;
         break;
       case 3:
         addItemList << mon1 << mon2 << mon3;
         removeItemList << mon4 << mon5;
         break;
       case 4:
         addItemList << mon1 << mon2 << mon3 << mon4;
         removeItemList << mon5;
         break;
       case 5:
         addItemList << mon1 << mon2 << mon3 << mon4 << mon5;
         break;
       default:;
     }

     foreach(WeekDayItem *item, addItemList){
       item->setVisible(true);
       item->setEnabled(true);
     }
     foreach(WeekDayItem *item, removeItemList){
       item->setVisible(false);
       item->setEnabled(false);
     }
}

void Calendar::tuesday_addTimeEditAndActionBox(int i){
     QList<WeekDayItem *> removeItemList;
     QList<WeekDayItem *> addItemList;

     switch(i){
       case 0:
         removeItemList << tue1 << tue2 << tue3 << tue4 << tue5;
         break;
       case 1:
         addItemList << tue1;
         removeItemList << tue2 << tue3 << tue4<< tue5;
         break;
       case 2:
         addItemList << tue1 << tue2;
         removeItemList << tue3 << tue4 << tue5;
         break;
       case 3:
         addItemList << tue1 << tue2 << tue3;
         removeItemList << tue4 << tue5;
         break;
       case 4:
         addItemList << tue1 << tue2 << tue3 << tue4;
         removeItemList << tue5;
         break;
       case 5:
         addItemList << tue1 << tue2 << tue3 << tue4 << tue5;
         break;
       default:;
     }

     foreach(WeekDayItem *item, addItemList){
       item->setVisible(true);
       item->setEnabled(true);
     }
     foreach(WeekDayItem *item, removeItemList){
       item->setVisible(false);
       item->setEnabled(false);
     }
}

void Calendar::wednesday_addTimeEditAndActionBox(int i){
     QList<WeekDayItem *> removeItemList;
     QList<WeekDayItem *> addItemList;

     switch(i){
       case 0:
         removeItemList << wed1 << wed2 << wed3 << wed4 << wed5;
         break;
       case 1:
         addItemList << wed1;
         removeItemList << wed2 << wed3 << wed4<< wed5;
         break;
       case 2:
         addItemList << wed1 << wed2;
         removeItemList << wed3 << wed4 << wed5;
         break;
       case 3:
         addItemList << wed1 << wed2 << wed3;
         removeItemList << wed4 << wed5;
         break;
       case 4:
         addItemList << wed1 << wed2 << wed3 << wed4;
         removeItemList << wed5;
         break;
       case 5:
         addItemList << wed1 << wed2 << wed3 << wed4 << wed5;
         break;
       default:;
     }

     foreach(WeekDayItem *item, addItemList){
       item->setVisible(true);
       item->setEnabled(true);
     }
     foreach(WeekDayItem *item, removeItemList){
       item->setVisible(false);
       item->setEnabled(false);
     }
}

void Calendar::thursday_addTimeEditAndActionBox(int i){
     QList<WeekDayItem *> removeItemList;
     QList<WeekDayItem *> addItemList;

     switch(i){
       case 0:
         removeItemList << thu1 << thu2 << thu3 << thu4 << thu5;
         break;
       case 1:
         addItemList << thu1;
         removeItemList << thu2 << thu3 << thu4<< thu5;
         break;
       case 2:
         addItemList << thu1 << thu2;
         removeItemList << thu3 << thu4 << thu5;
         break;
       case 3:
         addItemList << thu1 << thu2 << thu3;
         removeItemList << thu4 << thu5;
         break;
       case 4:
         addItemList << thu1 << thu2 << thu3 << thu4;
         removeItemList << thu5;
         break;
       case 5:
         addItemList << thu1 << thu2 << thu3 << thu4 << thu5;
         break;
       default:;
     }

     foreach(WeekDayItem *item, addItemList){
       item->setVisible(true);
       item->setEnabled(true);
     }
     foreach(WeekDayItem *item, removeItemList){
       item->setVisible(false);
       item->setEnabled(false);
     }
}

void Calendar::friday_addTimeEditAndActionBox(int i){
     QList<WeekDayItem *> removeItemList;
     QList<WeekDayItem *> addItemList;

     switch(i){
       case 0:
         removeItemList << fri1 << fri2 << fri3 << fri4 << fri5;
         break;
       case 1:
         addItemList << fri1;
         removeItemList << fri2 << fri3 << fri4<< fri5;
         break;
       case 2:
         addItemList << fri1 << fri2;
         removeItemList << fri3 << fri4 << fri5;
         break;
       case 3:
         addItemList << fri1 << fri2 << fri3;
         removeItemList << fri4 << fri5;
         break;
       case 4:
         addItemList << fri1 << fri2 << fri3 << fri4;
         removeItemList << fri5;
         break;
       case 5:
         addItemList << fri1 << fri2 << fri3 << fri4 << fri5;
         break;
       default:;
     }

     foreach(WeekDayItem *item, addItemList){
       item->setVisible(true);
       item->setEnabled(true);
     }
     foreach(WeekDayItem *item, removeItemList){
       item->setVisible(false);
       item->setEnabled(false);
     }
}

void Calendar::saturday_addTimeEditAndActionBox(int i){
     QList<WeekDayItem *> removeItemList;
     QList<WeekDayItem *> addItemList;

     switch(i){
       case 0:
         removeItemList << sat1 << sat2 << sat3 << sat4 << sat5;
         break;
       case 1:
         addItemList << sat1;
         removeItemList << sat2 << sat3 << sat4<< sat5;
         break;
       case 2:
         addItemList << sat1 << sat2;
         removeItemList << sat3 << sat4 << sat5;
         break;
       case 3:
         addItemList << sat1 << sat2 << sat3;
         removeItemList << sat4 << sat5;
         break;
       case 4:
         addItemList << sat1 << sat2 << sat3 << sat4;
         removeItemList << sat5;
         break;
       case 5:
         addItemList << sat1 << sat2 << sat3 << sat4 << sat5;
         break;
       default:;
     }

     foreach(WeekDayItem *item, addItemList){
       item->setVisible(true);
       item->setEnabled(true);
     }
     foreach(WeekDayItem *item, removeItemList){
       item->setVisible(false);
       item->setEnabled(false);
     }
}

void Calendar::sunday_addTimeEditAndActionBox(int i){
     QList<WeekDayItem *> removeItemList;
     QList<WeekDayItem *> addItemList;

     switch(i){
       case 0:
         removeItemList << sun1 << sun2 << sun3 << sun4 << sun5;
         break;
       case 1:
         addItemList << sun1;
         removeItemList << sun2 << sun3 << sun4<< sun5;
         break;
       case 2:
         addItemList << sun1 << sun2;
         removeItemList << sun3 << sun4 << sun5;
         break;
       case 3:
         addItemList << sun1 << sun2 << sun3;
         removeItemList << sun4 << sun5;
         break;
       case 4:
         addItemList << sun1 << sun2 << sun3 << sun4;
         removeItemList << sun5;
         break;
       case 5:
         addItemList << sun1 << sun2 << sun3 << sun4 << sun5;
         break;
       default:;
     }

     foreach(WeekDayItem *item, addItemList){
       item->setVisible(true);
       item->setEnabled(true);
     }
     foreach(WeekDayItem *item, removeItemList){
       item->setVisible(false);
       item->setEnabled(false);
     }
}

void Calendar::saveToConfFile(){
     if(settings->isWritable()){
       settings->setValue("Calendar/size",size());
       settings->setValue("Calendar_or_weekly",tabWidget->currentIndex());
       settings->setValue("Weekly_is_set",weekly->isChecked());
       settings->setValue("Monday/number_of_times",mon->spin->value());
       settings->setValue("Monday/time_1",mon1->timeEdit->time().toString());
       settings->setValue("Monday/time_2",mon2->timeEdit->time().toString());
       settings->setValue("Monday/time_3",mon3->timeEdit->time().toString());
       settings->setValue("Monday/time_4",mon4->timeEdit->time().toString());
       settings->setValue("Monday/time_5",mon5->timeEdit->time().toString());
       settings->setValue("Monday/method_1",mon1->comboBox->currentIndex());
       settings->setValue("Monday/method_2",mon2->comboBox->currentIndex());
       settings->setValue("Monday/method_3",mon3->comboBox->currentIndex());
       settings->setValue("Monday/method_4",mon4->comboBox->currentIndex());
       settings->setValue("Monday/method_5",mon5->comboBox->currentIndex());
       settings->setValue("Tuesday/number_of_times",tue->spin->value());
       settings->setValue("Tuesday/time_1",tue1->timeEdit->time().toString());
       settings->setValue("Tuesday/time_2",tue2->timeEdit->time().toString());
       settings->setValue("Tuesday/time_3",tue3->timeEdit->time().toString());
       settings->setValue("Tuesday/time_4",tue4->timeEdit->time().toString());
       settings->setValue("Tuesday/time_5",tue5->timeEdit->time().toString());
       settings->setValue("Tuesday/method_1",tue1->comboBox->currentIndex());
       settings->setValue("Tuesday/method_2",tue2->comboBox->currentIndex());
       settings->setValue("Tuesday/method_3",tue3->comboBox->currentIndex());
       settings->setValue("Tuesday/method_4",tue4->comboBox->currentIndex());
       settings->setValue("Tuesday/method_5",tue5->comboBox->currentIndex());
       settings->setValue("Wednesday/number_of_times",wed->spin->value());
       settings->setValue("Wednesday/time_1",wed1->timeEdit->time().toString());
       settings->setValue("Wednesday/time_2",wed2->timeEdit->time().toString());
       settings->setValue("Wednesday/time_3",wed3->timeEdit->time().toString());
       settings->setValue("Wednesday/time_4",wed4->timeEdit->time().toString());
       settings->setValue("Wednesday/time_5",wed5->timeEdit->time().toString());
       settings->setValue("Wednesday/method_1",wed1->comboBox->currentIndex());
       settings->setValue("Wednesday/method_2",wed2->comboBox->currentIndex());
       settings->setValue("Wednesday/method_3",wed3->comboBox->currentIndex());
       settings->setValue("Wednesday/method_4",wed4->comboBox->currentIndex());
       settings->setValue("Wednesday/method_5",wed5->comboBox->currentIndex());
       settings->setValue("Thursday/number_of_times",thu->spin->value());
       settings->setValue("Thursday/time_1",thu1->timeEdit->time().toString());
       settings->setValue("Thursday/time_2",thu2->timeEdit->time().toString());
       settings->setValue("Thursday/time_3",thu3->timeEdit->time().toString());
       settings->setValue("Thursday/time_4",thu4->timeEdit->time().toString());
       settings->setValue("Thursday/time_5",thu5->timeEdit->time().toString());
       settings->setValue("Thursday/method_1",thu1->comboBox->currentIndex());
       settings->setValue("Thursday/method_2",thu2->comboBox->currentIndex());
       settings->setValue("Thursday/method_3",thu3->comboBox->currentIndex());
       settings->setValue("Thursday/method_4",thu4->comboBox->currentIndex());
       settings->setValue("Thursday/method_5",thu5->comboBox->currentIndex());
       settings->setValue("Friday/number_of_times",fri->spin->value());
       settings->setValue("Friday/time_1",fri1->timeEdit->time().toString());
       settings->setValue("Friday/time_2",fri2->timeEdit->time().toString());
       settings->setValue("Friday/time_3",fri3->timeEdit->time().toString());
       settings->setValue("Friday/time_4",fri4->timeEdit->time().toString());
       settings->setValue("Friday/time_5",fri5->timeEdit->time().toString());
       settings->setValue("Friday/method_1",fri1->comboBox->currentIndex());
       settings->setValue("Friday/method_2",fri2->comboBox->currentIndex());
       settings->setValue("Friday/method_3",fri3->comboBox->currentIndex());
       settings->setValue("Friday/method_4",fri4->comboBox->currentIndex());
       settings->setValue("Friday/method_5",fri5->comboBox->currentIndex());
       settings->setValue("Saturday/number_of_times",sat->spin->value());
       settings->setValue("Saturday/time_1",sat1->timeEdit->time().toString());
       settings->setValue("Saturday/time_2",sat2->timeEdit->time().toString());
       settings->setValue("Saturday/time_3",sat3->timeEdit->time().toString());
       settings->setValue("Saturday/time_4",sat4->timeEdit->time().toString());
       settings->setValue("Saturday/time_5",sat5->timeEdit->time().toString());
       settings->setValue("Saturday/method_1",sat1->comboBox->currentIndex());
       settings->setValue("Saturday/method_2",sat2->comboBox->currentIndex());
       settings->setValue("Saturday/method_3",sat3->comboBox->currentIndex());
       settings->setValue("Saturday/method_4",sat4->comboBox->currentIndex());
       settings->setValue("Saturday/method_5",sat5->comboBox->currentIndex());
       settings->setValue("Sunday/number_of_times",sun->spin->value());
       settings->setValue("Sunday/time_1",sun1->timeEdit->time().toString());
       settings->setValue("Sunday/time_2",sun2->timeEdit->time().toString());
       settings->setValue("Sunday/time_3",sun3->timeEdit->time().toString());
       settings->setValue("Sunday/time_4",sun4->timeEdit->time().toString());
       settings->setValue("Sunday/time_5",sun5->timeEdit->time().toString());
       settings->setValue("Sunday/method_1",sun1->comboBox->currentIndex());
       settings->setValue("Sunday/method_2",sun2->comboBox->currentIndex());
       settings->setValue("Sunday/method_3",sun3->comboBox->currentIndex());
       settings->setValue("Sunday/method_4",sun4->comboBox->currentIndex());
       settings->setValue("Sunday/method_5",sun5->comboBox->currentIndex());
     }
}

void Calendar::loadSettings(){
     resize(settings->value("MainWindow/size",QSize(325,360)).toSize());
     tabWidget->setCurrentIndex(settings->value("Calendar_or_weekly",0).toInt());
     weekly->setChecked(settings->value("Weekly_is_set", false).toBool());
     if(!timeRunning)
       scrollAreaWidgetContents->setEnabled(weekly->isChecked());
     mon->spin->setValue(settings->value("Monday/number_of_times",0).toInt());
     mon1->timeEdit->setTime(QTime::fromString(settings->value("Monday/time_1","22:00:00").toString(), "hh:mm:ss"));
     mon2->timeEdit->setTime(QTime::fromString(settings->value("Monday/time_2","22:00:00").toString(), "hh:mm:ss"));
     mon3->timeEdit->setTime(QTime::fromString(settings->value("Monday/time_3","22:00:00").toString(), "hh:mm:ss"));
     mon4->timeEdit->setTime(QTime::fromString(settings->value("Monday/time_4","22:00:00").toString(), "hh:mm:ss"));
     mon5->timeEdit->setTime(QTime::fromString(settings->value("Monday/time_5","22:00:00").toString(), "hh:mm:ss"));
     mon1->comboBox->setCurrentIndex(settings->value("Monday/method_1",0).toInt());
     mon2->comboBox->setCurrentIndex(settings->value("Monday/method_2",0).toInt());
     mon3->comboBox->setCurrentIndex(settings->value("Monday/method_3",0).toInt());
     mon4->comboBox->setCurrentIndex(settings->value("Monday/method_4",0).toInt());
     mon5->comboBox->setCurrentIndex(settings->value("Monday/method_5",0).toInt());
     tue->spin->setValue(settings->value("Tuesday/number_of_times",0).toInt());
     tue1->timeEdit->setTime(QTime::fromString(settings->value("Tuesday/time_1","22:00:00").toString(), "hh:mm:ss"));
     tue2->timeEdit->setTime(QTime::fromString(settings->value("Tuesday/time_2","22:00:00").toString(), "hh:mm:ss"));
     tue3->timeEdit->setTime(QTime::fromString(settings->value("Tuesday/time_3","22:00:00").toString(), "hh:mm:ss"));
     tue4->timeEdit->setTime(QTime::fromString(settings->value("Tuesday/time_4","22:00:00").toString(), "hh:mm:ss"));
     tue5->timeEdit->setTime(QTime::fromString(settings->value("Tuesday/time_5","22:00:00").toString(), "hh:mm:ss"));
     tue1->comboBox->setCurrentIndex(settings->value("Tuesday/method_1",0).toInt());
     tue2->comboBox->setCurrentIndex(settings->value("Tuesday/method_2",0).toInt());
     tue3->comboBox->setCurrentIndex(settings->value("Tuesday/method_3",0).toInt());
     tue4->comboBox->setCurrentIndex(settings->value("Tuesday/method_4",0).toInt());
     tue5->comboBox->setCurrentIndex(settings->value("Tuesday/method_5",0).toInt());
     wed->spin->setValue(settings->value("Wednesday/number_of_times",0).toInt());
     wed1->timeEdit->setTime(QTime::fromString(settings->value("Wednesday/time_1","22:00:00").toString(), "hh:mm:ss"));
     wed2->timeEdit->setTime(QTime::fromString(settings->value("Wednesday/time_2","22:00:00").toString(), "hh:mm:ss"));
     wed3->timeEdit->setTime(QTime::fromString(settings->value("Wednesday/time_3","22:00:00").toString(), "hh:mm:ss"));
     wed4->timeEdit->setTime(QTime::fromString(settings->value("Wednesday/time_4","22:00:00").toString(), "hh:mm:ss"));
     wed5->timeEdit->setTime(QTime::fromString(settings->value("Wednesday/time_5","22:00:00").toString(), "hh:mm:ss"));
     wed1->comboBox->setCurrentIndex(settings->value("Wednesday/method_1",0).toInt());
     wed2->comboBox->setCurrentIndex(settings->value("Wednesday/method_2",0).toInt());
     wed3->comboBox->setCurrentIndex(settings->value("Wednesday/method_3",0).toInt());
     wed4->comboBox->setCurrentIndex(settings->value("Wednesday/method_4",0).toInt());
     wed5->comboBox->setCurrentIndex(settings->value("Wednesday/method_5",0).toInt());
     thu->spin->setValue(settings->value("Thursday/number_of_times",0).toInt());
     thu1->timeEdit->setTime(QTime::fromString(settings->value("Thursday/time_1","22:00:00").toString(), "hh:mm:ss"));
     thu2->timeEdit->setTime(QTime::fromString(settings->value("Thursday/time_2","22:00:00").toString(), "hh:mm:ss"));
     thu3->timeEdit->setTime(QTime::fromString(settings->value("Thursday/time_3","22:00:00").toString(), "hh:mm:ss"));
     thu4->timeEdit->setTime(QTime::fromString(settings->value("Thursday/time_4","22:00:00").toString(), "hh:mm:ss"));
     thu5->timeEdit->setTime(QTime::fromString(settings->value("Thursday/time_5","22:00:00").toString(), "hh:mm:ss"));
     thu1->comboBox->setCurrentIndex(settings->value("Thursday/method_1",0).toInt());
     thu2->comboBox->setCurrentIndex(settings->value("Thursday/method_2",0).toInt());
     thu3->comboBox->setCurrentIndex(settings->value("Thursday/method_3",0).toInt());
     thu4->comboBox->setCurrentIndex(settings->value("Thursday/method_4",0).toInt());
     thu5->comboBox->setCurrentIndex(settings->value("Thursday/method_5",0).toInt());
     fri->spin->setValue(settings->value("Friday/number_of_times",0).toInt());
     fri1->timeEdit->setTime(QTime::fromString(settings->value("Friday/time_1","22:00:00").toString(), "hh:mm:ss"));
     fri2->timeEdit->setTime(QTime::fromString(settings->value("Friday/time_2","22:00:00").toString(), "hh:mm:ss"));
     fri3->timeEdit->setTime(QTime::fromString(settings->value("Friday/time_3","22:00:00").toString(), "hh:mm:ss"));
     fri4->timeEdit->setTime(QTime::fromString(settings->value("Friday/time_4","22:00:00").toString(), "hh:mm:ss"));
     fri5->timeEdit->setTime(QTime::fromString(settings->value("Friday/time_5","22:00:00").toString(), "hh:mm:ss"));
     fri1->comboBox->setCurrentIndex(settings->value("Friday/method_1",0).toInt());
     fri2->comboBox->setCurrentIndex(settings->value("Friday/method_2",0).toInt());
     fri3->comboBox->setCurrentIndex(settings->value("Friday/method_3",0).toInt());
     fri4->comboBox->setCurrentIndex(settings->value("Friday/method_4",0).toInt());
     fri5->comboBox->setCurrentIndex(settings->value("Friday/method_5",0).toInt());
     sat->spin->setValue(settings->value("Saturday/number_of_times",0).toInt());
     sat1->timeEdit->setTime(QTime::fromString(settings->value("Saturday/time_1","22:00:00").toString(), "hh:mm:ss"));
     sat2->timeEdit->setTime(QTime::fromString(settings->value("Saturday/time_2","22:00:00").toString(), "hh:mm:ss"));
     sat3->timeEdit->setTime(QTime::fromString(settings->value("Saturday/time_3","22:00:00").toString(), "hh:mm:ss"));
     sat4->timeEdit->setTime(QTime::fromString(settings->value("Saturday/time_4","22:00:00").toString(), "hh:mm:ss"));
     sat5->timeEdit->setTime(QTime::fromString(settings->value("Saturday/time_5","22:00:00").toString(), "hh:mm:ss"));
     sat1->comboBox->setCurrentIndex(settings->value("Saturday/method_1",0).toInt());
     sat2->comboBox->setCurrentIndex(settings->value("Saturday/method_2",0).toInt());
     sat3->comboBox->setCurrentIndex(settings->value("Saturday/method_3",0).toInt());
     sat4->comboBox->setCurrentIndex(settings->value("Saturday/method_4",0).toInt());
     sat5->comboBox->setCurrentIndex(settings->value("Saturday/method_5",0).toInt());
     sun->spin->setValue(settings->value("Sunday/number_of_times",0).toInt());
     sun1->timeEdit->setTime(QTime::fromString(settings->value("Sunday/time_1","22:00:00").toString(), "hh:mm:ss"));
     sun2->timeEdit->setTime(QTime::fromString(settings->value("Sunday/time_2","22:00:00").toString(), "hh:mm:ss"));
     sun3->timeEdit->setTime(QTime::fromString(settings->value("Sunday/time_3","22:00:00").toString(), "hh:mm:ss"));
     sun4->timeEdit->setTime(QTime::fromString(settings->value("Sunday/time_4","22:00:00").toString(), "hh:mm:ss"));
     sun5->timeEdit->setTime(QTime::fromString(settings->value("Sunday/time_5","22:00:00").toString(), "hh:mm:ss"));
     sun1->comboBox->setCurrentIndex(settings->value("Sunday/method_1",0).toInt());
     sun2->comboBox->setCurrentIndex(settings->value("Sunday/method_2",0).toInt());
     sun3->comboBox->setCurrentIndex(settings->value("Sunday/method_3",0).toInt());
     sun4->comboBox->setCurrentIndex(settings->value("Sunday/method_4",0).toInt());
     sun5->comboBox->setCurrentIndex(settings->value("Sunday/method_5",0).toInt());
}
