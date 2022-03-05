/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:08:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/03 20:00:14 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	**env;
	char	**path;
}	t_data;

typedef struct s_cmds
{
	pid_t	pid;
	char	**commands;
	char	**p_command;
	int	n_cmds;
	int	**pipefds;
}	t_cmds;

/* builtin functions */
void	ft_check_echo(t_cmds *Cmds);
void	ft_pwd(void);
void	ft_env(t_data *Data);
void	ft_cd(t_cmds *Cmds, t_data *Data);
void	ft_exit(void);
void	ft_check_export(t_data *Data, t_cmds *Cmds);
void	ft_check_unset(t_data *Data, t_cmds *Cmds);
/* Command execution functions */
void	ft_commands(char *str, t_cmds *Cmds, t_data *Data);
void	ft_init_exec(t_cmds *Cmds, t_data *Data);
char	*ft_manage_quotes(char *command);

#endif
