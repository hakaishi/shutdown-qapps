<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="bs">
<context>
    <name>Gui</name>
    <message>
        <source>HH:mm:ss</source>
        <translation>HH:mm:ss</translation>
    </message>
    <message>
        <source>dddd dd.MM.yyyy</source>
        <translation>dddd dd.MM.yyyy</translation>
    </message>
    <message>
        <source>Sho&amp;w Logs</source>
        <translation>Pri&amp;kaži izvještaje</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation>U&amp;gasi</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>&amp;Savjeti</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Zatvara qprogram-starter nakon izvršavanja posljednje komande</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>&amp;Zatvori nakon posljednje komande</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>&amp;Bilježenje</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation>Ugasi računar nakon što se izvrše sve komande</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>Sadržaj će biti povraćen nakon svakog pokretanja qprogram-startera</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>&amp;Pokreni</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>&amp;Prekini</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Pretraži...</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Sačuvaj s&amp;adržaj uređivača teksta</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Pokreni komande u ovo vrijeme</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>Da&amp;tum i vrijeme:</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Odaberite program</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation>Prvo uređivanje teksta je prazno!</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Informacije</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Proces je prekinut</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;proces 1 završen!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;procesi 1 i 2 završeni!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Greška</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;Neuspjelo pokretanje!&lt;/b&gt;&lt;br/&gt;Ne postoji takav program ili komanda.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;proces 1 je krahirao!&lt;/b&gt;&lt;br/&gt;Moguće je da je ovo prouzrokovano netačnim parametrima ili opcijama.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;proces 2 je krahirao!&lt;/b&gt;&lt;br/&gt;Moguće je da je ovo prouzrokovano netačnim parametrima ili opcijama.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Nepoznata greška!&lt;/b&gt;&lt;br/&gt;Moguće je da je ovo prouzrokovano netačnim parametrima ili opcijama.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation>&quot;%1&quot;: Nije moguće pokrenuti! Ne postoji takav program ili komanda.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation type="unfinished"></translation>
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
        <translation>&amp;Izađi</translation>
    </message>
    <message>
        <source>&amp;Configure</source>
        <translation>&amp;Podesi</translation>
    </message>
    <message>
        <source>Version </source>
        <translation>Verzija </translation>
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
        <translation>Metoda gašenja:</translation>
    </message>
    <message>
        <source>The File &quot;%1&quot; is not writable!
Maybe you just don&apos;t have the permissions to do so.</source>
        <translation>U datoteku &quot;%1&quot; se ne može zapisivati!
Možda nemate potrebnu dozvolu za zapisivanje.</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Greška</translation>
    </message>
    <message>
        <source>Please read this carefully!</source>
        <translation>Molimo vas da ovo pažljivo pročitate!</translation>
    </message>
    <message>
        <source>Welcome to qprogram-starter!
If you want qprogram-starter to automatically shutdown the system and you are using the Gnome Shell, then you are likely to get a shutdown dialog from there. If you want a direct shutdown, then please consider going into the preferences and setting the shutdown method to ConsoleKit or something else.

Please feel free to visit https://launchpad.net/~hakaishi to report bugs or for anyting concerning translations.</source>
        <translation>Dobro došli u qprogram-starter!
Ako želite da qprogram-starter vrši automatsko gašenje vašeg sistema a koristite Gnome Shell, onda je vrlo vjerovatno da će vam se tamo prikazati dijaloški okvir. Ako želite izvršiti direktno gašenje, onda vas molimo da otvorite opcije i podesite metodu gašenja na ConsoleKit ili nešto drugo.
Prijave i primjedbe za greške i prijevode možete izvršiti na https://launchpad.net/~hakaishi</translation>
    </message>
</context>
</TS>
