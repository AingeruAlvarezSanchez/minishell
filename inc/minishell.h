#ifndef MINISHELL_H
#define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

# define WRITE 1
# define READ 0

typedef struct s_data {
    char    **env;
    char    **paths;
    int     last_out;
}   t_data;

typedef struct s_cmds {
    char    **tokens;
    int     n_cmds;

    char    **binary;
    char    **flags;
    char    **command;
    char    *after_cmd;

    pid_t	pid;
    int     **pipefd;
}   t_cmds;




/* Inital checks and memory allocation functions */
void    ft_cpyenv(t_data *data, char **envp);
void    ft_initcmds(char *prompt, t_cmds *cmds);

/* Functions to check various errors */
int     ft_has_final(t_cmds *cmds, int iref, int jref, int c);
int     ft_pipes_error(t_cmds *cmds, int iref, int jref);
void    ft_nonulls(t_cmds *cmds);

/* Functions to manage special characters*/
int	    ft_has_special_char(t_cmds *cmds);
void	ft_newcmds(t_cmds *cmds, char **tmp);

/* Quote managing functions */
void    ft_quotes(t_cmds *cmds, int iref, int jref, int xref);

/* Pipes managing functions */
int     ft_check_pipes(t_cmds *cmds, int iref, int jref);

/* Dollar managing functions */
void    ft_check_metacharacter(t_cmds *cmds, t_data *data);
void    ft_check_dollar(t_cmds *cmds, t_data *data, int iref, int jref);

/* parsing */
//void	ft_check_builtins(t_cmds *cmds, t_data *data)
void ft_parsing(t_cmds *cmds);

/* builtins */
void	ft_exit(char *flag, t_data *data, int cmd_n);
void	ft_cd(char *flag, t_data *data, int cmd_pos);
//void	ft_check_export(t_cmds *cmds, t_data *data, int cmd_n);
//void	ft_check_unset(t_cmds *cmds, t_data *data, int cmd_n);

/* utils */
void print_bi_array(char **arr, char *text);
char **copy_doble_array(char **arr);

#endif