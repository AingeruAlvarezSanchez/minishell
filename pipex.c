#include "minishell.h"

void	ft_routes(char **envp, t_cmds *cmds)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	envp[i] = ft_strtrim(envp[i], "PATH=");
	cmds->route = ft_split(envp[i], ':');
	i = 0;
	while (cmds->route[i])
	{
		cmds->tmp = ft_strjoin(cmds->route[i], "/");
		free(cmds->route[i]);
		cmds->route[i] = cmds->tmp;
		i++;
	}
}

void	ft_memory_assign(t_cmds *cmds, t_fds *fds, char **str, int argc)
{
	int	i;

	i = 0;
	fds->pipefd = (int **) malloc ((cmds->n_cmds + 1) * sizeof (int *));
	while (i < cmds->n_cmds + 1)
	{
		fds->pipefd[i] = (int *) malloc (2 * sizeof(int));
		pipe(fds->pipefd[i]);
		i++;
	}
	fds->pid = (int *) malloc (cmds->n_cmds * sizeof(int));
	close(fds->pipefd[0][0]);
	fds->pipefd[0][0] = open(str[1], O_RDONLY);
	close(fds->pipefd[cmds->n_cmds][1]);
	fds->pipefd[cmds->n_cmds][1] = open(str[argc - 1],
			O_RDWR | O_TRUNC | O_CREAT, 0777);
}

void	ft_execute(t_cmds cmds, int signal, int j, char **envp)
{
	while (cmds.route[j])
	{
		cmds.tmp2 = ft_strjoin(cmds.route[j], cmds.command[0]);
		access(cmds.tmp2, X_OK);
		if (signal == -1)
			free(cmds.tmp2);
		else
			execve(cmds.tmp2, cmds.command, envp);
		j++;
	}
	exit (0);
}

void	ft_init_execute(t_cmds cmds, t_fds fds, char **str, char **envp)
{
	int	j;
	int	signal;

	j = 0;
	signal = 0;
	while (j < cmds.n_cmds + 1)
	{
		if (j != cmds.i)
			close(fds.pipefd[j][0]);
		if (j != cmds.i + 1)
			close(fds.pipefd[j][1]);
		j++;
	}
	dup2(fds.pipefd[cmds.i][0], 0);
	dup2(fds.pipefd[cmds.i + 1][1], 1);
	close(fds.pipefd[cmds.i][0]);
	close(fds.pipefd[cmds.i + 1][1]);
	cmds.command = ft_split(str[cmds.cnum], ' ');
	j = 0;
	ft_execute(cmds, signal, j, envp);
}

int	pipex(int argc, char **str, char **envp)
{
	t_cmds	cmds;
	t_fds	fds;

	cmds.i = 0;
	cmds.cnum = 2;
	cmds.n_cmds = argc - 3;
	ft_routes(envp, &cmds);
	ft_memory_assign(&cmds, &fds, str, argc);
	while (cmds.i < cmds.n_cmds)
	{
		fds.pid[cmds.i] = fork();
		if (fds.pid[cmds.i] == 0)
			ft_init_execute(cmds, fds, str, envp);
		cmds.cnum++;
		cmds.i++;
	}
	return (0);
}
