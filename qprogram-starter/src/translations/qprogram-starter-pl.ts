<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="pl">
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
        <translation>Pok&amp;aż dziennik</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation>W&amp;yłącz</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>&amp;Podpowiedzi</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Zamyka qprogram-starter po wykonaniu ostatniego polecenia</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>&amp;Zakończ z ostatnim poleceniem</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>&amp;Dziennik</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation>Wyłącz komputer po wykonaniu wszystkich poleceń</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>Zawartość zostanie odtworzona przy każdym uruchomieniu qprogram-starter</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>&amp;Start</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>&amp;Przerwij</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Przeglądaj...</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Zapisz &amp;zawartość edytora tekstu</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Wykonaj polecenie o danej godzinie danego dnia</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>&amp;O czasie:</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Wybierz program</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation>Pierwsze pole tekstowe jest puste!</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Informacja</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Procesy przerwane</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;proces 1 zakończony!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;procesy 1 i 2 zakończone!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Błąd</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;Uruchomienie nie powiodło się!&lt;/b&gt;&lt;br/&gt;Brak takiego programu bądź polecenia.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;proces 1 został niespodziewanie zakończony!&lt;/b&gt;&lt;br/&gt;Może to być spowodowane niewłaściwymi parametrami lub opcjami.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;proces 2 został niespodziewanie zakończony!&lt;/b&gt;&lt;br/&gt;Może to być spowodowane niewłaściwymi parametrami lub opcjami.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Nieznany błąd!&lt;/b&gt;&lt;br/&gt;Może być spowodowany niewłaściwymi parametrami lub opcjami.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation>&quot;%1&quot;: Uruchomienie nie powiodło się! Brak takiego programu bądź polecenia.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation>Polecenie z drugiego pola tekstowego (jeśli pole jest wypełnione) zostanie wykonane po pierwszym. Powiadomienia zamkną się po 10 sekundach.&lt;br/&gt;By uruchomić program wpisz np. &quot;firefox&quot; lub &quot;firefox www.google.com&quot; i kliknij Start. Polecenia mogą być łączone znakiem &quot;&amp;&amp;&quot;.&lt;br/&gt;&lt;br/&gt;Jeśli proces został &quot;zakończony&quot; miomo, że wciąż działa, wypróbuj opcję --nofork (np. kopete --nofork). Zauważ, że taka sytuacja będzie miała miejsce dla niektórych programów takich jak gedit, firefox, czy gnome-terminal jeśli są już uruchomione.&lt;br/&gt;&lt;br/&gt;Jeśli chcesz uruchomić program z uprawnieniami administratora (sudo), używaj gksu(do) lub kdesu(do).&lt;br/&gt;&lt;br/&gt;Przykład dla make:&lt;br/&gt;&amp;nbsp;make -C /ścieżka/do/projektu&lt;br/&gt;&amp;nbsp;make clean -C /ścieżka/do/projektu&lt;br/&gt;&lt;br/&gt;O błedach:&lt;br/&gt;Ponieważ prawie każdy program zwraca inny kod błędu niemożliwe jest określenie co się stało. Zapisz wyjście programu i zobacz jaki rodzaj błedu się pojawił. Pliki z wyjściami można znaleźć w katalogu &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;Jeśli wyłączanie komputera nie działa oznacza to, że używane jest &quot;sudo shutdown -P now&quot;. To polecenie wymaga uprawnień administratora. Można to rozwiązać w następujący sposób:&lt;br/&gt;&lt;br/&gt;Wykonaj następujące polecenie w terminalu:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; i dodaj tą linijkę: &lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; gdzie * zastępuję nazwę użytkownika lub %grupy.&lt;br/&gt;&lt;br/&gt;Plik konfiguracyjny można znaleźć w katalogu &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Plik</translation>
    </message>
    <message>
        <source>&amp;Settings</source>
        <translation>&amp;Ustawienia</translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation>&amp;Pomoc</translation>
    </message>
    <message>
        <source>&amp;Quit</source>
        <translation>&amp;Wyjdź</translation>
    </message>
    <message>
        <source>&amp;Configure</source>
        <translation>&amp;Konfiguruj</translation>
    </message>
    <message>
        <source>Version </source>
        <translation>Wersja </translation>
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
        <translation>Preferencje</translation>
    </message>
    <message>
        <source>automatic</source>
        <translation>automatyczna</translation>
    </message>
    <message>
        <source>Gnome session</source>
        <translation>Sesja Gnome</translation>
    </message>
    <message>
        <source>KDE session</source>
        <translation>Sesja KDE</translation>
    </message>
    <message>
        <source>Shutdown Method:</source>
        <translation>Metoda zamknięcia:</translation>
    </message>
    <message>
        <source>The File &quot;%1&quot; is not writable!
Maybe you just don&apos;t have the permissions to do so.</source>
        <translation>Plik &quot;%1&quot; jest niezapisywalny!
Być może nie masz po prostu uprawnień do wykonania tej akcji.</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Błąd</translation>
    </message>
    <message>
        <source>Please read this carefully!</source>
        <translation>Proszę przeczytać to uważnie!</translation>
    </message>
    <message>
        <source>Welcome to qprogram-starter!
If you want qprogram-starter to automatically shutdown the system and you are using the Gnome Shell, then you are likely to get a shutdown dialog from there. If you want a direct shutdown, then please consider going into the preferences and setting the shutdown method to ConsoleKit or something else.

Please feel free to visit https://launchpad.net/~hakaishi to report bugs or for anyting concerning translations.</source>
        <translation>Witaj w qprogram-starter!
Jeśli chcesz by qprogram-starter automatycznie zamykał system i używasz Gnome Shell, prawdopodobnie uzyskasz stąd dialog zamknięcia. Jeśli chcesz bezpośredniego zamknięcia, rozważ ustawienie metody zamknięcia w preferencjach na ConsoleKit lub coś innego.
Odwiedź https://launchpad.net/~hakaishi w celu zgłoszenia błędów lub w sprawach dotyczących tłumaczeń.</translation>
    </message>
</context>
</TS>
