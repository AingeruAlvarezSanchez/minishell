#include "../../include/minishell.h"
#include <sys/wait.h>

/**
 * @param cmds struct with commands
 */
static void	ft_last_cmd(t_cmds_all *cmds)
{
	if (cmds->n_cmds == 2)
	{
		dup2(cmds->pipes[0], 0);
		close(cmds->pipes[1]);
		close(cmds->pipes[0]);
	}
	else
	{
		dup2(cmds->sngl_pipe, 0);
		close(cmds->pipes[1]);
		close(cmds->pipes[0]);
	}
}

/**
 *
 * @param pos_cmd command actual position
 * @param cmds struct with commands
 */
static void	ft_dupto_son(int pos_cmd, t_cmds_all *cmds)
{
	if (cmds->n_cmds == 0)
	{
		dup2(cmds->pipes[1], 1);
		close(cmds->pipes[0]);
		close(cmds->pipes[1]);
	}
	else if (pos_cmd == cmds->n_cmds - 1)
        ft_last_cmd(cmds);
	else
	{
		dup2(cmds->sngl_pipe, 0);
		dup2(cmds->pipes[1], 1);
		close(cmds->pipes[0]);
		close(cmds->pipes[1]);
	}
}

/**
 * @param env struct with environment
 * @param cmds struct with commands
 * @param pos_cmd command actual position
 */
static void	ft_child_ex(t_env *env, t_cmds_all *cmds, int pos_cmd)
{
	char	*aux;
	char	*aux2;

	if (cmds->n_cmds > 1)
		ft_dupto_son(pos_cmd, cmds);
	if (!ft_child_builtin(&cmds->cmds[pos_cmd], env))
		exit(0);
	if (cmds->cmds[pos_cmd].absolute)
		execve(cmds->cmds[pos_cmd].bin_path,
               cmds->cmds[pos_cmd].cmd, env->env);
    aux = ft_strjoin("/", cmds->cmds[pos_cmd].cmd[0]);
    aux2 = ft_strjoin(cmds->cmds[pos_cmd].bin_path, aux);
	if (!access(aux2, X_OK))
		execve(ft_strjoin(cmds->cmds[pos_cmd].bin_path,
                          ft_strjoin("/", cmds->cmds[pos_cmd].cmd[0])),
               cmds->cmds[pos_cmd].cmd, env->env);
	perror(cmds->cmds[pos_cmd].cmd[0]);
	free(aux);
	free(aux2);
}

/**
 * @param env struct with environment
 * @param cmds struct with commands
 * @param pos_cmd command actual position
 */
void	ft_exec_proc(t_cmds_all *cmds, t_env *env, int pos_cmd)
{
	int		status;
	pid_t	pid;

	ft_check_signal();
	pid = fork();
	if (pid == 0)
        ft_child_ex(env, cmds, pos_cmd);
	else
	{
		if (cmds->n_cmds > 1)
			close(cmds->pipes[1]);
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		if (cmds->n_cmds > 2)
		{
            cmds->sngl_pipe = dup(cmds->pipes[0]);
			close(cmds->pipes[0]);
			pipe(cmds->pipes);
		}
	}
}

/**
 * @param env struct with environment
 * @param cmds struct with commands
 * @return null if no path
 */
void	*ft_exec(t_cmds_all *cmds, t_env *env)
{	
	int		pos_cmd;

	if (ft_get_path(cmds, env))
		return (NULL);
	if (cmds->n_cmds > 1)
	{
        cmds->pipes = malloc(sizeof(int) * 2);
		pipe(cmds->pipes);
	}
    cmds->sngl_pipe = 3;
    pos_cmd = -1;
	while (++pos_cmd != cmds->n_cmds)
	{
		if (ft_parent_builtin(&cmds->cmds[pos_cmd], env, cmds->n_cmds, pos_cmd) || ft_is_exit(cmds, pos_cmd, cmds->n_cmds))
			continue ;
        ft_exec_proc(cmds, env, pos_cmd);
	}
    ft_free_exec(cmds);
	return (NULL);
}
