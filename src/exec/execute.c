#include "../../include/minishell.h"
#include <sys/wait.h>

static void	ft_last_command(t_cmds_all *table)
{
	if (table->n_cmds == 2)
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

static void	dup_son_choose(int i, t_cmds_all *table)
{
	if (table->n_cmds == 0)
	{
		dup2(table->pi[1], 1);
		close(table->pi[0]);
		close(table->pi[1]);
	}
	else if (i == table->n_cmds - 1)
		ft_last_command(table);
	else
	{
		dup2(table->unipipe, 0);
		dup2(table->pi[1], 1);
		close(table->pi[0]);
		close(table->pi[1]);
	}
}

void	ft_childexec(t_env *msh, t_cmds_all *table, int i)
{
	char	*tmp;
	char	*tmp2;

	if (table->n_cmds > 1)
		dup_son_choose(i, table);
	if (!ft_child_builtin(&table->cmds[i], msh))
		exit(0);
	if (table->cmds[i].is_absolute)
		execve(table->cmds[i].bin_path,
               table->cmds[i].cmd, msh->env);
	tmp = ft_strjoin("/", table->cmds[i].cmd[0]);
	tmp2 = ft_strjoin(table->cmds[i].bin_path, tmp);
	if (!access(tmp2, X_OK))
		execve(ft_strjoin(table->cmds[i].bin_path,
				ft_strjoin("/", table->cmds[i].cmd[0])),
               table->cmds[i].cmd, msh->env);
	perror(table->cmds[i].cmd[0]);
	free(tmp);
	free(tmp2);
}

void	ft_exec_proccess(t_cmds_all *table, t_env *msh, int i)
{
	pid_t	pid;
	int		status;

	ft_check_signal();
	pid = fork();
	if (pid == 0)
		ft_childexec(msh, table, i);
	else
	{
		if (table->n_cmds > 1)
			close(table->pi[1]);
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		if (table->n_cmds > 2)
		{
			table->unipipe = dup(table->pi[0]);
			close(table->pi[0]);
			pipe(table->pi);
		}
	}
}

void	*execute(t_cmds_all *table, t_env *msh)
{	
	int		i;

	if (gather_bin_path(table, msh))
		return (NULL);
	if (table->n_cmds > 1)
	{
		table->pi = malloc(sizeof(int) * 2);
		pipe(table->pi);
	}
	table->unipipe = 3;
	i = -1;
	while (++i != table->n_cmds)
	{
		if (ft_parent_builtin(&table->cmds[i],
                              msh, table->n_cmds, i)
			|| ft_isexit(table, i, table->n_cmds))
			continue ;
		ft_exec_proccess(table, msh, i);
	}
	close_and_liberate_execution(table);
	return (NULL);
}
