/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:26:26 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 19:54:25 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

# define ERROR 1
# define SUCCESS 0

/************ TOKENIZATION ***********/
void			ft_print_cmd(t_cmd *cmd);
void			free_parsed_cmd(t_cmd *to_free);
void			ft_lexer(t_cmd **cmd, t_tools *tools);
void			rest_are_word(t_cmd **curr, t_tools *tools);
void			find_cmd(t_cmd **curr);
t_cmdpos		*cmd_tokenizer(char *cmd, const char delim);
t_cmdpos		*cmd_tokenizer_loop(t_cmdpos_elem **elem, char *cmd);
void			check_start_pos(t_cmdpos_elem ***elem1, size_t *i);
void			bracket_seperation(char *cmd, t_cmdpos **cmd_pos, size_t *i,
					size_t *start_pos);
void			insert_cmdpos(t_cmdpos **head, size_t start_pos, size_t i);
bool			is_db_spc(char *cmd, size_t i);
bool			not_in_quotes(t_cmdpos_elem **elem);
int				ft_parser(char *cmd, t_tools *tools);
t_cmd			*cmd_pos_to_token(char *malloc_cmd, t_cmdpos *cmd_pos);
int				this_exec_exists(char *line, t_tools *tools);
bool			builtin_checker(char *token);
void			clean_token(t_cmd **spl);

/************ SYNTAX ERRORS ***********/
bool			open_quote_finder(char *token);
int				three_bracket_checker(char *cmd);
bool			syntax_ruban(char *cmd);
bool			syntax_diamond(char *cmd);
bool			syntax_big_diamond(char *cmd);
bool			syntax_pipe_start_end(char *cmd);
bool			syntax_consec_pipe(char *cmd);
bool			syntax_end_with_bracket(char *cmd);
bool			syntax_dot(char *cmd);

/********* ENVIRONMENT VARIABLE MANAGEMENT *********/

/************* QUOTE REMOVER *********/
void			quote_remover(t_cmd **cmd);

/*********** PARSING FOR PRE_EXEC_COMMAND **********/

t_pre_execcmd	*parser_pre_exec(t_cmd *splcmd);
void			pre_execcmd_init(t_pre_execcmd **cmd);

/************* UTILS ************/

char			*malloc_position(char *str, int start, int end);
void			remove_quotes(t_cmd **curr);
void			quote_init(t_quote **quote);
void			quote_toggler(char c, bool *in_sq, bool *in_dq);
void			pre_execcmd_init(t_pre_execcmd **cmd);
void			sub_pre_execcmd_init2(t_sub_pre_execcmd **spec);
bool			exit_status_exists(char *token, size_t i);
void			free_cmdpos(t_cmdpos *to_free);

/*********** PRINT RESULT **********/
void			print_pre_execcmd(t_pre_execcmd *reparsed);
void			print_sub_pre_execcmd(t_sub_pre_execcmd *sub);
void			ft_print_cmd(t_cmd *cmd);

/**********newenvar parser (to be polished later)*******/
void			envvar_parser(t_cmd **curr, t_tools *tools);
t_envvar_elem	*translation_elem(char *str, t_env *env_chl);
char			*envvar_elem_join(t_envvar_elem *translated);
t_envvar_elem	*translation_envvar(char **currtoken, t_env *env_chl);
void			translation_loop(char *token, t_env *env_chl, t_quote *quote,
					t_envvar_elem **ev);
t_envvar_elem	*new_envvar_elem(void);
void			put_value_if_key_exists(char *token, size_t *i,
					t_envvar_elem **envvar_param, t_env *env_chl);
void			put_this_text(char *token, size_t *i, t_envvar_elem **envvar,
					t_quote **quote);
bool			valid_envvar(char *str, size_t i);
void			put_text_between_sq(char *token, size_t *i,
					t_envvar_elem **envvar);
void			putchar_and_see(char *token, size_t *i, t_envvar_elem **envvar);
char			*generate_uid(t_env *env_chl);
bool			exit_status_exists(char *token, size_t i);

#endif