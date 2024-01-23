/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:35:04 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 17:33:34 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include <readline/history.h> //check if it is a must for readline
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <wait.h>
# include "includes/structures.h"
# include "includes/builtins.h"
# include "includes/get_next_line.h"
# include "includes/parser.h"
# include "libft/libft.h"

# define PROPMPT_MSG "\033[1;36mminishell\033[34m$ \033[0m"
# define ERR_ARGS "\033[1;31mERROR: Minishell does not accept arguments\033[0m\n"

# define BUFF_SIZE (SIZE_MAX)

extern int	g_exit_status;

int			syntax_error(char *line);
/*******environment*******/
bool		is_valid_var(char *var);
bool		is_valid_var_unset(char *var);
void		init_tools(t_tools *tools, char *envp[]);
t_env		**cpy_chl_env(char *envp[]);
char		**cpy_arr_env(char *envp[]);
char		*get_variable_path(char *arr_env[]);
t_env		*get_env_variable(t_env **chl_env, char *var);
// char	*get_absolute_path(char **cmd_args, char *arr_env[]);
char		*get_absolute_path(char **cmd_args, t_tools *tools);
int			create_restricted_env(t_tools *tools);
t_env		*set_env_var(char *cmd_arg);
void		add_vars(t_tools *tools);

/*     SIGNAL     */
void		sig_ctrlc(int sig);

/***********MINISHELL************/
int			minishell_loop(t_tools *tools);

/****to be deleted*******/
void		print_list(t_env *env_l);

/*******safe exit***********/
void		free_table(char **tab);
void		free_env_list(t_env **env);
void		free_tools(t_tools *tools);

void		free_cmd_line_all(t_tools *tools);
// void		free_cmd_line_all(t_pre_execcmd *cmd_line);
void		free_exec(t_exec *exec);

void		ft_exit(t_tools *tools, long long int i);

/******builtins**************/

/*parsing*/
void		from_sub_to_pre(t_tools *tools);

/*formatting exec*/

t_exec		*format_exec(t_pre_execcmd *node);
int			open_all_keep_last_in(t_exec *exec, t_pre_execcmd *node);
int			open_all_keep_last_out(t_pre_execcmd *node);
int			create_execution_list(t_tools *tools);
void		print_exec(t_exec **exec);

/*execution*/
void		exec_child(t_tools *tools, t_exec *temp, int i);
// void	exec_child(t_tools *tools, t_pre_execcmd *temp, t_exec *exec, int i);
void		exec_simple_cmd(t_exec *exec, t_tools *tools);
int			exec_simple_builtin(t_exec *exec, t_tools *tools);
void		exec_builtin(t_exec *exec, t_tools *tools);
// void	exec_cmd(t_exec *exec, t_tools *tools);
int			exec_multi_cmds(t_tools *tools);
int			execute(t_tools *tools);
/*files*/

void		ft_close(int *fd);

int			get_input_file(char *file);

/*exit status*/
int			exit_status(pid_t last_pid);

/*heredocument*/

int			get_heredoc_input_file(char *heredoc_filename, char *delim);
void		exec_here_doc(int fd, char *delim);
char		*generate_heredoc_filename(void);

/*pipes*/

bool		init_pipes(t_tools *tools);
bool		set_pipes(t_tools *tools, t_exec *exec, int i);
bool		close_pipes(t_tools *tools, t_exec *exec, int i);

/*redirections*/

bool		save_std_io(t_tools *tools);
bool		restore_io(t_tools *tools, t_exec *exec);
bool		redirect_io(t_tools *tools, t_exec *exec);

/*path*/
char		*get_cmd_path(char *arg, char **arr_env);

/*errors*/
int			invalid_option(char *cmd_arg);
int			err_msg_cmd(char *cmd, char *detail, int error_nb);
int			err_msg_exit(char *cmd, char *detail1, char *detail2, int error_nb);
int			err_msg(char *cmd, char *detail1, char *detail2, int error_nb);

#endif
