#include "../../include/minishell.h"
#include <sys/wait.h>

static void	ft_last_command(t_command_table *table)
{
	if (table->cmd_count == 2)
	{
		dup2(table->pi[0], 0);
		close(table->pi[1]);
		close(table->pi[0]);
	}
	else
	{
		dup2(table->unipipe, 0);
		close(table->pi[1]);
		close(table->pi[0]);
	}
}

static void	dup_son_choose(int i, t_command_table *table)
{
	if (table->cmd_count == 0)
	{
		dup2(table->pi[1], 1);
		close(table->pi[0]);
		close(table->pi[1]);
	}
	else if (i == table->cmd_count - 1)
		ft_last_command(table);
	else
	{
		dup2(table->unipipe, 0);
		dup2(table->pi[1], 1);
		close(table->pi[0]);
		close(table->pi[1]);
	}
}

void	ft_childexec(t_msh_var *msh, t_command_table *table, int i)
{
	char	*tmp;
	char	*tmp2;

	if (table->cmd_count > 1)
		dup_son_choose(i, table);
	if (!ft_child_builtin(&table->commands[i], msh))
		exit(0);
	if (table->commands[i].is_absolute)
		execve(table->commands[i].bin_path,
			table->commands[i].command, msh->own_envp);
	tmp = ft_strjoin("/", table->commands[i].command[0]);
	tmp2 = ft_strjoin(table->commands[i].bin_path, tmp);
	if (!access(tmp2, X_OK))
		execve(ft_strjoin(table->commands[i].bin_path,
				ft_strjoin("/", table->commands[i].command[0])),
			table->commands[i].command, msh->own_envp);
	perror(table->commands[i].command[0]);
	free(tmp);
	free(tmp2);
}

void	ft_exec_proccess(t_command_table *table, t_msh_var *msh, int i)
{
	pid_t	pid;
	int		status;

	ft_check_signal();
	pid = fork();
	if (pid == 0)
		ft_childexec(msh, table, i);
	else
	{
		if (table->cmd_count > 1)
			close(table->pi[1]);
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		if (table->cmd_count > 2)
		{
			table->unipipe = dup(table->pi[0]);
			close(table->pi[0]);
			pipe(table->pi);
		}
	}
}

void	*execute(t_command_table *table, t_msh_var *msh)
{	
	int		i;

	if (gather_bin_path(table, msh))
		return (NULL);
	if (table->cmd_count > 1)
	{
		table->pi = malloc(sizeof(int) * 2);
		pipe(table->pi);
	}
	table->unipipe = 3;
	i = -1;
	while (++i != table->cmd_count)
	{
		if (ft_parent_builtin(&table->commands[i],
				msh, table->cmd_count, i)
			|| ft_isexit(table, i, table->cmd_count))
			continue ;
		ft_exec_proccess(table, msh, i);
	}
	close_and_liberate_execution(table);
	return (NULL);
}
