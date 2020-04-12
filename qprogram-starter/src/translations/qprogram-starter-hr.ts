<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="hr">
<context>
    <name>Gui</name>
    <message>
        <source>HH:mm:ss</source>
        <translation>SS:mm:ss</translation>
    </message>
    <message>
        <source>dddd dd.MM.yyyy</source>
        <translation>dddd dd.MM.gggg</translation>
    </message>
    <message>
        <source>Sho&amp;w Logs</source>
        <translation>Prikaž&amp;i Dnevnike</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation type="vanished">I&amp;sključi</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>&amp;Savjeti</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Prekida qprogram-starter kad završi provođenje zadnje naredbe</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>&amp;Prekida sa zanjom naredbom</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>&amp;Prijavljivanje</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation type="vanished">Isključuje računalo nakon što završi provođenje svih naredbi</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>Sadržaj će biti vraćen na svakom početku programa qprogram-starter</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>&amp;Start</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>&amp;Prekid</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Pregled...</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Spremi tekstualne editore i sadržaje</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Pokrenite naredbe na ovaj datum i u ovo vrijeme</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>N&amp;a datum i vrijeme:</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Odaberite program</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation type="vanished">Prva izmjena teksta je prazna!</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Informacija</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Prekinuti su procesi</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation type="vanished">&lt;b&gt;proces 1 je dovršen!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation type="vanished">&lt;b&gt;proces 1 i 2 su dovršeni!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Greška</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;Neuspjelo pokretanje!&lt;/b&gt;&lt;br/&gt;Nema takvog programa ili naredbe.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation type="vanished">&lt;b&gt;proces 1 se srušio!&lt;/b&gt;&lt;br/&gt;To bi moglo biti uzrokovano nevažećim parametrima ili opcijama.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation type="vanished">&lt;b&gt;proces 2 se srušio!&lt;/b&gt;&lt;br/&gt;To bi moglo biti uzrokovano nevažećim parametrima ili opcijama.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Nepoznata greška!&lt;/b&gt;&lt;br/&gt;To bi moglo biti uzrokovano nevažećim parametrima ili opcijama.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation type="vanished">&quot;%1&quot;: Neuspjelo pokretanje! Nema takvog programa ili naredbe.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation type="vanished">Naredba u drugom uređivaču teksta (postoji li) će se izvršiti nakon izvršavanja u prvom. Okviri poruka će se zatvoriti nakon 10 sekundi.&lt;br/&gt;Za pokretanje programa samo upišite tj. &quot;firefox&quot; ili &quot;firefox www.google.com&quot;, a zatim kliknite na Start. Naredbe i sl. mogu biti povezani s &quot;&amp;&amp;&quot; itd. &lt;br/&gt;&lt;br/&gt;Ako je proces &quot;završio&quot;, iako je još uvijek radi, onda pokušajte sa --nofork ocijom (tj. kopete --nofork). Imajte na umu da se ovo također događa sa nekim programima kao što su gedit, Firefox ili gnome-terminal, ako su već pokrenuti.&lt;br/&gt;&lt;br/&gt;Kada želite pokrenuti program ili naredbu sa sudo, molimo koristite na primjer gksu(do) ili kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;O Greškama:&lt;br/&gt;Budući da gotovo svaki program daje drugačiji kod pogreške, je nemoguće reći što se je dogodilo. Dakle, samo zabilježite izlazni podatak i pogledajte o kakvoj se grešci radi. Izlazne datoteke se mogu naći u &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;Ako isključivanja neće raditi, to znači da se koristi &quot;sudo shutdown-P now&quot;. Za ovo ćete trebati root ovlasti. Možete napraviti ovo:&lt;br/&gt;&lt;br/&gt;U terminalu utipkajte sljedeće:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; i dodajte ovu liniju:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; gdje * zamjenjuje korisničko ime ili %groupname.&lt;br/&gt;&lt;br/&gt;Konfiguracijsku datoteku možete pronaći u &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Datoteka</translation>
    </message>
    <message>
        <source>&amp;Settings</source>
        <translation>&amp;Postavke</translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation>&amp;Pomoć</translation>
    </message>
    <message>
        <source>&amp;Quit</source>
        <translation>&amp;Prestanak</translation>
    </message>
    <message>
        <source>&amp;Configure</source>
        <translation>&amp;Podešavanje</translation>
    </message>
    <message>
        <source>Version </source>
        <translation>Inačica </translation>
    </message>
    <message>
        <source>Ctrl+Q</source>
        <translation>Ctrl+Q</translation>
    </message>
    <message>
        <source>Ctrl+P</source>
        <translation>Ctrl+P</translation>
    </message>
    <message>
        <source>Ctrl+H</source>
        <translation>Ctrl+H</translation>
    </message>
    <message>
        <source>Choose an action</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Shutdown</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Reboot</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Suspend</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Hibernate</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>History</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Protokoll</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Info</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;b&gt;General:&lt;/b&gt;&lt;br/&gt;Each line in the text editor will be executed as one seperate process. Put a backslash at the end of the line for a multiline command.&lt;br/&gt;&lt;br/&gt; The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;&lt;b&gt;Files:&lt;/b&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;%2&lt;/i&gt;.&lt;br/&gt;The log files can be found at &lt;i&gt;%1&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;&lt;b&gt;make examples:&lt;/b&gt;&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;&lt;b&gt;About Errors:&lt;/b&gt;&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;%1&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it might mean that &quot;sudo shutdown -P now&quot; is used. This needs admin permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>The text edit is empty!</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;b&gt;process finished!&lt;/b&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>&lt;b&gt;process crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Preferences</name>
    <message>
        <source>Preferences</source>
        <translation>Postavke</translation>
    </message>
    <message>
        <source>automatic</source>
        <translation>automatski</translation>
    </message>
    <message>
        <source>Gnome session</source>
        <translation>Gnome sesija</translation>
    </message>
    <message>
        <source>KDE session</source>
        <translation>KDE sesija</translation>
    </message>
    <message>
        <source>Shutdown Method:</source>
        <translation>Metoda Gašenja:</translation>
    </message>
    <message>
        <source>The File &quot;%1&quot; is not writable!
Maybe you just don&apos;t have the permissions to do so.</source>
        <translation>U Datoteku &quot;%1&quot; nije dopušteno pisanje!
Možda naprosto nemate dopuštenja za to.</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Greška</translation>
    </message>
    <message>
        <source>Please read this carefully!</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Welcome to qprogram-starter!
If you want qprogram-starter to automatically shutdown the system and you are using the Gnome Shell, then you are likely to get a shutdown dialog from there. If you want a direct shutdown, then please consider going into the preferences and setting the shutdown method to ConsoleKit or something else.

Please feel free to visit https://launchpad.net/~hakaishi to report bugs or for anything concerning translations.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>login1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>HAL</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>UPower</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>DeviceKit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Suspend Method:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Reboot Method:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>ConsoleKit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>sudo shutdown -r now</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Maximum History saved:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Hibernate Method:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Clear History</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Don&apos;t quit or shutdown on error</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Countdown before action:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
