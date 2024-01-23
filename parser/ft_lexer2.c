/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 22:06:28 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 19:35:15 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

void	rest_are_word(t_cmd **curr, t_tools *tools)
{
	t_cmd	*current;

	current = *curr;
	if (current->type != UNPARSED)
		return ;
	current->type = WORD;
	if (current->type == WORD)
		envvar_parser(&current, tools);
}

void	find_cmd(t_cmd **curr)
{
	t_cmd	*current;
	bool	cmd_in_exec;

	current = *curr;
	cmd_in_exec = 0;
	while (current != NULL)
	{
		if (current->type == WORD && !cmd_in_exec)
		{
			current->type = CMD;
			cmd_in_exec = 1;
		}
		else if (current->type == PIPE)
			cmd_in_exec = 0;
		current = current->next;
	}
}
