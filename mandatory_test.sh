

make -n

#Comados simples y la variable global
/bin/ls
/bin/pwd
/bin/env
comando vacio
espacios
tabulacion

#Argumentos e historial
/bin/ls -l

#echo
echo
echo -n abcdefghijk
echo -E 12324215
echo -e 12324215

#exit
exit 1
exit 0
exit 12324215125214123123
exit -12324215125214123123

#Valor de retorno de un proceso
/bin/ls
echo $?

/bin/ls archivo_que_no_existe
echo $?

expr $? + $?

#Comillas dobles
echo "cat lol.c | cat > lol.c"
echo "ls -l | grep e"
" "
""

#Comillas simples
' '
'$HOME '
'ls -l | grep e'
'cat lol.c | cat > lol.c'

#enviroment
env

#export
export a = 5

#unset