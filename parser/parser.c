/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:14:27 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 19:41:49 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/structures.h"
#include "../minishell.h"

int	syntax_check(char *cmd)
{
	if (!cmd)
		return (ERROR);
	else if (three_bracket_checker(cmd))
		return (err_msg_cmd(NULL, "syntax error near unexpected tokeechon `>'", \
		EXIT_FAILURE));
	else if (open_quote_finder(cmd))
		return (err_msg_cmd(NULL, "syntax error with unclosed quotes", \
		EXIT_FAILURE));
	else if (syntax_ruban(cmd))
		return (err_msg_cmd(NULL, "syntax error near unexpected token `<'", \
		EXIT_FAILURE));
	else if (syntax_diamond(cmd) || syntax_end_with_bracket(cmd))
		return (err_msg_cmd(NULL, "syntax error near unexpected token \
		`newline'", EXIT_FAILURE));
	else if (syntax_big_diamond(cmd))
		return (err_msg_cmd(NULL, "syntax error near unexpected token `>'", \
		EXIT_FAILURE));
	else if (syntax_pipe_start_end(cmd) || syntax_consec_pipe(cmd))
		return (err_msg_cmd(NULL, "syntax error near unexpected token `|'", \
		EXIT_FAILURE));
	else if (syntax_dot(cmd))
		return (err_msg_cmd(NULL, "bash: .: filename argument required\n.: \
		usage: . filename [arguments]", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	ft_parser(char *cmd, t_tools *tools)
{
	char		*malloc_cmd;
	t_cmd		*spl_cmd;
	t_cmdpos	*cmdpos;
	char		*temp_cmd;

	if (syntax_check(cmd) == EXIT_FAILURE)
		return (ERROR);
	temp_cmd = ft_strtrim(cmd, " ");
	malloc_cmd = ft_strdup(temp_cmd);
	free(temp_cmd);
	cmdpos = cmd_tokenizer(malloc_cmd, ' ');
	spl_cmd = cmd_pos_to_token(malloc_cmd, cmdpos);
	if (!spl_cmd)
		return (ERROR);
	free(malloc_cmd);
	free_cmdpos(cmdpos);
	ft_lexer(&spl_cmd, tools);
	tools->cmd_line = parser_pre_exec(spl_cmd);
	free_parsed_cmd(spl_cmd);
	return (SUCCESS);
}
