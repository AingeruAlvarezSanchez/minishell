#include "../inc/minishell.h"

/* This function creates the string to search on the environment */
static char	*ft_tofind(t_cmds *cmds, int iref, int jref)
{
	char	*to_find;
	int		j;
	int		reference;

	j = 0;
	reference = jref + 1;
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
	{
		jref++;
		j++;
	}
	to_find = (char *)malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (reference < jref)
	{
		to_find[j] = cmds->tokens[iref][reference];
		j++;
		reference++;
	}
	to_find[j] = 0;
	to_find = ft_strtrim(to_find, "\"");
	to_find = ft_strjoin(to_find, "=");
	return (to_find);
}

/* This function is only called if the value inside the dollar is actually in
the environment variable, it isn't used otherwise */
static void	ft_dollar_value(t_cmds *cmds, char *to_find, int iref, int jref)
{
	char	**tmp;
	char	*tmp2;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 1));
	i = -1;
	while (cmds->tokens[++i])
		tmp[i] = ft_strdup(cmds->tokens[i]);
	tmp[i] = 0;
	tmp2 = ft_substr(tmp[iref], 0, jref);
	tmp2 = ft_strjoin(tmp2, to_find);
	tmp2 = ft_strtrim(tmp2, "\"");
	while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
		jref++;
	tmp[iref] = ft_substr(tmp[iref], jref, ft_strlen(tmp[iref]));
	tmp[iref] = ft_strjoin(tmp2, tmp[iref]);
	ft_doublefree(cmds->tokens);
	i = -1;
	cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 1));
	while (tmp[++i])
		cmds->tokens[i] = ft_strdup(tmp[i]);
	cmds->tokens[i] = 0;
	ft_doublefree(tmp);
	free(tmp2);
}

/* This function is only called if the value inside the dollar
is not inside the environment varible, it changes the dollar value
to null, exactly like in bash */
static void ft_dollar_no_value(t_cmds *cmds, int iref, int jref)
{
    char    *tmp;

    tmp = ft_substr(cmds->tokens[iref], 0, jref);
    while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != ' ')
        jref++;
    cmds->tokens[iref] = ft_substr(cmds->tokens[iref], jref, ft_strlen(cmds->tokens[iref]));
    tmp = ft_strjoin(tmp, cmds->tokens[iref]);
	tmp = ft_strtrim(tmp, "\"");
    free(cmds->tokens[iref]);
    cmds->tokens[iref] = ft_strdup(tmp);
    free(tmp);
}

/* This function is the entrance to checking all the possibilites for the $
caracter, that means expansion for environment variable or last status */
void	ft_check_dollar(t_cmds *cmds, t_data *data, int iref, int jref)
{
	char	*to_find;
	int		i;

	if (!cmds->tokens[iref][jref + 1])
		return ;
	//if (cmds->tokens[iref][jref + 1] == '?')
		//ft_last_status();
	to_find = ft_tofind(cmds, iref, jref); 
	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], to_find, ft_strlen(to_find)))
		{
			to_find = ft_substr(data->env[i], ft_strlen(to_find), ft_strlen(data->env[i]));
			ft_dollar_value(cmds, to_find, iref, jref);
			free(to_find);
			return ;
		}
	}
	free(to_find);
	ft_dollar_no_value(cmds, iref, jref);
}