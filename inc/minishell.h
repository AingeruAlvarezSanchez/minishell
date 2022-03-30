/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:08:14 by aalvarez          #+#    #+#             */
/*   Updated: 2022/03/29 16:07:10 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

typedef struct s_data
{
	char	**env;
	char	**path;
	int		last_out;
}	t_data;

typedef struct s_cmds
{
	pid_t	pid;
	char	**tokens;
	int		n_cmds;
}	t_cmds;

#endif
