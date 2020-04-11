<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ms">
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
        <translation>Papa&amp;r Log</translation>
    </message>
    <message>
        <source>S&amp;hutdown</source>
        <translation>&amp;Matikan</translation>
    </message>
    <message>
        <source>&amp;Hints</source>
        <translation>Pem&amp;bayang</translation>
    </message>
    <message>
        <source>Quits qprogram-starter when the last command finished</source>
        <translation>Keluar qprogram-starter bila perintah terakhir selesai</translation>
    </message>
    <message>
        <source>&amp;Quit with last command</source>
        <translation>&amp;Keluar dengan perintah terakhir</translation>
    </message>
    <message>
        <source>&amp;Logging</source>
        <translation>Pen&amp;gelogan</translation>
    </message>
    <message>
        <source>Shutdown the computer after all commands finished</source>
        <translation>Matikan komputer selepas semua perintah selesai</translation>
    </message>
    <message>
        <source>The contents will be restored on every start of qprogram-starter</source>
        <translation>Kandungan yang akan dipulih setiap kali mulakan qprogram-starter</translation>
    </message>
    <message>
        <source>&amp;Start</source>
        <translation>&amp;Mula</translation>
    </message>
    <message>
        <source>&amp;Abort</source>
        <translation>Henti P&amp;aksa</translation>
    </message>
    <message>
        <source>Browse...</source>
        <translation>Layar...</translation>
    </message>
    <message>
        <source>Save text editors &amp;contents</source>
        <translation>Simpan kan&amp;dungan penyunting teks</translation>
    </message>
    <message>
        <source>Start the commands to this time and date</source>
        <translation>Mula perintah pada masa dan tarikh ini</translation>
    </message>
    <message>
        <source>A&amp;t date and time:</source>
        <translation>&amp;Pada tarikh dan masa:</translation>
    </message>
    <message>
        <source>Select a program</source>
        <translation>Pilih satu program</translation>
    </message>
    <message>
        <source>The first text edit is empty!</source>
        <translation>Suntingan teks pertama adalah kosong!</translation>
    </message>
    <message>
        <source>Information</source>
        <translation>Maklumat</translation>
    </message>
    <message>
        <source>Processes aborted</source>
        <translation>Proses dihenti paksa</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;proses 1 selesai!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 &amp; 2 finished!&lt;/b&gt;</source>
        <translation>&lt;b&gt;proses 1 &amp; 2 selesai!&lt;/b&gt;</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Ralat</translation>
    </message>
    <message>
        <source>&lt;b&gt;Failed to start!&lt;/b&gt;&lt;br/&gt;No such program or command.</source>
        <translation>&lt;b&gt;Gagal dimulakan!&lt;/b&gt;&lt;br/&gt;Tiada program atau perintah sebegitu.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 1 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;proses 1 mengalami kerosakan!&lt;/b&gt;&lt;br/&gt;Ia disebabkan oleh parameter atau pilihan tidak sah.</translation>
    </message>
    <message>
        <source>&lt;b&gt;process 2 crashed!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;proses 2 mengalami kerosakan!&lt;/b&gt;&lt;br/&gt;Ia disebabkan oleh parameter atau pilihan tidak sah.</translation>
    </message>
    <message>
        <source>&lt;b&gt;Unknown error!&lt;/b&gt;&lt;br/&gt;This could be caused by invalid parameters or options.</source>
        <translation>&lt;b&gt;Ralat tidak diketahui!&lt;/b&gt;&lt;br/&gt;Ia disebabkan oleh parameter atau pilihan tidak sah.</translation>
    </message>
    <message>
        <source>&quot;%1&quot;: Failed to start! No such program or command.
</source>
        <translation>&quot;%1&quot;: Gagal dimulakan! Tiada program atau perintah sebegitu.
</translation>
    </message>
    <message>
        <source>The command in the second text editor (if there is any) will be executed after the first one. The message boxes will close themselves after 10 seconds.&lt;br/&gt;To start a program just type i.e. &quot;firefox&quot; or &quot;firefox www.google.com&quot; and then click on Start. Commands etc. can be linked by &quot;&amp;&amp;&quot; etc. &lt;br/&gt;&lt;br/&gt;If the process is &quot;finished&quot; although it is still running, then try the --nofork option (i.e. kopete --nofork). Note that this will also occure for some programs like gedit, firefox or gnome-terminal if they are already running.&lt;br/&gt;&lt;br/&gt;When you want to start a program or command with sudo, please use for example gksu(do) or kdesu(do).&lt;br/&gt;&lt;br/&gt;make examples:&lt;br/&gt;&amp;nbsp;make -C /path/to/project&lt;br/&gt;&amp;nbsp;make clean -C /path/to/project&lt;br/&gt;&lt;br/&gt;About Errors:&lt;br/&gt;Because almost every program gives a different error code, it is impossible to say what happend. So just log the output and see what kind of error occured. The output files can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;If the shutdown won&apos;t work, it means that &quot;sudo shutdown -P now&quot; is used. This needs root permissions. You can do the this:&lt;br/&gt;&lt;br/&gt;Post the following in a terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; and add this line:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; whereas * replaces the username or %groupname.&lt;br/&gt;&lt;br/&gt;The configuration-file can be found at &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</source>
        <translation>Perintah dalam penyunting teks kedua (jika ada) akan dilakukan selepas yang pertama. Kotak mesej akan ditutup sendiri selepas 10 saat.&lt;br/&gt;Untuk mulakan program hanya taip, cth. &quot;firefox&quot; atau &quot;firefox www.google.com&quot; dan kemudian klik pada Mula. Perintah dll. boleh dipaut dengan tanda &quot;&amp;&amp;&quot; dll. &lt;br/&gt;&lt;br/&gt;Jika proses telah &quot;selesai&quot; walaupun ia masih lagi berjalan, maka cuba pilihan --nofork (cth. kopete --nofork). Pethatian ia juga berlaku pada beberapa program seperti gedit, firefox atau gnome-terminal jika ia sedang berjalan.&lt;br/&gt;&lt;br/&gt;Bila anda mahu mulakan program atau perintah dengan sudo, sila guna gksu(do) atau kdesu(do).&lt;br/&gt;&lt;br/&gt;contoh make:&lt;br/&gt;&amp;nbsp;make -C /laluan/ke/projek&lt;br/&gt;&amp;nbsp;make clean -C /laluan/ke/projek&lt;br/&gt;&lt;br/&gt;Perihal Ralat:&lt;br/&gt;Oleh kerana setiap program menghasilkan kod ralat yang berbeza, adalah mustahil dapat menerangkan apa yang telah berlaku. Oleh itu hanya logkan output dan lihat apakah jenis ralat yang berlaku. Fail output boleh ditemui di &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.&lt;br/&gt;&lt;br/&gt;Jika shutdown tidak berfungsi, ia bermaksud &quot;sudo shutdown -P now&quot; digunakan. Ia memerlukan keizinan root. Anda boleh membuatnya:&lt;br/&gt;&lt;br/&gt;Poskan yang berikut kedalam terminal:&lt;pre&gt;EDITOR=nano sudo -E visudo&lt;/pre&gt; dan tambah baris ini:&lt;pre&gt;* ALL = NOPASSWD:/sbin/shutdown&lt;/pre&gt; yang mana * gantikan nama pengguna atau %groupname.&lt;br/&gt;&lt;br/&gt;Fail-konfigurasi boleh ditemui di &lt;i&gt;~/.qprogram-starter/&lt;/i&gt;.</translation>
    </message>
    <message>
        <source>&amp;File</source>
        <translation>&amp;Fail</translation>
    </message>
    <message>
        <source>&amp;Settings</source>
        <translation>&amp;Tetapan</translation>
    </message>
    <message>
        <source>&amp;Help</source>
        <translation>&amp;Bantuan</translation>
    </message>
    <message>
        <source>&amp;Quit</source>
        <translation>&amp;Keluar</translation>
    </message>
    <message>
        <source>&amp;Configure</source>
        <translation>Konfi&amp;gur</translation>
    </message>
    <message>
        <source>Version </source>
        <translation>Versi </translation>
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
        <translation>Keutamaan</translation>
    </message>
    <message>
        <source>automatic</source>
        <translation>automatik</translation>
    </message>
    <message>
        <source>Gnome session</source>
        <translation>Sesi Gnome</translation>
    </message>
    <message>
        <source>KDE session</source>
        <translation>Sesi KDE</translation>
    </message>
    <message>
        <source>Shutdown Method:</source>
        <translation>Kaedah Matikan:</translation>
    </message>
    <message>
        <source>The File &quot;%1&quot; is not writable!
Maybe you just don&apos;t have the permissions to do so.</source>
        <translation>Fail &quot;%1&quot; tidak boleh ditulis!
Mungkin anda tidak mempunyai keizinan membuatnya.</translation>
    </message>
    <message>
        <source>Error</source>
        <translation>Ralat</translation>
    </message>
    <message>
        <source>Please read this carefully!</source>
        <translation>Sila baca dengan teliti!</translation>
    </message>
    <message>
        <source>Welcome to qprogram-starter!
If you want qprogram-starter to automatically shutdown the system and you are using the Gnome Shell, then you are likely to get a shutdown dialog from there. If you want a direct shutdown, then please consider going into the preferences and setting the shutdown method to ConsoleKit or something else.

Please feel free to visit https://launchpad.net/~hakaishi to report bugs or for anything concerning translations.</source>
        <translation>Selamat datang ke qprogram-starter!
Jika anda mahu qprogram-starter matikan sistem secara automatik dan anda menggunakan Shell Gnome, maka anda perlu dapatkan dialog matikan disana. Jika anda mahu matikan secara terus, maka peergi ke keutamaan dan tetapkan kaedah matikan ke ConsoleKit atau yang lain.
Sila lawati https://launchpad.net/~hakaishi untuk laporkan pepijat atau lain-lain berkenaan terjemahan.</translation>
    </message>
</context>
</TS>
