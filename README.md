# shutdown-qapps

## intro

This repository consists of 2 programms.  
qshutdown and qprogram-starter

## Instructions

For detailed instructions, please see the README files in the corresponding folders.  
* [qshutdown/README.md](qshutdown/README.md)
* [qprogram-starter/README.md](qprogram-starter/README.md)

### Install on Linux

To install from the repositories of Debian based systems like Ubuntu:  

* `sudo apt-get install qshutdown`
* `sudo apt-get install qprogram-starter`

There is a launchpad ppa repository as well, but be aware that the builds are more unstable.
For qshutdown:

1. `sudo apt-add-repository ppa:hakaishi/qshutdown`
2. `sudo apt-get update && sudo apt-get install qshutdown`

For qprogram-starter:

1. `sudo apt-add-repository ppa:hakaishi/qprogram-starter`
2. `sudo apt-get update && sudo apt-get install qprogram-starter`

### Windows

We provide Windows binaries in the release section of GitHub: [here](https://github.com/hakaishi/shutdown-qapps/releases)

## License

The Debian distribution is licensed under GPLv3.  
The Windows binaries include suspend_win.h which is licensed under BSD-2-clause.
Note that either of them includes Qt sources which are licensed under various licenses
depending on the modules used. See [here](https://doc.qt.io/archives/qt-5.15/licenses-used-in-qt.html) for details.
