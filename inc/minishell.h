/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 05:41:11 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/20 01:34:13 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../libft/libft.h"

typedef struct s_data {
    char    **env;
    char    **paths;
}   t_data;

typedef struct s_cmds {
    char    *prompt;
    char    *token_value;
    char    **tokens;
}   t_cmds;

/* Initials */
void    ft_cpyenv(char **envp, t_data *data);
void    ft_initcmds(t_cmds *cmds);

/* Errors handling fucntions */
int ft_has_final(t_cmds *cmds, int xref, char c);
int  ft_pipes_error(t_cmds *cmds, int xref);

/* Special chars */
int	ft_is_special_char(char c);
int ft_has_special_char(t_cmds *cmds);

/* First case function */
void ft_check_first(t_cmds *cmds);

/* Quotes managing function */
int  ft_quotes(t_cmds *cmds, int xref, char c);
int  ft_composed_quotes_ref(t_cmds *cmds, int xref);
int  ft_composed_quotes_len(t_cmds *cmds, int xref);

/* Quotes managing function */
int ft_pipes(t_cmds *cmds, int xref);

/* Join after checking special chars */
void ft_lastjoin(t_cmds *cmds);

/* Dollar expanding function */
void    ft_dollars(t_cmds *cmds, t_data *data);

#endif