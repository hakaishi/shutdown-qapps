<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="uk">
<context>
    <name>Gui</name>
    <message>
        <source>HH:mm:ss</source>
        <translation>HH:mm:ss</translation>
    </message>
    <message>
        <source>dddd dd.MM.yyyy</source>
        <translation>dddd, dd.MM.yyyy</translation>
    </message>
    <message>
        <source>Sho&amp;w Logs</source>
        <translation>&amp;Показати журнал</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation>З&amp;авершити роботу</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>П&amp;ідказки</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Завершує роботу qprogram-starter, щойно буде виконано останню команду</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>Ви&amp;йти після останньої команди</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>&amp;Журнал</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation>Завершити роботу комп’ютера, щойно буде виконано всі команди</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>Дані відновлюватимуться після кожного запуску qprogram-starter</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>&amp;Запустити</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>П&amp;ерервати</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Вибрати...</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Зберегти &amp;дані у текстових редакторах</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Запустити команду у вказаний час вказаної дати</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>Да&amp;та і час запуску:</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Виберіть програму</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation>Перше текстове поле порожнє!</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Відомості</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Роботу процесів перервано</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;роботу процесу 1 завершено!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;роботу процесів 1 і 2 завершено!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Помилка</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;Не вдалося запустити!&lt;/b&gt;&lt;br/&gt;Немає такої програми або команди.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Процес 1 аварійно завершив роботу!&lt;/b&gt;&lt;br/&gt;Це може бути спричинено некоректними параметрами або аргументами.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Процес 2 аварійно завершив роботу!&lt;/b&gt;&lt;br/&gt;Це може бути спричинено некоректними параметрами або аргументами.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Невідома помилка!&lt;/b&gt;&lt;br/&gt;Це може бути спричинено некоректними параметрами або аргументами.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation>«%1»: не вдалося запустити команду! Немає такої програми або команди.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation>Команду у другому вікні редагування тексту (якщо таке показано) буде виконано після команди у першому. Панелі повідомлень буде закрито автоматично за 10 секунд.&lt;br/&gt;Для запуску програми просто вкажіть, наприклад, «firefox» або «firefox www.google.com», а потім натисніть кнопку «Запустити». Команди можна об’єднувати у кортежі за допомогою «&amp;&amp;» тощо. &lt;br/&gt;&lt;br/&gt;Якщо процес «завершує» роботу, хоча її робота все ще продовжується, спробуйте скористатися параметром --nofork (тобто kopete --nofork). Зауважте, що таке трапляється і для деяких інших програм, зокрема gedit, firefox або gnome-terminal, якщо їх вже запущено.&lt;br/&gt;&lt;br/&gt;Якщо ви хочете запустити команду або програму за допомогою sudo, будь ласка, скористайтеся, наприклад, gksu(do) або kdesu(do).&lt;br/&gt;&lt;br/&gt;Приклади для make:&lt;br/&gt;&amp;nbsp;make -C /шлях/до/проекту&lt;br/&gt;&amp;nbsp;make clean -C /шлях/до/проекту&lt;br/&gt;&lt;br/&gt;Про помилки:&lt;br/&gt;оскільки майже всі програми повідомляють про помилки різними кодами, неможливо визначити причину помилки. Отже просто запишіть виведені дані до журналу і ознайомтеся з повідомленням про помилку. Файли виведених даних можна знайти у &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;Якщо вимикання комп’ютера не працює, значить використовується «sudo shutdown -P now». Для виконання цієї команди потрібні права доступу адміністратора (root). Ви можете усунути помилку так:&lt;br/&gt;&lt;br/&gt;Введіть таку команду у терміналі:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; і додайте такий рядок:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt;, де * замінює ім’я користувача або %groupname.&lt;br/&gt;&lt;br/&gt;Файл налаштувань зберігається у &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
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
