/* qshutdown, a program to shutdown the shutdown/reboot/suspend/hibernate
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

/* INFO: For Windows hibernate has to be activated:
   Please note that this only works if the hardware supports it and
   enough RAM is available.
   - powercfg -a #prints aviable sleep states
   - powercfg -hibernate on
   - powercfg -hibernate off
*/

#ifndef POWER_H
#define POWER_H

#ifdef Q_OS_LINUX
  #include <QtDBus>
#endif

#include <QProcess>
#include <QTextStream>

//extern bool verbose;
//extern QString shell;

namespace Power{

bool verbose = true;

QTextStream oput(stdout);

bool lockMyScreen;
bool automatic = false;
bool login1 = false;
bool gnome = false;
bool kde = false;
bool hal_ = false;
bool consolekit = false;
bool sudo = false;
bool upower_ = false;
bool devicekit = false;
bool user = false;
QString myShutdown, myReboot, mySuspend, myHibernate;

void shutdown(){
 #ifdef Q_OS_LINUX
  QDBusMessage response;
  //variables for automatic mode
  bool g_pwr1 = false;
  bool g_pwr2 = false;

  QStringList args;
  args << "-c" << myShutdown;

  QDBusInterface freedesktopLogin1("org.freedesktop.login1",
    "/org/freedesktop/login1",
    "org.freedesktop.login1.Manager", QDBusConnection::systemBus());
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
   #if defined(Q_OS_WIN32)
     QProcess::startDetached("shutdown", QStringList() << "-s" << "-f" << "-t" << "00"); // Windows command to shutdown immediately
     }
    #elif defined(Q_OS_MACOS)
       QProcess::startDetached("/usr/bin/osascript",QStringList() << "-e" << "tell application \"System Events\" to shut down");
    }
   #else
     if(QProcess::startDetached("/usr/bin/systemctl", QStringList() << "poweroff"))
       return;
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh", QStringList() << "shutdown");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd", QStringList() << "shutdown");
     if(verbose && !g_pwr1 && !g_pwr2)
       oput << "W: gnome-power-cmd, gnome-power-cmd.sh and gnome-session-quit didn't work"
            << Qt::endl;
     else if(g_pwr1 || g_pwr2)
       return;

     response = freedesktopLogin1.call("PowerOff", true);
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = gnomeSessionManager.call("RequestShutdown");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = gnomeSessionManager.call("Shutdown");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = kdeSessionManager.call("logout", 0, 2, 2);
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopHal.call("Shutdown");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopConsoleKit.call("Stop");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     if(QProcess::startDetached("sudo", QStringList() << "shutdown" << "-P" << "now"))
       return;
     QProcess::startDetached("sudo", QStringList() << "shutdown" << "-h" << "-P" << "now");
  } //end of automatic
  else if(login1){
    response = freedesktopLogin1.call("PowerOff", true);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(gnome){
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh", QStringList() << "shutdown");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd", QStringList() << "shutdown");
     if(verbose && !g_pwr1 && !g_pwr2)
       oput << "W: gnome-power-cmd, gnome-power-cmd.sh and gnome-session-quit didn't work"
            << Qt::endl;
     if(g_pwr1 || g_pwr2)
       return;

     response = gnomeSessionManager.call("RequestShutdown");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = gnomeSessionManager.call("Shutdown");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
  }
  else if(kde){
    response = kdeSessionManager.call("logout", 0, 2, 2);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
      }
  }
  else if(hal_){
    response = freedesktopHal.call("Shutdown");
    if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
       }
  }
  else if(consolekit){
    response = freedesktopConsoleKit.call("Stop");
    if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
    }
  }
  else if(sudo){
     if(QProcess::startDetached("sudo", QStringList() << "/usr/bin/systemctl" << "poweroff"))
       return;
     if(QProcess::startDetached("sudo", QStringList() << "shutdown" << "-P" << "now"))
       return;
     QProcess::startDetached("sudo", QStringList() << "shutdown" << "-h" << "-P" << "now");
  }
  //else if(user)
  //  if(!shell.isEmpty())
  //    QProcess::startDetached(shell, args);

  //resetting variables
  automatic = false;
  login1 = false;
  gnome = false;
  kde = false;
  hal_ = false;
  consolekit = false;
  sudo = false;
  user = false;
   #endif
}

void reboot(){
 #ifdef Q_OS_LINUX
  QDBusMessage response;
  bool g_pwr1 = false;
  bool g_pwr2 = false;

  QStringList args;
  args << "-c" << myReboot;

  QDBusInterface freedesktopLogin1("org.freedesktop.login1",
    "/org/freedesktop/login1",
    "org.freedesktop.login1.Manager", QDBusConnection::systemBus());
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
   #if defined(Q_OS_WIN32)
     QProcess::startDetached("shutdown", QStringList() << "-r" << "-f" << "-t" << "00"); // Windows command to reboot immediately
}
   #elif defined(Q_OS_MACOS)
      QProcess::startDetached("/usr/bin/osascript",QStringList() << "-e" << "tell application \"System Events\" to restart");
}

   #else
     if(QProcess::startDetached("/usr/bin/systemctl", QStringList() << "reboot"))
       return;
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh", QStringList() << "reboot");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd", QStringList() << "reboot");
     if(verbose && !g_pwr1 && !g_pwr2)
       oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
            << Qt::endl;
     else if(g_pwr1 || g_pwr2)
       return;

     response = freedesktopLogin1.call("Reboot", true);
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = gnomeSessionManager.call("RequestReboot");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     QDBusInterface kdeSessionManager("org.kde.ksmserver", "/KSMServer",
       "org.kde.KSMServerInterface", QDBusConnection::sessionBus());
     response = kdeSessionManager.call("logout", 0, 2, 1);
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopHal.call("Reboot");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopConsoleKit.call("Restart");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     QProcess::startDetached("sudo", QStringList() << "shutdown" << "-r" << "now");
  } //end of automatic
  else if(login1){
    response = freedesktopLogin1.call("Reboot", true);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(gnome){
    g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh", QStringList() << "reboot");
    g_pwr2 = QProcess::startDetached("gnome-power-cmd", QStringList() << "reboot");
    if(verbose && !g_pwr1 && !g_pwr2)
      oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
           << Qt::endl;
    if(g_pwr1 || g_pwr2)
      return;

    response = gnomeSessionManager.call("RequestReboot");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(kde){
    response = kdeSessionManager.call("logout", 0, 2, 1);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(hal_){
    response = freedesktopHal.call("Reboot");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(consolekit){
    response = freedesktopConsoleKit.call("Restart");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(sudo){
    if(QProcess::startDetached("sudo", QStringList() << "/usr/bin/systemctl" << "reboot"))
      return;
    QProcess::startDetached("sudo", QStringList() << "shutdown" << "-r" << "now");
  }
  //else if(user)
  //  if(!shell.isEmpty())
  //    QProcess::startDetached(shell, args);

  //resetting variables
  automatic = false;
  login1 = false;
  gnome = false;
  kde = false;
  hal_ = false;
  consolekit = false;
  sudo = false;
  user = false;
   #endif
}

void suspend(){
 #ifdef Q_OS_LINUX
  QDBusMessage response;
  bool g_pwr1 = false;
  bool g_pwr2 = false;

  QStringList args;
  args << "-c" << mySuspend;

  QDBusInterface freedesktopLogin1("org.freedesktop.login1",
    "/org/freedesktop/login1",
    "org.freedesktop.login1.Manager", QDBusConnection::systemBus());
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
                << response.errorMessage() << Qt::endl;
       }
       else
         lock_works = true;

       if(!lock_works){
         if(!QProcess::startDetached("gnome-screensaver-command", QStringList() << "-l")){
           if(verbose) oput << "W: gnome-screensaver-command -l didn't work"
                            << Qt::endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("qdbus", QStringList() << "org.freedesktop.ScreenSaver" << "/ScreenSaver Lock")){
           if(verbose) oput << "W: qdbus org.freedesktop.ScreenSaver /ScreenSaver Lock didn't work"
                            << Qt::endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("dcop", QStringList() << "kdesktop" << "KScreensaverIface" << "lock")){
           if(verbose) oput << "W: dcop kdesktop KScreensaverIface lock didn't work"
                            << Qt::endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("xscreensaver-command", QStringList() << "-lock")){
           if(verbose) oput << "W: xscreensaver-command -lock didn't work"
                            << Qt::endl;
          }
	  else lock_works = true;
        }
     }
 #endif

  if(automatic){
   #if defined(Q_OS_WIN32)
     QProcess::startDetached("powercfg", QStringList() << "-hibernate" << "off"); // enable suspend
     QProcess::startDetached("rundll32", QStringList() << "powrprof.dll,SetSuspendState");
     }

    #elif defined(Q_OS_MACOS)
      QProcess::startDetached("/usr/bin/osascript",QStringList() << "-e" << "tell application \"System Events\" to sleep");
    }
   #else
     if(QProcess::startDetached("/usr/bin/systemctl", QStringList() << "suspend"))
       return;

     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh", QStringList() << "suspend");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd", QStringList() << "suspend");
     if(!g_pwr1 && !g_pwr2 && verbose)
       oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
            << Qt::endl;
     else if(g_pwr1 || g_pwr2)
       return;

     response = freedesktopLogin1.call("Suspend", true);
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopHal.call("Suspend",0);
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopUPower.call("Suspend");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopDeviceKit.call("Suspend");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
  } //end of automatic
  else if(login1){
    response = freedesktopLogin1.call("Suspend", true);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(gnome){
    g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh", QStringList() << "suspend");
    g_pwr2 = QProcess::startDetached("gnome-power-cmd", QStringList() << "suspend");
    if(!g_pwr1 && !g_pwr2 && verbose)
      oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
           << Qt::endl;
  }
  else if(hal_){
    response = freedesktopHal.call("Suspend",0);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(upower_){
    response = freedesktopUPower.call("Suspend");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(devicekit){
    response = freedesktopDeviceKit.call("Suspend");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  //else if(user)
  //  if(!shell.isEmpty())
  //    QProcess::startDetached(shell, args);


  //resetting variables
  automatic = false;
  login1 = false;
  gnome = false;
  hal_ = false;
  upower_ = false;
  devicekit = false;
  user = false;
   #endif
}

void hibernate(){
 #ifdef Q_OS_LINUX
  QDBusMessage response;
  bool g_pwr1 = false;
  bool g_pwr2 = false;

  QStringList args;
  args << "-c" << myHibernate;

  QDBusInterface freedesktopLogin1("org.freedesktop.login1",
    "/org/freedesktop/login1",
    "org.freedesktop.login1.Manager", QDBusConnection::systemBus());
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
                << response.errorMessage() << Qt::endl;
       }
       else
         lock_works = true;

       if(!lock_works){
         if(!QProcess::startDetached("gnome-screensaver-command", QStringList() << "-l")){
           if(verbose) oput << "W: gnome-screensaver-command -l didn't work"
                            << Qt::endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("qdbus", QStringList() << "org.freedesktop.ScreenSaver" << "/ScreenSaver" << "Lock")){
           if(verbose) oput << "W: qdbus org.freedesktop.ScreenSaver /ScreenSaver Lock didn't work"
                            << Qt::endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("dcop", QStringList() << "kdesktop" << "KScreensaverIface" << "lock")){
           if(verbose) oput << "W: dcop kdesktop KScreensaverIface lock didn't work"
                            << Qt::endl;
          }
	  else lock_works = true;
        }
       if(!lock_works){
         if(!QProcess::startDetached("xscreensaver-command", QStringList() << "-lock")){
           if(verbose) oput << "W: xscreensaver-command -lock didn't work"
                            << Qt::endl;
          }
	  else lock_works = true;
        }
     }
 #endif

  if(automatic){
   #if defined (Q_OS_WIN32)
     QProcess::startDetached("powercfg", QStringList() << "-hibernate" << "on"); // enable hibernate
     QProcess::startDetached("rundll32", QStringList() << "powrprof.dll,SetSuspendState");
     }
    #elif defined(Q_OS_MACOS)
       QProcess::startDetached("/usr/bin/osascript",QStringList() << "-e" << "tell application \"System Events\" to sleep");
    }
   #else
     if(QProcess::startDetached("/usr/bin/systemctl", QStringList() << "hibernate"))
       return;
     g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh", QStringList() << "hibernate");
     g_pwr2 = QProcess::startDetached("gnome-power-cmd", QStringList() << "hibernate");
     if(!g_pwr1 && !g_pwr2 && verbose)
       oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
            << Qt::endl;
     else if (g_pwr1 || g_pwr2)
       return;

     response = freedesktopLogin1.call("Hibernate", true);
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopHal.call("Hibernate");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopUPower.call("Hibernate");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
     else return;

     response = freedesktopDeviceKit.call("Hibernate");
     if(response.type() == QDBusMessage::ErrorMessage){
       if(verbose)
         oput << "W: " << response.errorName() << ": "
              << response.errorMessage() << Qt::endl;
     }
  } // end of automatic
  else if(login1){
    response = freedesktopLogin1.call("Hibernate", true);
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(gnome){
    g_pwr1 = QProcess::startDetached("gnome-power-cmd.sh", QStringList() << "hibernate");
    g_pwr2 = QProcess::startDetached("gnome-power-cmd", QStringList() << "hibernate");
    if(!g_pwr1 && !g_pwr2 && verbose)
      oput << "W: gnome-power-cmd and gnome-power-cmd.sh didn't work"
           << Qt::endl;
  }
  else if(hal_){
    response = freedesktopHal.call("Hibernate");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(upower_){
    response = freedesktopUPower.call("Hibernate");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  else if(devicekit){
    response = freedesktopDeviceKit.call("Hibernate");
    if(response.type() == QDBusMessage::ErrorMessage){
      if(verbose)
        oput << "W: " << response.errorName() << ": "
             << response.errorMessage() << Qt::endl;
    }
  }
  //else if(user)
  //  if(!shell.isEmpty())
  //    QProcess::startDetached(shell, args);

  //resetting variables
  automatic = false;
  login1 = false;
  gnome = false;
  hal_ = false;
  upower_ = false;
  devicekit = false;
  user = false;
   #endif
}

}

#endif //POWER_H
