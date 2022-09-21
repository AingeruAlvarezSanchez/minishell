#include "../../include/minishell.h"

/**
 * brief gets binary path
 * @param cmds struct with commands
 * @param env struct with environment
 * @return true if path is null
 */
bool	ft_get_path(t_cmds_all *cmds, t_env *env)
{
	int		pos_cmd;

    pos_cmd = -1;
	while (++pos_cmd != cmds->n_cmds)
	{
        cmds->cmds[pos_cmd].bin_pth = ft_bin_path(&cmds->cmds[pos_cmd], env);
		if (!ft_checkparent(&cmds->cmds[pos_cmd]))
		{
			if (pos_cmd == cmds->n_cmds - 1)
				return (ft_final_cmd(cmds, pos_cmd, cmds->n_cmds, env));
			continue ;
		}
		if (cmds->cmds[pos_cmd].bin_pth == NULL)
		{
			if (ft_check_access(cmds, pos_cmd))
				continue ;
			printf("%s %s %s", "Minishell :", cmds->cmds[pos_cmd].cmd[0],
                   ": cmd not found\n");
            g_exit = 127;
			ft_free_commands(cmds);
			return (1);
		}		
	}
	return (0);
}

bool	ft_check_path(const char *path, char *binary)
{
	DIR				*dp;
	struct dirent	*dirp;

	dp = opendir(path);
	if (dp != NULL)
	{
		dirp = readdir(dp);
		while (dirp != NULL)
		{
			if (ft_str_has(dirp->d_name, binary))
			{
				closedir(dp);
				return (1);
			}
			dirp = readdir(dp);
		}
		closedir(dp);
	}
	return (0);
}

static void ft_init_path(t_cmd *cmd, t_env *env)
{
	int	i;

    cmd->path = ft_rewrite_path(env);
    cmd->absolute = false;
    ft_strtolower(cmd->cmd[0]);
	i = -1;
	while (cmd->cmd[++i])
		ft_trim_algorithm(cmd, i);
}

/**
 * @param env struct with environemnt
 * @return the new path
 */
char	**ft_rewrite_path(t_env *env)
{
	int		i;
	char	*aux;
	char	**aux2;
	char	**path;

	i = 0;
	while (env->env && env->env[++i])
	{
		if (env->env[i] && ft_str_contains(env->env[i], "PATH="))
		{
            aux = ft_strdup(env->env[i]);
            aux2 = ft_split(aux, '=');
			path = ft_split(aux2[1], ':');
			free(aux);
			ft_doublefree(aux2);
			return (path);
		}
	}
	return (NULL);
}

/**
 * @param cmd struct with command
 * @param env struct with environment
 * @return path of the binary
 */
char	*ft_bin_path(t_cmd *cmd, t_env *env)
{	
	int		pos;
	char	*binary;

    ft_init_path(cmd, env);
    pos = 0;
	if (cmd->path)
	{
		while (cmd->path[pos])
		{
			if (ft_check_path(cmd->path[pos], cmd->cmd[0]))
				return (ft_cpy_path(cmd, pos));
            cmd->path[pos] = NULL;
			pos++;
		}
		if (access(cmd->cmd[0], X_OK) == 0)
		{
            binary = ft_strdup(cmd->cmd[0]);
            cmd->absolute = true;
			return (binary);
		}
	}
	if (cmd->path)
		ft_doublefree(cmd->path);
	return (NULL);
}
