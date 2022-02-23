#include "../minishell.h"

/*Este builtin solo funciona dentro del programa de minishell, sino,
chdir retorna la shell, sin cambiar de directorio, porque chdir crea un
subproceso para esta tarea, y al morir, ya no hace nada */
void	ft_cd(char *str)
{
	if (!chdir(str))
		printf("cd: %s:\n", perror(str));
}

