#include "../../include/minishell.h"

static char	**return_heaped_env(bool flag, char **str)
{
	char	**result;

	if (flag == 1)
		result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str)));
	else
		result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str) + 1));
	return (result);
}

char	**ft_dup_env(char **env)
{
	char	**nw_env;
	int		i;
	bool	flag;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
            flag = 1;
	}
    nw_env = return_heaped_env(flag, env);
	if (!nw_env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			env++;
		if (env[i])
            nw_env[i] = ft_strdup(env[i]);
	}
    nw_env[i] = 0;
	return (nw_env);
}
