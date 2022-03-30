/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:06:39 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/29 16:53:05 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/* This function is used to create a copy of the environment in the data structure */
void	ft_cpyenv(t_data *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	data->env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = 0;
}

 /* This function is used to create a copy of the PATH variable onto the data structure */
void	ft_get_path(t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (ft_strncmp(data->env[i], "PATH=", 5))
		i++;
	tmp2 = ft_strtrim(data->env[i], "PATH=");
	data->path = ft_split(tmp2, ':');
	i = 0;
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		free(data->path[i]);
		data->path[i] = tmp;
		i++;
	}
	free (tmp2);
	free (tmp);
}

/* This function reshape the "tokens" member of cmds in order to adapt it to simple quotes needs */
void	ft_simple_quotes(__attribute__((unused)) t_cmds *cmds,__attribute__((unused)) int iref,__attribute__((unused)) int jref)
{
	int	i;

	i = -1;
	while (cmds->tokens[++i])
		printf("CMD: %s\n", cmds->tokens[i]);
}

/* needed to search for a way to make this function smaller to norminette */
void	ft_commands(char *prompt, t_cmds *cmds, __attribute__((unused)) t_data *data)
{
	int	j;
	
	cmds->tokens = (char **)malloc(sizeof(char *) * 2);
	cmds->tokens[0] = ft_strdup(prompt);
	cmds->tokens[1] = 0;
	cmds->n_cmds = 1;
	j = -1;
	while (cmds->tokens[0][++j])
	{
		if (cmds->tokens[0][j] == '\'')
		{
			j++;
			//ft_simple_quotes(cmds, i, j);
			while (cmds->tokens[0][j] && cmds->tokens[0][j] != '\'')
				j++;
			if (cmds->tokens[0][j] != '\'')
			{
				printf("Syntax error, unclosed quotes\n");
				return ;
			}
		}
		else if (cmds->tokens[0][j] == '"')
		{
			//ft_double_quotes(cmds);
			j++;
			while (cmds->tokens[0][j] && cmds->tokens[0][j] != '"')
			{
				if (cmds->tokens[0][j] == '$')
					printf("i found a dollar inside double quotes\n");
					//ft_dollar(cmds, data);
				j++;
			}
			if (cmds->tokens[0][j] != '"')
			{
				printf("Syntax error, unclosed quotes\n");
				return ;
			}
		}
		/*else if (cmds->tokens[0][j] == '$')
		{
			//ft_dollar(cmds, data);
		}*/
		else if (cmds->tokens[0][j] == '|')
			cmds->n_cmds++;
	}
	printf("Cmd num: %d\n", cmds->n_cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_cmds	cmds;
	t_data	data;

	data.last_out = 0;
	ft_cpyenv(&data, envp);
	ft_get_path(&data);
	while (1 && argc && argv)
	{	
		prompt = readline("ejemplo1 ₺ ");
		add_history(prompt);
		ft_commands(prompt, &cmds, &data);
		waitpid(Cmds.pid, NULL, WUNTRACED);
		free(prompt);
	}
	return (0);
}
