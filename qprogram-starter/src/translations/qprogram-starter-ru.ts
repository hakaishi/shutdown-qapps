<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="ru">
<context>
    <name>Gui</name>
    <message>
        <source>HH:mm:ss</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>dddd dd.MM.yyyy</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Sho&amp;w Logs</source>
        <translation>Показать &amp;журнал</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation>&amp;Выключить</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>&amp;Подсказки</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Выйти из qprogram-starter после выполнения последней команды</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>В&amp;ыйти вместе с последней командой</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>П&amp;ротоколирование</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation>Выключить компьютер после выполнения всех команд</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>Содержимое будет востанавливаться после каждого запуска qprogram-starter</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>&amp;Запуск</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>&amp;Отмена</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Обзор…</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Сохранить &amp;содержимое редакторов текста</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Запустить команду в заданный день и время</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>&amp;Дата и время:</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Выберите программу</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation>Первое тесктовое поле пустое!</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Информация</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Процесс прерван</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;процесс 1 выполнен!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;процессы 1 и 2 выполнены!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Ошибка</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;Запуск невозможен!&lt;/b&gt;&lt;br/&gt;Нет такой команды или программы.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;процесс 1 аварийно завершён!&lt;/b&gt;&lt;br/&gt;Эта ситуация может возникнуть из-за неправильной опции или параметра.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;процесс 2 аварийно завершён!&lt;/b&gt;&lt;br/&gt;Эта ситуация может возникнуть из-за неправильной опции или параметра.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Неизвестная ошибка!&lt;/b&gt;&lt;br/&gt;Эта ситуация может возникнуть из-за неправильной опции или параметра.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation>&quot;%1&quot;: Запуск невозможен! Нет такой команды или программы.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation>Если во втором редакторе задана команда, то она будет выполнена после первой команды. Окна с сообщениями автоматически закроются через 10 секунд.&lt;br/&gt;Для того, чтобы запустить программу, просто напечатайте, например, &quot;firefox&quot; или &quot;firefox www.google.com&quot;, затем нажмите кнопку &quot;Запуск&quot;. Команды могут объединяться с помощью символов &quot;&amp;&amp;&quot; и т.д.&lt;br/&gt;&lt;br/&gt;Если процесс &quot;закончился&quot;, несмотря на то, что он всё ещё выполняется, попробуйте использовать параметр &quot;--nofork&quot; (например, kopete --nofork). Обратите внимание, что это затронет также некоторые программы, например gedit, firefox или gnome-terminal, если они уже выполняются.&lt;br/&gt;&lt;br/&gt;Если вы хотите запустить программу или команду с помощью sudo, используйте gksu(do) или kdesu(do).&lt;br/&gt;&lt;br/&gt;Примеры использования команды make:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;Об ошибках:&lt;br/&gt;Из-за того, что разные программы выдают разные сообщения об ошибках, иногда невозможно сказать, что именно произошло в данном случае. При возникновении ошибок, включите протоколирование и просмотрите журнал. Файлы журналов могут быть найдены в каталоге &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;Если выключение компьютера не работает, это значит, что используется команда &quot;sudo shutdown -P now&quot;. Для её выполнения требуются права администратора. Вариант решения проблемы:&lt;br/&gt;&lt;br/&gt;Введите в терминале:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; и добавьте следующую строку:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; где * представляет собой имя пользователя или группы.&lt;br/&gt;&lt;br/&gt;Файл конфигурации расположен в каталоге &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
    </message>
    <message>
        <source>MainWindow</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;!DOCTYPE HTML PUBLIC &quot;-//W3C//DTD HTML 4.0//EN&quot; &quot;http://www.w3.org/TR/REC-html40/strict.dtd&quot;&gt;
&lt;html&gt;&lt;head&gt;&lt;meta name=&quot;qrichtext&quot; content=&quot;1&quot; /&gt;&lt;style type=&quot;text/css&quot;&gt;
p, li { white-space: pre-wrap; }
&lt;/style&gt;&lt;/head&gt;&lt;body style=&quot; font-family:&apos;Sans&apos;; font-size:10pt; font-weight:400; font-style:normal;&quot;&gt;
&lt;p style=&quot; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;&quot;&gt;Log &lt;span style=&quot; font-weight:600;&quot;&gt;all&lt;/span&gt; output&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Quit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&amp;Configure</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Version </source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Preferences</name>
    <message>
        <source>Preferences</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>automatic</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Gnome session</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>KDE session</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Shutdown Method:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>The File &quot;%1&quot; is not writable!
Maybe you just don&apos;t have the permissions to do so.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Welcome to qprogram-starter!
If you want qprogram-starter to automatically shutdown the system and you are using the Gnome Shell, then you are likely to get a shutdown dialog from there. If you want a direct shutdown, then please consider going into the preferences and setting the shutdown method to ConsoleKit or something else.

Please feel free to visit https://launchpad.net/~hakaishi to report bugs or for anyting concerning translations.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
