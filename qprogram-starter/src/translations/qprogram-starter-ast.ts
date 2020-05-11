<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ast">
<context>
    <name>Gui</name>
    <message>
        <source>HH:mm:ss</source>
        <translation>HH:mm:ss</translation>
    </message>
    <message>
        <source>dddd dd.MM.yyyy</source>
        <translation>dddd dd-MMM-yyyy</translation>
    </message>
    <message>
        <source>Sho&amp;w Logs</source>
        <translation>Amosar re&amp;xistros</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation>Apa&amp;gar</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>&amp;Gabitos</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Colar de qprogram-starter en acabando l&apos;últimu comandu</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>&amp;Colar col últimu comandu</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>&amp;Rexistrar</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation>Apagar l&apos;ordenador en acabando l&apos;últimu comandu</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>El conteníu restauraráse con cada arranque de qprogram-starter</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>&amp;Aniciar</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>&amp;Encaboxar</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Esaminar…</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Guardar el &amp;conteníu de los editores de testu</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Llanzar los comandos esta hora y data</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>A &amp;hora y data</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Escoyer un programa</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation>¡La primera edición de testu ta balera!</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Información</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Procesos encaboxaos</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;¡finó&apos;l procesu 1!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;¡finaron los procesos 1 y 2!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Error</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;¡Nun pudo llanzase!&lt;/b&gt;&lt;br/&gt;Nun esiste esi programa o comandu.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;¡el procesu 1 frañó!&lt;/b&gt;&lt;br/&gt;Esto pue debese a parámetros o opciones inválides.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;¡el procesu 2 frañó!&lt;/b&gt;&lt;br/&gt;Esto pue debese a parámetros o opciones inválides.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;¡Error desconocíu!&lt;/b&gt;&lt;br/&gt;Esto pue debese a parámetros o opciones inválidos.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation>&quot;%1&quot;: ¡Nun pudo arrancar! Nun esiste esi programa o comandu.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation>El comandu del segundu editor de testu (si lu hai) executaráse dempués del primeru. Los cuadros de mensaxe zarraránse dempués de 10 segundos.&lt;br/&gt;P&apos;aniciar un programa sólo tien que escribir p.ex. «firefox» o «firefox www.google.com» y, darréu, calcar Llanzar. Los comandos, etc. puen encadenase con «&amp;&amp;» etc. &lt;br/&gt;&lt;br/&gt;Si&apos;l procesu ta «fináu», anque inda tea executandose, pruebe la opción «--nofork» (p.ex. kopete --nofork). Tenga en cuenta qu&apos;esto tamién asocederá con dellos programes como gedit, firefox o gnome-terminal si tá tan executandose.&lt;br/&gt;&lt;br/&gt;Cuando quiera aniciar un programa o comandu con sudo, use por exemplu gksu(do) o kdesu(do).&lt;br/&gt;&lt;br/&gt;Exemplos con «make»:&lt;br/&gt;&amp;nbsp;make -C /camín/al/proyeutu&lt;br/&gt;&amp;nbsp;make clean -C /camín/al/proyeutu&lt;br/&gt;&lt;br/&gt;Tocante a los errores:&lt;br/&gt;Como casi cada programa devuelve un códigu d&apos;error diferente, ye imposible dicir qué ye lo que pasó. Poro, namái tien que ver el rexistru de salida pa ver que tipu d&apos;error asocedió. Los ficheros de salida puen alcontrase&apos;n &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;Si l&apos;apagáu nun funciona, quier dicir que ta usando «sudo shutdown-P now». Esto necesita permisu de root. Pue facer lo siguiente:&lt;br/&gt;&lt;br/&gt;Apegue lo siguiente nun terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; y amieste esta llinia:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; onde * sustituye al nome d&apos;usuariu o al nome de grupu.&lt;br/&gt;&lt;br/&gt;El ficheru de configuración pue alcontrase&apos;n &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Ficheru</translation>
    </message>
    <message>
        <source>&amp;Settings</source>
        <translation>Preferencie&amp;s</translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation>A&amp;yuda</translation>
    </message>
    <message>
        <source>&amp;Quit</source>
        <translation>Co&amp;lar</translation>
    </message>
    <message>
        <source>&amp;Configure</source>
        <translation>&amp;Configurar</translation>
    </message>
    <message>
        <source>Version </source>
        <translation>Versión </translation>
    </message>
    <message>
        <source>Ctrl+Q</source>
        <translation>Ctrl+L</translation>
    </message>
    <message>
        <source>Ctrl+P</source>
        <translation>Ctrl+P</translation>
    </message>
    <message>
        <source>Ctrl+H</source>
        <translation>Ctrl+Y</translation>
    </message>
</context>
<context>
    <name>Preferences</name>
    <message>
        <source>Preferences</source>
        <translation>Preferencies</translation>
    </message>
    <message>
        <source>automatic</source>
        <translation>automáticu</translation>
    </message>
    <message>
        <source>Gnome session</source>
        <translation>Sesión de Gnome</translation>
    </message>
    <message>
        <source>KDE session</source>
        <translation>Sesión de KDE</translation>
    </message>
    <message>
        <source>Shutdown Method:</source>
        <translation>Métodu d&apos;apagáu:</translation>
    </message>
    <message>
        <source>The File &quot;%1&quot; is not writable!
Maybe you just don&apos;t have the permissions to do so.</source>
        <translation>¡El ficheru &quot;%1&quot; nun pue escribise!
Seique nun tenga permisos pa facelo.</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Error</translation>
    </message>
    <message>
        <source>Please read this carefully!</source>
        <translation>¡Por favor, llea esto con atención!</translation>
    </message>
    <message>
        <source>Welcome to qprogram-starter!
If you want qprogram-starter to automatically shutdown the system and you are using the Gnome Shell, then you are likely to get a shutdown dialog from there. If you want a direct shutdown, then please consider going into the preferences and setting the shutdown method to ConsoleKit or something else.

Please feel free to visit https://launchpad.net/~hakaishi to report bugs or for anything concerning translations.</source>
        <translation>¡Bienveníu a qprogram-starter!
Si quier que qprogram-starter apague&apos;l sistema de mou automáticu y ta usando Gnome Shell, posiblemente recibirá un diálogu d&apos;apagáu de la mesma. Si quier un apagáu direutu, por favor, considere entrar nes preferencies y configurar el métodu d&apos;apagáu a ConsoleKit o daqué distinto.
Visite con total llibertá https://launchpad.net/~hakaishi si quier informar de fallos o  de cualquier cosa tocante a les traducciones.</translation>
    </message>
</context>
</TS>
