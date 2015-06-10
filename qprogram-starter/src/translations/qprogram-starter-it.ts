<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="it">
<context>
    <name>Gui</name>
    <message>
        <source>HH:mm:ss</source>
        <translation>HH:mm:ss</translation>
    </message>
    <message>
        <source>dddd dd.MM.yyyy</source>
        <translation>ddd d MMM yyyy</translation>
    </message>
    <message>
        <source>Sho&amp;w Logs</source>
        <translation>Most&amp;ra registri</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation>&amp;Arrestare</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>S&amp;uggerimenti</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Esce da qprogram-starter al termine dell&apos;ultimo comando</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>&amp;Uscire dopo l&apos;ultimo comando</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>Re&amp;gistrazione</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation>Arresta il computer al termine dell&apos;ultimo comando</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>I contenuti verranno ripristinati ad ogni avvio di qprogram-starter</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>A&amp;vvia</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>&amp;Interrompi</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Esplora...</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Salva campi e contenuti</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Lancia i comandi alla data e ora stabiliti</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>Avvia in data e ora:</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Seleziona programma</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation>Il primo campo è vuoto</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Informazioni</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Elaborazione interrotta</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;Processo 1 completato.&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;Processi 1 e 2 completati.&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Errore</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;Impossibile avviare.&lt;/b&gt;&lt;br/&gt;Nessun programma o comando specificati.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Processo 1 bloccato.&lt;/b&gt;&lt;br/&gt;Questo può dipendere da opzioni o parametri non validi.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Processo 2 bloccato.&lt;/b&gt;&lt;br/&gt;Questo può dipendere da opzioni o parametri non validi.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Errore sconosciuto.&lt;/b&gt;&lt;br/&gt;Questo può dipendere da opzioni o parametri non validi.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation>«%1»: impossibile avviare. Nessun programma o comando specificati.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation>Il comando nel secondo campo (se presente) verrà eseguito dopo il primo. Le finestre dei messaggi verranno chiuse automaticamente dopo 10 secondi.&lt;br/&gt;Per lanciare un programma scrivere semplicemente, per esempio, «firefox» o «firefox www.google.com» e fare clic su «Avvia». I vari comandi possono essere eseguiti in sequenza usando «&amp;&amp;».&lt;br/&gt;&lt;br/&gt;Se l&apos;elaborazione viene indicata come conclusa nonostante sia ancora in esecuzione, provare l&apos;opzione «--nofork» (per esempio kopete --nofork). Notare che questo potrebbe essere necessario per alcuni programmi come gedit, firefox o gnome-terminal quando sono già in esecuzione.&lt;br/&gt;&lt;br/&gt;Per eseguire un programma o un comando usando «sudo», usare «gksu(do)» o «kdesu(do)».&lt;br/&gt;&lt;br/&gt;Alcuni esempi:&lt;br/&gt;&amp;nbsp;make -C /percorso/del/progetto/&lt;br/&gt;&amp;nbsp;make clean -C /percorso/del/progetto&lt;br/&gt;&lt;br/&gt;Informazioni sugli errori:&lt;br/&gt;A causa dei diversi codici di errore restituiti dai vari programmi, non è possibile stabilire cosa accade. Controllare quindi l&apos;output dei comandi per vedere quale errore si è verificato. I fiel di output possono essere trovati in &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;Se non è possibile eseguire lo spegnimento della macchina, significa che è stato usato il comando «sudo shutdown -P now». Questa operazione richiede i privilegi di root. È possibile provare le seguenti operazioni:&lt;br/&gt;&lt;br/&gt;Eseguire in un terminale il seguente comando:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; e aggiungere al file appena aperto la seguente riga:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; sostituendo «*» con «username» o «%groupname». .&lt;br/&gt;&lt;br/&gt;Il file di configurazione si trova in  &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;File</translation>
    </message>
    <message>
        <source>&amp;Settings</source>
        <translation>Impo&amp;stazioni</translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation>A&amp;iuto</translation>
    </message>
    <message>
        <source>&amp;Quit</source>
        <translation>&amp;Esci</translation>
    </message>
    <message>
        <source>&amp;Configure</source>
        <translation>&amp;Configura</translation>
    </message>
    <message>
        <source>Version </source>
        <translation>Versione </translation>
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
        <translation>Preferenze</translation>
    </message>
    <message>
        <source>automatic</source>
        <translation>automatico</translation>
    </message>
    <message>
        <source>Gnome session</source>
        <translation>Sessione GNOIME</translation>
    </message>
    <message>
        <source>KDE session</source>
        <translation>Sessione KDE</translation>
    </message>
    <message>
        <source>Shutdown Method:</source>
        <translation>Metodo di arresto:</translation>
    </message>
    <message>
        <source>The File &quot;%1&quot; is not writable!
Maybe you just don&apos;t have the permissions to do so.</source>
        <translation>Il file «%1» non è scrivibile.
Forse non si hanno i permessi per eseguire l&apos;operazione.</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Errore</translation>
    </message>
    <message>
        <source>Please read this carefully!</source>
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
