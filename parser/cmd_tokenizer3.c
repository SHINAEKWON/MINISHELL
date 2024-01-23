/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:21:13 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/02 19:35:16 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

void	process_space_character(t_cmdpos_elem **elem, \
t_cmdpos **cmd_pos, size_t i)
{
	if ((*elem)->start_pos <= i - 1)
		insert_cmdpos(cmd_pos, (*elem)->start_pos, (i - 1));
	(*elem)->started = 0;
}

void	process_pipe_character(t_cmdpos_elem **elem, \
t_cmdpos **cmd_pos, size_t i)
{
	insert_cmdpos(cmd_pos, (*elem)->start_pos, i - 1);
	(*elem)->start_pos = i;
	insert_cmdpos(cmd_pos, (*elem)->start_pos, i);
	(*elem)->started = 0;
}

void	process_pipe2(t_cmdpos_elem **elem, t_cmdpos **cmd_pos, size_t i)
{
	insert_cmdpos(cmd_pos, (*elem)->start_pos, i);
	(*elem)->started = 0;
}

void	process_bracket_character(t_cmdpos_elem **elem, t_cmdpos **cmd_pos, \
char *cmd, size_t *i)
{
	bracket_seperation(cmd, cmd_pos, i, &(*elem)->start_pos);
	(*elem)->started = 0;
}

t_cmdpos	*cmd_tokenizer_loop(t_cmdpos_elem **elem, char *cmd)
{
	t_cmdpos	*cmd_pos;
	size_t		i;

	cmd_pos = NULL;
	i = 0;
	while (cmd[i])
	{
		check_start_pos(&elem, &i);
		if ((cmd[i] == '\'') || cmd[i] == '\"')
			quote_toggler(cmd[i], &(*elem)->in_sq, &(*elem)->in_dq);
		else if (cmd[i] == ' ' && not_in_quotes(elem) && (*elem)->started)
			process_space_character(elem, &cmd_pos, i);
		else if (is_db_spc(cmd, i) && not_in_quotes(elem) && (*elem)->started)
			(*elem)->start_pos = i;
		else if (cmd[i] == '|' && !(*elem)->in_sq && !(*elem)->in_dq)
			process_pipe_character(elem, &cmd_pos, i);
		if (cmd[i + 1] == '|' && not_in_quotes(elem) && (*elem)->started)
			process_pipe2(elem, &cmd_pos, i);
		else if ((cmd[i] == '>' || cmd[i] == '<') && not_in_quotes(elem))
			process_bracket_character(elem, &cmd_pos, cmd, &i);
		i++;
	}
	if (cmd[i] == '\0')
		insert_cmdpos(&cmd_pos, (*elem)->start_pos, (i - 1));
	return (cmd_pos);
}
