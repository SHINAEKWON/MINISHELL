/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:52:51 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 17:17:04 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../minishell.h"

typedef struct s_env
{
	char						*key;
	char						*value;
	char						*k_eq_v;
	struct s_env				*next;
}								t_env;

typedef struct s_quote
{
	bool						in_dq;
	bool						in_sq;
}								t_quote;

enum							e_type_token
{
	UNPARSED,
	WORD,
	SQ,
	DQ,
	CMD,
	INPUT_FILE,
	OUTPUT_FILE,
	OUTPUT_FILE_APPEND,
	PIPE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	HEREDOC,
	HEREDOC_DELIM,
	REDIR_OUTPUT_APPEND,
	NUM_TYPES
};

typedef struct s_cmd
{
	char						*token;
	enum e_type_token			type;
	struct s_cmd				*next;
	struct s_cmd				*previous;
}								t_cmd;

typedef struct s_cmdpos
{
	size_t						start;
	size_t						end;
	struct s_cmdpos				*next;
}								t_cmdpos;

typedef struct s_cmdpos_elem
{
	size_t						start_pos;
	bool						started;
	bool						in_dq;
	bool						in_sq;
}								t_cmdpos_elem;

typedef struct s_pre_execcmd
{
	char						*cmd;
	struct s_sub_pre_execcmd	*redir_in;
	struct s_sub_pre_execcmd	*redir_out;
	struct s_sub_pre_execcmd	*argument;
	struct s_pre_execcmd		*next;
}								t_pre_execcmd;

typedef struct s_sub_pre_execcmd
{
	char						*content;
	int							type;
	struct s_sub_pre_execcmd	*next;
}								t_sub_pre_execcmd;

typedef struct s_envvar_elem
{
	char						*content;
	char						*translated_value;
	struct s_envvar_elem		*next;
}								t_envvar_elem;

typedef struct s_exec
{
	int							fd_in;
	int							fd_out;
	char						*cmd_path;
	char						**cmd_args;
	char						*save_failed_file;
	char						*heredoc_filename;
	struct s_exec				*next;
}								t_exec;

typedef struct s_tools
{
	t_env						**chl_env;
	char						**arr_env;
	char						*temp_path;
	t_pre_execcmd				*cmd_line;
	t_cmd						*one_cmd;
	t_exec						*exec;
	int							pipes[2][2];
	int							std_io[2];
	int							ig_env;
}								t_tools;

#endif
