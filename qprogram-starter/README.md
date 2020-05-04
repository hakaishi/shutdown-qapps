# qprogram-starter

## INSTALL
Dependencies: qtbase5-dev, qttools5-dev-tools, build-essential


If you want to install from source, open a terminal and change into this folder.
To install type:

`qmake`
`sudo make install distclean`

## UNINSTALL
To uninstall type:

`qmake`     (if the Makefile has been removed)
`sudo make deinstall`

(please note that the users qprogram-starter settings file and
 the log files won't be removed)


## KNOWN ISSUE:

For most systems using the Gnome Shell a certain DBus method has been removed,
thus a shutdown dialog will be likely to appear if qshutdown's methods have
been set to automatic or to Gnome session. If you do not want this
shutdown dialog to appear, please use ConsoleKit or something else.
