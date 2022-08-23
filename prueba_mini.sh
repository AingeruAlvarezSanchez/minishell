/bin/ls
/bin/pwd
echo -n jamon
echo -n jamon
echo "jamon"
echo $?
echo "cat lol.c | cat > lol.c"
"ls" -l | grep "a"
' '
''
'ls' -l | grep 'a'
echo '$USER'

#- Ejecuta un comando simple con una ruta absoluta como /bin/ls, u otro
#comando con argumentos pero sin comillas simples y comillas dobles.
/bin/ls
/bin/pwd
#- Prueba un comando vacío.
#- Prueba solo tabuladores o espacios.

#- Ejecuta un comando simple con una ruta absoluta como /bin/ls, u otro
#comando con argumentos pero sin comillas simples y comillas dobles.
/bin/ls

#echo
#- Ejecuta el comando echo con o sin argumentos, y con o sin -n.
echo -n jamon
echo -n jamon
echo "jamon"

#exit
#- Ejecuta el comando exit con o sin argumentos.
exit 1
exit 0
exit 1231231245
exit asv

#Valor de retorno de un proceso
#Ejecuta una prueba simple con una ruta absoluta del tipo /bin/ls, o
#algún otro comando con argumentos pero sin comillas simples o comillas
#dobles. Después ejecuta echo $?
/bin/ls
echo $?                                                                         MAL

#- Hazlo varias veces, con distintos comandos y argumentos. Ejecuta
#algunos comandos que fallen como '/bin/ls archivo_que_no_existe'.
#- Algo como 'expr $? + $?'.

<< 'Comment'
Señales
- Verifica que ctrl-C en una entrada limpia muestra una nueva línea con         
una entrada limpia.
- Verifica que ctrl-\ en una entrada limpia no hace nada.
- Verifica que ctrl-D en una entrada limpia termina minishell, ejecútalo         (corregido)segfaul
de nuevo.
- Verifica que ctrl-C en una entrada con texto, muestra una nueva línea          (corregido)MAL despues de un comando
con una entrada limpia.
- El buffer debería limpiarse correctamente, pulsa "enter" para
verificar que nada de lo que habías escrito se ejecute.
- Verifica que ctrl-D en una entrada con texto no hace nada.
- Verifica que ctrl-\ en una entrada con texto no hace nada.                    (corregido)MAL
- Verifica que ctrl-C después de ejecutar un comando bloqueante como
cat sin argumentos o grep "algo".
- Verifica que ctrl-\ después de ejecutar un comando bloqueante como
cat sin argumentos o grep "algo".
- Verifica que ctrl-D después de ejecutar un comando bloqueante como
cat sin argumentos o grep "algo".
Comment

#Comillas dobles
#- Ejecuta un comando simple con argumentos, esta vez con comillas dobles
#(deberás incluir espacios).

echo "cat lol.c | cat > lol.c"
"ls" -l | grep "a"

#Comillas simples
#- Ejecuta comandos con comillas simples como argumento.
' '
''
'ls' -l | grep 'a'
echo '$USER'

#env
#- Comprueba si env muestra las variables de entorno actuales
env

#export
#- Exporta variables de entorno, crea nuevas, y reemplaza viejas.
#- Comprueba que funcione correctamente con env
export zoologico=420
env | grep zoologico

export zoologico = 420                                                  MAL
#bash: export: `=': not a valid identifier
#bash: export: `420': not a valid identifier

#unset
#- Exporta variables de entorno, crea nuevas, y reemplaza viejas.
#- Utiliza unset para eliminar algunas de ellas.
#- Verifica el resultado con env.

export mercadona=420
env | grep mercadona
unset mercadona
env | grep mercadona                                                        MAL

#- Utiliza el comando cd para cambiar de directorio de trabajo, y
#asegúrate de que estás en el directorio correcto con /bin/ls.
cd src
bin/ls
cd..
pwd
cd.
cd
cd -

#pwd
#- Utiliza el comando pwd.
pwd
env

#Rutas relativas
#- Ejecuta comandos, pero esta vez con rutas relativas.

ls ..
ls /libft
pwd src/                                                                MAL

#La variable de entorno PATH
#- Ejecuta comandos, pero esta vez sin rutas (ls, wc, awk, etc).
ls

#- Elimina $PATH y verifica que ya no funcionen.
unset PATH                                                              MAL

#- Establece $PATH para varios directorios (directorio1:directorio2) y
#valida que los directorios se comprueban de izquierda a derecha.
                                                                        NO ENTIENDO
                                                               
#Redirecciones
#- Ejecuta comandos con redirecciones < y/o >.
ls > texto.txt                                                          POR HACER

#- Repite esto varias veces con diferentes comandos y argumentos, cambia
#de vez en cuando > por >>.
ls >> texto.txt                                                          POR HACER

#Pipes
#- Ejecuta comandos con pipes como 'cat file | grep bla | more'.
ls -l -a | grep e | wc
ls archivoquenoexiste | grep bla | more

#- Prueba a mezclar pipes y redirecciones.
ls -l -a | grep e | wc > texto.txt                                      BUENA SUERTE

<< 'Comment'
Vuélvete loco, y el historial
- Escribe una línea de comandos, utiliza ctrl-C y pulsa enter. El buffer
deberá estar vacío y nada deberá ejecutarse.
- ¿Puedes navegar en el historial con las flechas de arriba y abajo
para reintentar algún comando?
- Ejecuta comandos que no deberían funcionar como 'wjkgjrgwg4g43go34o'
y verifica que minishell no termina y muestra un error.
- "cat | cat | ls" se comporta de forma "normal".
- Prueba a ejecutar un comando largo con muchísimos argumentos.
- Pásatelo bien con este increíble minishell y disfruta.
Comment

#Variables de entorno
#- Ejecuta echo con algunas $ variables como argumentos.
#- Verifica que $ se interpreta como una variable de entorno.
#- Verifica que las comillas dobles interpolan $.
#- Verifica que $USER existe o créalo.
#- echo "$USER" deberá imprimir el valor de $USER

echo $HOME
echo "$HOME"
echo '$HOME'
env | grep USER
echo $USER


echo -a -b "jamon"
exit                ----> leaks

' '?                ---> heap-buffer-overflow

