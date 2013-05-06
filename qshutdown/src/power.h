/* qshutdown, a program to shutdown the shutdown/reboot/suspend/hibernate
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
QString shell = QProcess::systemEnvironment().filter("SHELL").first().remove("SHELL=");

bool lockMyScreen;
bool automatic = false;
bool gnome = false;
bool kde = false;
bool hal_ = false;
bool consolekit = false;
bool sudo = false;
bool upower_ = false;
bool devicekit = false;
bool user = false;
QString myShutdown, myReboot, mySuspend, myHibernate;
#ifndef Q_OS_WIN32
QDBusMessage response;
#endif

void shutdown(){
 #ifndef Q_OS_WIN32
  //variables for automatic mode
  bool g = false; //gnome
  bool k = false; //kde
  bool g_pwr1 = false;
  bool g_pwr2 = false;
  bool hal = false;

  QStringList args;
  args << "-c" << myShutdown;

  QDBusInterface gnomeSessionManager("org.gnome.SessionManager",
    "/org/gnome/SessionManager", "org.gnome.SessionManager",
    QDBusConnection::sessionBus());
  QDBusInterface kdeSessionManager("org.kde.ksmserver", "/KSMServer",
    "org.kde.KSMServerInterface", QDBusConnection::sessionBus());
  QDBusInterface freedesktopHal("org.freedesktop.Hal",
    "/org/freedesktop/Hal/devices/computer",
    "org.freedesktop.Hal.Device.SystemPowerManagement",
    QDBusConnection::systemBus());
  QDBusInterface freedesktopConsoleKit("org.freedesktop.ConsoleKit",
    "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager",
    QDBusConnection::systemBus());
 #endif

  if(automatic){
   #ifdef Q_OS_WIN32
     QProcess::startDetached("shutdown -s -f -t 00"); // Windows command to shutdown immediately
     }
   #else
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh shutdown");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd shutdown");
     if(verbose && !g_pwr1 && !g_pwr2)
       oput << "W: gnome-power-cmd, gnome-power-cmd.sh and gnome-session-quit didn't work"
            << endl;
     if(!g_pwr1 && !g_pwr2){
       response = gnomeSessionManager.call("RequestShutdown");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else g = true;
       if(!g){
         response = gnomeSessionManager.call("Shutdown");
         if(response.type() == QDBusMessage::ErrorMessage){
           if(verbose)
             oput << "W: " << response.errorName() << ": "
                  << response.errorMessage() << endl;
         }
         else g = true;
       }
     }
     else g = true;

     if(!g && !g_pwr1 && !g_pwr2){
       response = kdeSessionManager.call("logout", 0, 2, 2);
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else k = true;
     }

     if(!g && !g_pwr1 && !g_pwr2 && !k){
       response = freedesktopHal.call("Shutdown");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else hal = true;
     }

     if(!g && !g_pwr1 && !g_pwr2 && !k && !hal){
       response = freedesktopConsoleKit.call("Stop");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
         QProcess::startDetached("sudo shutdown -P now");
       }
     }
  }
  if(gnome){
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh shutdown");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd shutdown");
     if(verbose && !g_pwr1 && !g_pwr2)
       oput << "W: gnome-power-cmd, gnome-power-cmd.sh and gnome-session-quit didn't work"
            << endl;
     if(!g_pwr1 && !g_pwr2){
       response = gnomeSessionManager.call("RequestShutdown");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else g = true;
       if(!g){
         response = gnomeSessionManager.call("Shutdown");
         if(response.type() == QDBusMessage::ErrorMessage){
           if(verbose)
             oput << "W: " << response.errorName() << ": "
                  << response.errorMessage() << endl;
         }
       }
     }
  }
  if(kde){
    response = kdeSessionManager.call("logout", 0, 2, 2);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
      }
  }
  if(hal_){
    response = freedesktopHal.call("Shutdown");
    if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << endl;
       }
  }
  if(consolekit){
    response = freedesktopConsoleKit.call("Stop");
    if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << endl;
    }
  }
  if(sudo)
    QProcess::startDetached("sudo shutdown -P now");
  if(user)
    QProcess::startDetached(shell, args);

  //resetting variables
  automatic = false;
  gnome = false;
  kde = false;
  hal_ = false;
  consolekit = false;
  sudo = false;
  user = false;
   #endif
}

void reboot(){
 #ifndef Q_OS_WIN32
  bool g = false; //gnome
  bool k = false; //kde
  bool g_pwr1 = false;
  bool g_pwr2 = false;
  bool hal = false;

  QStringList args;
  args << "-c" << myReboot;

  QDBusInterface gnomeSessionManager("org.gnome.SessionManager",
    "/org/gnome/SessionManager", "org.gnome.SessionManager",
    QDBusConnection::sessionBus());
  QDBusInterface kdeSessionManager("org.kde.ksmserver", "/KSMServer",
    "org.kde.KSMServerInterface", QDBusConnection::sessionBus());
  QDBusInterface freedesktopHal("org.freedesktop.Hal",
    "/org/freedesktop/Hal/devices/computer",
    "org.freedesktop.Hal.Device.SystemPowerManagement",
    QDBusConnection::systemBus());
  QDBusInterface freedesktopConsoleKit("org.freedesktop.ConsoleKit",
    "/org/freedesktop/ConsoleKit/Manager", "org.freedesktop.ConsoleKit.Manager",
    QDBusConnection::systemBus());
 #endif

  if(automatic){
   #ifdef Q_OS_WIN32
     QProcess::startDetached("shutdown -r -f -t 00"); // Windows command to reboot immediately
     }
   #else
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh reboot");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd reboot");
     if(verbose && !g_pwr1 && !g_pwr2)
       oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
            << endl;
     if(!g_pwr1 && !g_pwr2){
       response = gnomeSessionManager.call("RequestReboot");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else g = true;
     }
     else g = true;

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
       response = freedesktopHal.call("Reboot");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         hal = true;
     }

     if(!g && !g_pwr1 && !g_pwr2 && !k && !hal){
       response = freedesktopConsoleKit.call("Restart");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
         QProcess::startDetached("sudo shutdown -r now");
       }
     }
  }
  if(gnome){
    g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh reboot");
    g_pwr2 = QProcess::startDetached("gnome-power-cmd reboot");
    if(verbose && !g_pwr1 && !g_pwr2)
      oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
           << endl;
    if(!g_pwr1 && !g_pwr2){
      response = gnomeSessionManager.call("RequestReboot");
      if(response.type() == QDBusMessage::ErrorMessage){
        if(verbose)
          oput << "W: " << response.errorName() << ": "
               << response.errorMessage() << endl;
      }
    }
  }
  if(kde){
    response = kdeSessionManager.call("logout", 0, 2, 1);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
    }
  }
  if(hal_){
    response = freedesktopHal.call("Reboot");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
    }
  }
  if(consolekit){
    response = freedesktopConsoleKit.call("Restart");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
    }
  }
  if(sudo)
    QProcess::startDetached("sudo shutdown -r now");
  if(user)
    QProcess::startDetached(shell, args);

  //resetting variables
  automatic = false;
  gnome = false;
  kde = false;
  hal_ = false;
  consolekit = false;
  sudo = false;
  user = false;
   #endif
}

void suspend(){
 #ifndef Q_OS_WIN32
  bool g_pwr1 = false;
  bool g_pwr2 = false;
  bool hal = false;
  bool upower = false;

  QStringList args;
  args << "-c" << mySuspend;

  QDBusInterface freedesktopHal("org.freedesktop.Hal",
    "/org/freedesktop/Hal/devices/computer",
    "org.freedesktop.Hal.Device.SystemPowerManagement",
    QDBusConnection::systemBus());
  QDBusInterface freedesktopUPower("org.freedesktop.UPower",
    "/org/freedesktop/UPower",
    "org.freedesktop.UPower", QDBusConnection::systemBus());
  QDBusInterface freedesktopDeviceKit("org.freedesktop.DeviceKit.Power",
    "/org/freedesktop/DeviceKit/Power",
    "org.freedesktop.DeviceKit.Power", QDBusConnection::systemBus());

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
 #endif

  if(automatic){
   #ifdef Q_OS_WIN32
     QProcess::startDetached("rundll32 powrprof.dll,SetSuspendState"); // Windows command to suspend immediately
     }
   #else
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh suspend");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd suspend");
     if(!g_pwr1 && !g_pwr2 && verbose)
       oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
            << endl;

     if(!g_pwr1 && !g_pwr2){
       response = freedesktopHal.call("Suspend",0);
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         hal = true;
     }

     if(!hal && !g_pwr1 && !g_pwr2){
       response = freedesktopUPower.call("Suspend");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         upower = true;
     }

     if(!upower && !hal && !g_pwr1 && !g_pwr2){
       response = freedesktopDeviceKit.call("Suspend");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
     }
  }
  if(gnome){
    g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh suspend");
    g_pwr2 = QProcess::startDetached("gnome-power-cmd suspend");
    if(!g_pwr1 && !g_pwr2 && verbose)
      oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
           << endl;
  }
  if(hal_){
    response = freedesktopHal.call("Suspend",0);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
    }
  }
  if(upower_){
    response = freedesktopUPower.call("Suspend");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
    }
  }
  if(devicekit){
    if(!upower && !hal && !g_pwr1 && !g_pwr2){
      response = freedesktopDeviceKit.call("Suspend");
      if(response.type() == QDBusMessage::ErrorMessage){
        if(verbose)
          oput << "W: " << response.errorName() << ": "
               << response.errorMessage() << endl;
      }
    }
  }
  if(user)
    QProcess::startDetached(shell, args);

  //resetting variables
  automatic = false;
  gnome = false;
  hal_ = false;
  upower_ = false;
  devicekit = false;
  user = false;
   #endif
}

void hibernate(){
 #ifndef Q_OS_WIN32
  bool g_pwr1 = false;
  bool g_pwr2 = false;
  bool hal = false;
  bool upower = false;

  QStringList args;
  args << "-c" << myHibernate;

  QDBusInterface freedesktopHal("org.freedesktop.Hal",
    "/org/freedesktop/Hal/devices/computer",
    "org.freedesktop.Hal.Device.SystemPowerManagement",
    QDBusConnection::systemBus());
  QDBusInterface freedesktopUPower("org.freedesktop.UPower",
    "/org/freedesktop/UPower",
    "org.freedesktop.UPower", QDBusConnection::systemBus());
  QDBusInterface freedesktopDeviceKit("org.freedesktop.DeviceKit.Power",
    "/org/freedesktop/DeviceKit/Power",
    "org.freedesktop.DeviceKit.Power", QDBusConnection::systemBus());

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
 #endif

  if(automatic){
   #ifdef Q_OS_WIN32
     QProcess::startDetached("rundll32 powrprof.dll,SetSuspendState"); // Windows command to hibernate immediately
     }
   #else
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh hibernate");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd hibernate");
     if(!g_pwr1 && !g_pwr2 && verbose)
       oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
            << endl;

     if(!g_pwr1 && !g_pwr2){
       response = freedesktopHal.call("Hibernate");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         hal = true;
     }

     if(!hal && !g_pwr1 && !g_pwr2){
       response = freedesktopUPower.call("Hibernate");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
       else
         upower = true;
     }

     if(!upower && !hal && !g_pwr1 && !g_pwr2){
       response = freedesktopDeviceKit.call("Hibernate");
       if(response.type() == QDBusMessage::ErrorMessage){
         if(verbose)
           oput << "W: " << response.errorName() << ": "
                << response.errorMessage() << endl;
       }
     }
  }
  if(gnome){
    g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh hibernate");
    g_pwr2 = QProcess::startDetached("gnome-power-cmd hibernate");
    if(!g_pwr1 && !g_pwr2 && verbose)
      oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
           << endl;
  }
  if(hal_){
    response = freedesktopHal.call("Hibernate");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
    }
  }
  if(upower_){
    response = freedesktopUPower.call("Hibernate");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
    }
  }
  if(devicekit){
    response = freedesktopDeviceKit.call("Hibernate");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << endl;
    }
  }
  if(user)
    QProcess::startDetached(shell, args);

  //resetting variables
  automatic = false;
  gnome = false;
  hal_ = false;
  upower_ = false;
  devicekit = false;
  user = false;
   #endif
}

}

#endif //POWER_H
