Funciones de la biblioteca GNU Readline (gestión de línea de comandos):
readline:

Lee una línea de entrada del usuario, con características como historial y edición interactiva (usualmente para shells o interfaces).
Proporcionada por la biblioteca GNU Readline.
rl_clear_history:

Limpia el historial de comandos almacenado por Readline.
rl_on_new_line:

Indica a Readline que debe iniciar una nueva línea (útil para manejar entradas interactivas).
rl_replace_line:

Reemplaza el contenido actual de la línea editada en Readline.
rl_redisplay:

Redibuja la línea de edición actual (útil para actualizar la interfaz del usuario).
add_history:

Añade la línea de entrada más reciente al historial de comandos.
Funciones de entrada/salida estándar:
printf:

Imprime texto formateado en la salida estándar.
write:

Escribe datos sin formato en un archivo o descriptor de archivo (nivel bajo).
read:

Lee datos sin formato desde un archivo o descriptor de archivo.
access:

Verifica si un archivo es accesible con ciertos permisos (lectura, escritura, etc.).
open:
Abre un archivo y devuelve un descriptor de archivo.
close:
Cierra un descriptor de archivo.
malloc:
Reserva memoria dinámica en el heap.
free:
Libera memoria previamente reservada con malloc.
unlink:
Elimina un archivo.
Funciones relacionadas con procesos:
fork:
Crea un nuevo proceso hijo duplicando el proceso actual.
wait:
Espera a que un proceso hijo termine.
waitpid:
Espera a que un proceso hijo específico termine.
wait3 y wait4:
Versiones extendidas de wait, que permiten obtener información adicional sobre el proceso hijo terminado.
execve:
Reemplaza el programa actual por otro (usualmente para ejecutar un binario nuevo).
exit:
Termina el proceso actual, devolviendo un código de salida.
Funciones relacionadas con señales:
signal:
Configura un manejador para señales específicas.
sigaction:
Alternativa moderna a signal, que permite un control más detallado de las señales.
kill:
Envía una señal a un proceso o grupo de procesos.
Funciones relacionadas con el sistema de archivos:
getcwd:
Obtiene el directorio de trabajo actual.
chdir:
Cambia el directorio de trabajo actual.
stat:
Obtiene información sobre un archivo (metadatos).
lstat:
Similar a stat, pero funciona con enlaces simbólicos.
fstat:
Similar a stat, pero opera sobre descriptores de archivo.
Funciones relacionadas con terminales e I/O avanzado:
isatty:
Verifica si un descriptor de archivo es un terminal.
ttyname:
Obtiene el nombre del archivo asociado a un terminal.
ttyslot:
Obtiene el número de línea del terminal en uso.
ioctl:
Realiza operaciones de control sobre dispositivos (como terminales).
tcsetattr:
Configura atributos del terminal.
tcgetattr:
Obtiene atributos del terminal.
Funciones relacionadas con terminales (capas terminfo):
tgetent:
Inicializa una entrada de terminal desde la base de datos terminfo.
tgetflag:
Obtiene un indicador booleano de la entrada terminfo.
tgetnum:
Obtiene un valor numérico de la entrada terminfo.
tgetstr:
Obtiene una cadena de la entrada terminfo.
tgoto:
Construye una cadena para posicionar el cursor en terminfo.
tputs:
Envía una cadena de salida terminfo al terminal.
Funciones relacionadas con directorios:
opendir:
Abre un directorio para leer su contenido.
readdir:
Lee la siguiente entrada en un directorio abierto.
closedir:
Cierra un directorio previamente abierto con opendir.
Funciones relacionadas con errores:
strerror:
Convierte un código de error en un mensaje de texto legible.
perror:
Imprime un mensaje de error asociado al valor de errno.
Funciones relacionadas con variables de entorno:
getenv:
Obtiene el valor de una variable de entorno.
