<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ro">
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
        <translation>Arată &amp;jurnale</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation>Înc&amp;hidere</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>&amp;Sugestii</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Închide qprogram-starter, atunci când ultima comandă s-a încheiat</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>În&amp;chide cu ultima comandă</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>&amp;Jurnalizare</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation>Închide calculator după ce toate comenzile s-au încheiat</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>Conținutul va fi restaurat la fiecare pornire a qprogram-starter</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>&amp;Pornește</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>&amp;Renunță</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Răsfoieşte...</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Salvează &amp;conținutul editoarelor text</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Începeți comenzile la această dată și oră</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>&amp;La data și ora:</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Selectează un program</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation>Prima editare de text este goală!</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Informații</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Procese întrerupte</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;procesul1 s-a încheiat!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;procesele 1 &amp; 2 s-au încheiat!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Eroare</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;nu a reușit să porneasca!&lt;/b&gt;&lt;br/&gt;Nu există un astfel de program sau comanda.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;procesul 1 s-a încheiat neasteptat!&lt;/b&gt;&lt;br/&gt;Acest lucru ar putea fi cauzat de parametri sau opțiuni invalide.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;procesul 2 s-a încheiat neasteptat!&lt;/b&gt;&lt;br/&gt;Acest lucru ar putea fi cauzat de parametri sau opțiuni invalide.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Eroare necunosctă!&lt;/b&gt;&lt;br/&gt;Acest lucru ar putea fi cauzat de parametri sau opțiuni invalide.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation>&quot;%1&quot;: Nu a reușit să înceapă! Nu există un astfel de program sau de comandă.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation>Comandă în al doilea editor de text (dacă există) va fi executată dupa prima. Casete de mesaj se vor închide după 10 secunde.&lt;br/&gt;Pentru a porni un program, doar tastați i.e. &quot;firefox&quot; ori &quot;firefox www.google.com&quot; și apoi click pe Start. Comenzile etc. pot fi legate prin by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;Dacă procesul este &quot;încheiat&quot; deși acesta este încă în desfășurare, atunci încercați opțiunea --nofork (i.e. kopete --nofork). Rețineți că acest lucru va avea loc, de asemenea, pentru unele programe, cum ar fi gedit, firefox sau gnome-terminal în cazul în care acestea sunt deja în  funcționare.&lt;br/&gt;&lt;br/&gt;Când doriți să porniți un program sau comandă cu sudo, folosiți de exemplu gksu(do) sau kdesu(do).&lt;br/&gt;&lt;br/&gt;Exemple make:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;Despre erori:&lt;br/&gt;Pentru că aproape fiecare program oferă un cod de eroare diferit, este imposibil de spus ce sa intamplat. Deci, conectați doar ieșirea și a se vedea ce fel de eroare s-a produs. Fișierele de ieșire pot fi găsite la &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;În cazul în care închiderea nu va funcționa, înseamnă că &quot;sudo shutdown -P now&quot; este utilizată. Acest lucru are nevoie de permisiuni de root. Puteți să faceți asta:&lt;br/&gt;&lt;br/&gt;Inserați următoarele într-un terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; și adăugați această linie:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; unde * înlocuiește numele de utilizator sau numele de grup.&lt;br/&gt;&lt;br/&gt;Fișierul de configurare poate fi găsit la &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Fișier</translation>
    </message>
    <message>
        <source>&amp;Settings</source>
        <translation>&amp;Setări</translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation>&amp;Ajutor</translation>
    </message>
    <message>
        <source>&amp;Quit</source>
        <translation>&amp;Ieșire</translation>
    </message>
    <message>
        <source>&amp;Configure</source>
        <translation>&amp;Configurare</translation>
    </message>
    <message>
        <source>Version </source>
        <translation>Versiunea </translation>
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
        <translation>Preferințe</translation>
    </message>
    <message>
        <source>automatic</source>
        <translation>automat</translation>
    </message>
    <message>
        <source>Gnome session</source>
        <translation>Sesiune Gnome</translation>
    </message>
    <message>
        <source>KDE session</source>
        <translation>Sesiune KDE</translation>
    </message>
    <message>
        <source>Shutdown Method:</source>
        <translation>Metodă de închidere</translation>
    </message>
    <message>
        <source>The File &quot;%1&quot; is not writable!
Maybe you just don&apos;t have the permissions to do so.</source>
        <translation>Fișierul „%1” nu poate fi scris!
Poate nu aveți permisiune de scriere.</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Eroare</translation>
    </message>
    <message>
        <source>Please read this carefully!</source>
        <translation>Citiți aceasta cu atenție!</translation>
    </message>
    <message>
        <source>Welcome to qprogram-starter!
If you want qprogram-starter to automatically shutdown the system and you are using the Gnome Shell, then you are likely to get a shutdown dialog from there. If you want a direct shutdown, then please consider going into the preferences and setting the shutdown method to ConsoleKit or something else.

Please feel free to visit https://launchpad.net/~hakaishi to report bugs or for anyting concerning translations.</source>
        <translation>Bun venit la qprogram-starter!
Dacă doriți qprogram-starter să oprească automat sistemul și utilizați Gnome Shell, atunci vă sunt susceptibile de a primi un dialog de oprire de acolo. Dacă doriți o închidere directă, atunci vă rugăm să luați în considerare de a merge în preferințele și stabilirea metodei de închidere pentru ConsoleKit sau altceva.
Vă rugăm să nu ezitați să vizitați https://launchpad.net/~hakaishi pentr a raporta buguri sau pentru orice cu privire la traduceri.</translation>
    </message>
</context>
</TS>
