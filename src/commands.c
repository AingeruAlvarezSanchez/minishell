#include "../inc/minishell.h"

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
		Cmds->commands[0] = ft_manage_quotes(str);
		Cmds->commands[1] = NULL;
	}
}

void	ft_ischild_builtin(t_cmds *Cmds, t_data *Data)
{
	if (!ft_strncmp(Cmds->p_command[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(Cmds->p_command[0], "echo", 4))
		ft_check_echo(Cmds);
	else if (!ft_strncmp(Cmds->p_command[0], "env", 3))
		ft_env(Data);
}

void	ft_isparent_builtin(t_cmds *Cmds, t_data *Data)
{
	int 	i;

	i = -1;
	Cmds->p_command = ft_split(Cmds->commands[0], ' ');
	if (!Cmds->p_command[0])
	{
		while(Cmds->p_command[++i])
			free(Cmds->p_command[i]);
		free(Cmds->p_command);
		return ;
	}
	if (!ft_strncmp(Cmds->p_command[0], "cd", 2))
		ft_cd(Cmds, Data);
	else if (!ft_strncmp(Cmds->p_command[0], "exit", 4)) 
		ft_exit();
	if (Cmds->p_command)
	{
		while(Cmds->p_command[++i])
			free(Cmds->p_command[i]);
		free(Cmds->p_command);
	}
}

void	ft_execute(t_data *Data, t_cmds *Cmds, char *command)
{
	char	*tmp;
	int 	i;
	
	i = -1;
	Cmds->p_command = ft_split(command, ' ');
	if (!Cmds->p_command[0])
		exit (0);	
	if (!ft_strncmp(Cmds->p_command[0], "cd", 2))
		exit (0);
	ft_ischild_builtin(Cmds, Data);
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
	ft_isparent_builtin(Cmds, Data);
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

