/* qshutdown, a program to shutdown the shutdown/reboot/suspend/hibernate
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
#ifndef POWER_H
#define POWER_H

#ifndef Q_OS_WIN32
  #include <QtDBus>
#endif

#include <QProcess>
#include <QTextStream>

extern bool verbose;

namespace Power{

QTextStream oput(stdout);

bool lockMyScreen;

void shutdown(){
   #ifdef Q_OS_WIN32
     QProcess::startDetached("shutdown -s -f -t 00"); // Windows command to shutdown immediately
   #else
     bool g = false; //gnome
     bool k = false; //kde
     bool g_pwr1 = false;
     bool g_pwr2 = false;
     bool hal = false;
     QDBusMessage response;

     QDBusInterface gnomeSessionManager("org.gnome.SessionManager",
       "/org/gnome/SessionManager", "org.gnome.SessionManager",
       QDBusConnection::sessionBus());
     response = gnomeSessionManager.call("RequestShutdown");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << endl;
       g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh shutdown");
       g_pwr2 = QProcess::startDetached("gnome-power-cmd shutdown");
       if(verbose && !g_pwr1 && !g_pwr2)
           oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
                << endl;
     }
     else
       g = true;

     if(!g && !g_pwr1 && !g_pwr2){
       QDBusInterface kdeSessionManager("org.kde.ksmserver", "/KSMServer",
         "org.kde.KSMServerInterface", QDBusConnection::sessionBus());
       response = kdeSessionManager.call("logout", 0, 2, 2);
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         k = true;
     }

     if(!g && !g_pwr1 && !g_pwr2 && !k){
       QDBusInterface powermanagement("org.freedesktop.Hal",
         "/org/freedesktop/Hal/devices/computer",
         "org.freedesktop.Hal.Device.SystemPowerManagement",
         QDBusConnection::systemBus());
       response = powermanagement.call("Shutdown");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         hal = true;
     }

     if(!g && !g_pwr1 && !g_pwr2 && !k && !hal){
       QDBusInterface powermanagement("org.freedesktop.ConsoleKit",
         "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager",
         QDBusConnection::systemBus());
       response = powermanagement.call("Stop");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
         QProcess::startDetached("sudo shutdown -P now");
       }
     }
   #endif
}

void reboot(){
   #ifdef Q_OS_WIN32
     QProcess::startDetached("shutdown -r -f -t 00"); // Windows command to reboot immediately
   #else
     bool g = false; //gnome
     bool k = false; //kde
     bool g_pwr1 = false;
     bool g_pwr2 = false;
     bool hal = false;
     QDBusMessage response;

     QDBusInterface gnomeSessionManager("org.gnome.SessionManager",
       "/org/gnome/SessionManager", "org.gnome.SessionManager",
       QDBusConnection::sessionBus());
     response = gnomeSessionManager.call("RequestReboot");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << endl;
       g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh reboot");
       g_pwr2 = QProcess::startDetached("gnome-power-cmd reboot");
       if(verbose && !g_pwr1 && !g_pwr2)
         oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
              << endl;
     }
     else
       g = true;

     if(!g && !g_pwr1 && !g_pwr2){
       QDBusInterface kdeSessionManager("org.kde.ksmserver", "/KSMServer",
         "org.kde.KSMServerInterface", QDBusConnection::sessionBus());
       response = kdeSessionManager.call("logout", 0, 2, 1);
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         k = true;
     }

     if(!g && !g_pwr1 && !g_pwr2 && !k){
       QDBusInterface powermanagement("org.freedesktop.Hal",
         "/org/freedesktop/Hal/devices/computer",
         "org.freedesktop.Hal.Device.SystemPowerManagement",
         QDBusConnection::systemBus());
       response = powermanagement.call("Reboot");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         hal = true;
     }

     if(!g && !g_pwr1 && !g_pwr2 && !k && !hal){
       QDBusInterface powermanagement("org.freedesktop.ConsoleKit",
         "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager",
         QDBusConnection::systemBus());
       response = powermanagement.call("Restart");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
         QProcess::startDetached("sudo shutdown -r now");
       }
     }
   #endif
}

void suspend(){
   #ifdef Q_OS_WIN32
     QProcess::startDetached("rundll32 powrprof.dll,SetSuspendState"); // Windows command to suspend immediately
   #else
     bool g_pwr1 = false;
     bool g_pwr2 = false;
     bool hal = false;
     bool upower = false;
     QDBusMessage response;

     if(lockMyScreen){
       bool lock_works = false;

       QDBusInterface screenlock("org.gnome.ScreenSaver",
         "/org/gnome/ScreenSaver", "org.gnome.ScreenSaver",
         QDBusConnection::systemBus());
       response = screenlock.call("Lock");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         lock_works = true;

       if(!lock_works){
         if(!QProcess::startDetached("gnome-screensaver-command -l")){
           if(verbose) oput << "W: gnome-screensaver-command -l didn't work"
                            << endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("qdbus org.freedesktop.ScreenSaver /ScreenSaver Lock")){
           if(verbose) oput << "W: qdbus org.freedesktop.ScreenSaver /ScreenSaver Lock didn't work"
                            << endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("dcop kdesktop KScreensaverIface lock")){
           if(verbose) oput << "W: dcop kdesktop KScreensaverIface lock didn't work"
                            << endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("xscreensaver-command -lock")){
           if(verbose) oput << "W: xscreensaver-command -lock didn't work"
                            << endl;
          }
	  else lock_works = true;
        }
     }

     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh suspend");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd suspend");
     if(!g_pwr1 && !g_pwr2 && verbose)
       oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
            << endl;

     if(!g_pwr1 && !g_pwr2){
       QDBusInterface powermanagement("org.freedesktop.Hal",
         "/org/freedesktop/Hal/devices/computer",
         "org.freedesktop.Hal.Device.SystemPowerManagement",
         QDBusConnection::systemBus());
       response = powermanagement.call("Suspend",0);
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         hal = true;
     }

     if(!hal && !g_pwr1 && !g_pwr2){
       QDBusInterface powermanagement("org.freedesktop.UPower",
         "/org/freedesktop/UPower",
         "org.freedesktop.UPower", QDBusConnection::systemBus());
       response = powermanagement.call("Suspend");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         upower = true;
     }

     if(!upower && !hal && !g_pwr1 && !g_pwr2){
       QDBusInterface powermanagement("org.freedesktop.DeviceKit.Power",
         "/org/freedesktop/DeviceKit/Power",
         "org.freedesktop.DeviceKit.Power", QDBusConnection::systemBus());
       response = powermanagement.call("Suspend");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
     }
   #endif
}

void hibernate(){
   #ifdef Q_OS_WIN32
     QProcess::startDetached("rundll32 powrprof.dll,SetSuspendState"); // Windows command to hibernate immediately
   #else
     bool g_pwr1 = false;
     bool g_pwr2 = false;
     bool hal = false;
     bool upower = false;
     QDBusMessage response;

     if(lockMyScreen){
       bool lock_works = false;

       QDBusInterface screenlock("org.gnome.ScreenSaver",
         "/org/gnome/ScreenSaver", "org.gnome.ScreenSaver",
         QDBusConnection::systemBus());
       response = screenlock.call("Lock");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         lock_works = true;

       if(!lock_works){
         if(!QProcess::startDetached("gnome-screensaver-command -l")){
           if(verbose) oput << "W: gnome-screensaver-command -l didn't work"
                            << endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("qdbus org.freedesktop.ScreenSaver /ScreenSaver Lock")){
           if(verbose) oput << "W: qdbus org.freedesktop.ScreenSaver /ScreenSaver Lock didn't work"
                            << endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("dcop kdesktop KScreensaverIface lock")){
           if(verbose) oput << "W: dcop kdesktop KScreensaverIface lock didn't work"
                            << endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("xscreensaver-command -lock")){
           if(verbose) oput << "W: xscreensaver-command -lock didn't work"
                            << endl;
          }
	  else lock_works = true;
        }
     }

     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh hibernate");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd hibernate");
     if(!g_pwr1 && !g_pwr2 && verbose)
       oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
            << endl;

     if(!g_pwr1 && !g_pwr2){
       QDBusInterface powermanagement("org.freedesktop.Hal",
         "/org/freedesktop/Hal/devices/computer",
         "org.freedesktop.Hal.Device.SystemPowerManagement",
         QDBusConnection::systemBus());
       response = powermanagement.call("Hibernate");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         hal = true;
     }

     if(!hal && !g_pwr1 && !g_pwr2){
       QDBusInterface powermanagement("org.freedesktop.UPower",
         "/org/freedesktop/UPower",
         "org.freedesktop.UPower", QDBusConnection::systemBus());
       response = powermanagement.call("Hibernate");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         upower = true;
     }

     if(!upower && !hal && !g_pwr1 && !g_pwr2){
       QDBusInterface powermanagement("org.freedesktop.DeviceKit.Power", "/org/freedesktop/DeviceKit/Power",
         "org.freedesktop.DeviceKit.Power", QDBusConnection::systemBus());
       response = powermanagement.call("Hibernate");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
     }
   #endif
}

}

#endif //POWER_H
