#include "minishell.h"

void	ft_commands_n(char *str, t_cmds *Cmds)
{
	int	i;

	i = -1;
	Cmds->n_cmds = 1;
	while (str[++i])
	{
		if (str[i] == '|')
			Cmds->n_cmds++;
	}
}

void	ft_fill_commands(char *str, t_cmds *Cmds)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			check = 1;
	}
	i = -1;
	if (check == 1)
	{
		Cmds->commands = ft_split(str, '|');
		while (Cmds->commands[++i])
			Cmds->commands[i] = ft_strtrim(Cmds->commands[i], " ");
	}
	else
	{
		Cmds->commands[0] = str;
		Cmds->commands[1] = NULL;
	}
}

void	ft_execute(t_data *Data, t_cmds *Cmds, char *command)
{
	char * tmp;
	int i;
	
	i = -1;
	Cmds->p_command = ft_split(command, ' ');
	if (!Cmds->p_command[0])
		exit (0);	
	while (Data->path[++i])
	{
		tmp = ft_strjoin(Data->path[i], Cmds->p_command[0]);
		if (access(tmp, X_OK) == 0)
			execve(tmp, Cmds->p_command, Data->env);
		free(tmp);
	}
	printf("%s: Command not found\n", Cmds->p_command[0]);
	exit(0);
}

void	ft_init_exec(t_cmds *Cmds, t_data *Data)
{
	int	i;

	i = 0;
	while (i < Cmds->n_cmds)
	{
		Cmds->pid = fork();
		if (Cmds->pid == 0)
			ft_execute(Data, Cmds, Cmds->commands[i]);
		i++;
	}
}

void	ft_commands(char *str, t_cmds *Cmds, t_data *Data)
{
	ft_commands_n(str, Cmds);
	ft_fill_commands(str, Cmds);
	ft_init_exec(Cmds, Data);
}

