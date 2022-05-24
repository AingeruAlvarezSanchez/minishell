/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 05:41:11 by aalvarez          #+#    #+#             */
/*   Updated: 2022/05/24 12:11:03 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../libft/libft.h"

# define WRITE 1
# define READ 0

typedef struct s_data {
    char    **env;
    char    **paths;
    int     last_out;
}   t_data;

typedef struct s_cmds {
    char    *prompt;
    char    *token_value;
    char    **tokens;
    
    int     n_cmds;
    char    **binary;
    char    ***command;

    pid_t	pid;
    int     **pipefd;
    int     redir_flag;//*redir_flag
    int     redir_fd;
    
}   t_cmds;

/* Initials */
void    ft_cpyenv(char **envp, t_data *data);
void    ft_initcmds(t_cmds *cmds);
void	ft_create_pipes(t_cmds *cmds);

/* Errors handling fucntions */
int ft_has_final(t_cmds *cmds, int xref, char c);
int  ft_pipes_error(char *prompt, char *sp);

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
int ft_pipes(t_cmds *cmds, int xref, char *sp);
int	ft_is_pipe_or_redir(char c);

/* Join after checking special chars */
void ft_lastjoin(t_cmds *cmds);

/* Dollar expanding function */
void    ft_dollars(t_cmds *cmds, t_data *data);

/* parsing */
void ft_parsing(t_cmds *cmds);

/* builtins */
void	ft_exit(char *flag, t_data *data, int cmd_n);
void	ft_cd(char *flag, t_data *data, int cmd_pos);
void	ft_check_export(char **command, t_data *data, int cmd_n);
void	ft_check_unset(char **command, t_data *data, int cmd_n);

/* utils */
void    print_bi_array(char **arr, char *text);
char    **copy_doble_array(char **arr);

/* execute*/
void	ft_create_forks(t_cmds *cmds, t_data *data, int pos);

/*signals*/
void	ft_signals(void);
int     ft_interactive(int inter);
void	ft_signal_exit(t_data *data, t_cmds *cmds);

#endif