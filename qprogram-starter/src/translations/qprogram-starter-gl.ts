<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="gl">
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
            <translation>Amosar &amp;rexistros</translation>
        </message>
        <message>
            <source>S&amp;hutdown</source>
            <translation>Apa&amp;gado</translation>
        </message>
        <message>
            <source>&amp;Hints</source>
            <translation>&amp;Consellos</translation>
        </message>
        <message>
            <source>Quits qprogram-starter when the last command finished</source>
            <translation>Saír de qprogram-starter cando remate a última orde</translation>
        </message>
        <message>
            <source>&amp;Quit with last command</source>
            <translation>&amp;Saír coa última orde</translation>
        </message>
        <message>
            <source>&amp;Logging</source>
            <translation>&amp;Acceso</translation>
        </message>
        <message>
            <source>Shutdown the computer after all commands finished</source>
            <translation>Apagar o computador despois de que remate a última orde</translation>
        </message>
        <message>
            <source>The contents will be restored on every start of qprogram-starter</source>
            <translation>Os contidos restauranse en cada inicio de qprogram-starter</translation>
        </message>
        <message>
            <source>&amp;Start</source>
            <translation>&amp;Iniciar</translation>
        </message>
        <message>
            <source>&amp;Abort</source>
            <translation>&amp;Interromper</translation>
        </message>
        <message>
            <source>Browse...</source>
            <translation>Examinar...</translation>
        </message>
        <message>
            <source>Save text editors &amp;contents</source>
            <translation>Gardar os &amp;contidos dos editores de texto</translation>
        </message>
        <message>
            <source>Start the commands to this time and date</source>
            <translation>Iniciar as ordes nesta hora e data</translation>
        </message>
        <message>
            <source>A&amp;t date and time:</source>
            <translation>&amp;Nesta hora e data</translation>
        </message>
        <message>
            <source>Select a program</source>
            <translation>Seleccione un programa</translation>
        </message>
        <message>
            <source>The first text edit is empty!</source>
            <translation>O primeir texto de edición está baleiro!</translation>
        </message>
        <message>
            <source>Information</source>
            <translation>Información</translation>
        </message>
        <message>
            <source>Processes aborted</source>
            <translation>Proceso interrompido</translation>
        </message>
        <message>
            <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
            <translation>&lt;b&gt;o proceso 1 rematou!&lt;/b&gt;</translation>
        </message>
        <message>
            <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
            <translation>&lt;b&gt;os procesos 1 e 2 remataron!&lt;/b&gt;</translation>
        </message>
        <message>
            <source>Error</source>
            <translation>Erro</translation>
        </message>
        <message>
            <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
            <translation>&lt;b&gt;Produciuse un fallo no inicio!&lt;/b&gt;&lt;br/&gt;Non hai tal programa ou orde.</translation>
        </message>
        <message>
            <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
            <translation>&lt;b&gt;o proceso 1 quebrou!&lt;/b&gt;&lt;br/&gt;Isto pode ser por mor de parámetros ou opcións incorrectas.</translation>
        </message>
        <message>
            <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
            <translation>&lt;b&gt;o proceso 2 quebrou!&lt;/b&gt;&lt;br/&gt;Isto pode ser por mor de parámetros ou opcións incorrectas.</translation>
        </message>
        <message>
            <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
            <translation>&lt;b&gt;Produciuse un erro descoñecido!&lt;/b&gt;&lt;br/&gt;Isto pode ser por mor de parámetros ou opcións incorrectas.</translation>
        </message>
        <message>
            <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
            <translation>«%1»: Produciuse un fallo ao inicialo! Non hai tal programa ou orde.
</translation>
        </message>
        <message>
            <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won't work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
            <translation>A orde no segundo editor de texto (se hai algunha) executarase despois da primeira. As caixas de mensaxe pecharanse despois de 10 segundos.&lt;br/&gt;Para iniciar un programa só ten que escribir p.ex. «firefox» ou «firefox www.google.com» a de seguido premer en Inicio. As ordes, etc. pódense encadear con «&amp;&amp;» etc. &lt;br/&gt;&lt;br/&gt;Se o proceso está «rematado», a pesares de estar aínda en execución, tente usar a opción «--nofork» (p.ex. kopete --nofork). Teña en conta que isto tamén pode ocorrer con algúns outros programas como gedit, firefox ou gnome-terminal se xa estean en execución.&lt;br/&gt;&lt;br/&gt;Se quere iniciar un programa ou orde con sudo, empregue por por exemplo gksu(do) o kdesu(do).&lt;br/&gt;&lt;br/&gt;exemplos con «make»:&lt;br/&gt;&amp;nbsp;make -C /ruta/ao/proxecto&lt;br/&gt;&amp;nbsp;make clean -C /ruta/ao/proxecto&lt;br/&gt;&lt;br/&gt;Sobre os erros:&lt;br/&gt;Xa que case todos os programas dan un código de erro diferente, é imposíbel dicir que foi o que pasou. Só ten que ver a saída e ver que tipo de erro se produciu. Os ficheiros de saída pódense atopar en &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;Se o peche non funciona, é porque «sudo shutdown-P now» aínda está en uso. Isto precisa permisos de administrador (root). Neste caso pode facer o seguinte:&lt;br/&gt;&lt;br/&gt;Pegue o seguinte nun terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; e engada esta liña:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; onde * substitúe o nome de usuario ou o nome do grupo %group.&lt;br/&gt;&lt;br/&gt;O ficheiro de configuración atopase en &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
        </message>
        <message>
            <source>&amp;File</source>
            <translation>&amp;Ficheiro</translation>
        </message>
        <message>
            <source>&amp;Settings</source>
            <translation>&amp;Configuracións</translation>
        </message>
        <message>
            <source>&amp;Help</source>
            <translation>&amp;Axuda</translation>
        </message>
        <message>
            <source>&amp;Quit</source>
            <translation>&amp;Saír</translation>
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
            <translation>Preferencias</translation>
        </message>
        <message>
            <source>automatic</source>
            <translation>automático</translation>
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
            <translation>Método de apagado:</translation>
        </message>
        <message>
            <source>The File &quot;%1&quot; is not writable!
Maybe you just don't have the permissions to do so.</source>
            <translation>O ficheiro «%1» non é escribíbel.
E probábel que non teña permisos para facelo.</translation>
        </message>
        <message>
            <source>Welcome to qprogram-starter!
If you want qprogram-starter to automatically shutdown the system and you are using the Gnome Shell, then you are likely to get a shutdown dialog from there. If you want a direct shutdown, then please consider going into the preferences and setting the shutdown method to ConsoleKit or something else.
Please feel free to visit https://launchpad.net/~hakaishi to report bugs or for anyting concerning translations.</source>
            <translation>Benvido a qprogram-starter!
Se quere que qprogram-starter apague automaticamente o sistema e emprega o Gnome Shell, entón é probábel que obteña un diálogo de apagado. Se quere dspor dun apagado directo, vaia ás preferencias e estableza o método de apagado para ConsoleKit ou outro.
Non dubide en visitar https://launchpad.net/~hakaishi para informar de erros, ou calquera outra cousa sobre as traducións.</translation>
        </message>
        <message>
            <source>Error</source>
            <translation>Erro</translation>
        </message>
        <message>
            <source>Please read this carefully!</source>
            <translation>Por favor, lea isto detidamente!</translation>
        </message>
    </context>
</TS>
