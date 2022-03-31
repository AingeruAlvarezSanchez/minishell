#include "../inc/minishell.h"
#include <stdio.h>
 
/* This function checks wheter after the found quote there are any other quotes,
if there aren't any other closing quotes, the program returns to prompt state */
int	ft_quote_error(t_cmds *cmds, int iref, int jref, int quote)
{
	if (quote == 0)
	{
		while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != '\'')
			jref++;
		if (cmds->tokens[iref][jref] != '\'')
		{
			printf("Syntax error, unclosed quotes\n");
			return (-1);
		}
	}
	else if (quote == 1)
	{
		while (cmds->tokens[iref][jref] && cmds->tokens[iref][jref] != '"')
			jref++;
		if (cmds->tokens[iref][jref] != '"')
		{
			printf("Syntax error, unclosed quotes\n");
			return (-1);
		}
	}
	return (jref);
}

/* This function is only called if after the last quote there are other characters,
this exist for memory assign efficiency */
static char    **ft_full_final( t_cmds *cmds, char **tmp, int iref, int i, int quote)
{
    int	j;
    int jref;

	while (cmds->tokens[++i])
		tmp[i] = ft_strdup(cmds->tokens[i]);
	j = 0;
	if (quote == 0)
	{
		while (tmp[iref][j] != '\'')
			j++;
        jref = j + 1;
        while (tmp[iref][jref] != '\'')
            jref++;
	}
	else if (quote == 1)
	{
		while (tmp[iref][j] != '"')
			j++;
        jref = j + 1;
        while (tmp[iref][jref] != '"')
            jref++;
	}
	tmp[iref] = ft_substr(cmds->tokens[iref], 0, j);
	tmp[iref + 1] = ft_substr(cmds->tokens[iref], j, (jref - (j - 1)));
	tmp[iref + 2] = ft_substr(cmds->tokens[iref], (jref + 1), ft_strlen(cmds->tokens[iref]));
    tmp[iref + 3] = 0;
	ft_doublefree(cmds->tokens);
	return (tmp);
}

/* This function is only called if after the last quote there are no other characters,
this exist for memory assign efficiency */
static char	**ft_empty_final(t_cmds *cmds, char **tmp, int iref, int i, int quote)
{
	int	j;

	while (cmds->tokens[++i])
		tmp[i] = ft_strdup(cmds->tokens[i]);
	j = 0;
	if (quote == 0)
	{
		while (tmp[iref][j] != '\'')
			j++;
	}
	else if (quote == 1)
	{
		while (tmp[iref][j] != '"')
			j++;
	}
	tmp[iref] = ft_substr(cmds->tokens[iref], 0, j);
	tmp[iref + 1] = ft_substr(cmds->tokens[iref], j, ft_strlen(cmds->tokens[iref]));
	tmp[iref + 2] = 0;
	j = -1;
	ft_doublefree(cmds->tokens);
	return (tmp);
}

/* This function recreates the result of tmp on the cmds->tokens structure component */
static void	ft_newcmds(t_cmds *cmds, char **tmp)
{
    int i;

	cmds->tokens = (char **)malloc(sizeof(char *) * (ft_doublestrlen(tmp) + 1));
	i = -1;
	while (tmp[++i])
		cmds->tokens[i] = ft_strdup(tmp[i]);
	cmds->tokens[i] = 0;
}

/* This function manages both simple and multiple quotes */
void	ft_quotes(t_cmds *cmds, int iref, int jref, int quote)
{
	char	**tmp;
	int		i;

	i = -1;
	if (cmds->tokens[iref][jref + 1])
	{
		tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 3));
		if (quote == 0)
			tmp = ft_full_final(cmds, tmp, iref, i, 0);
		else if (quote == 1)
			tmp = ft_full_final(cmds, tmp, iref, i, 1);
	}
	else
	{
		tmp = (char **)malloc(sizeof(char *) * (ft_doublestrlen(cmds->tokens) + 2));
		if (quote == 0)
			tmp = ft_empty_final(cmds, tmp, iref, i, 0);
		else if (quote == 1)
			tmp = ft_empty_final(cmds, tmp, iref, i, 1);
	}
	ft_newcmds(cmds, tmp);
	ft_doublefree(tmp);
}
