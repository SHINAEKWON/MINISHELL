/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 22:06:28 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 17:47:18 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

static void	pipe_checker(t_cmd **curr, size_t len)
{
	t_cmd	*current;

	current = *curr;
	if (current->type != UNPARSED)
		return ;
	if (ft_strncmp(current->token, "|", len) == 0)
		current->type = PIPE;
}

static void	input_and_output(t_cmd **cur, t_cmd **prev, size_t len)
{
	t_cmd	*current;
	t_cmd	*previous;

	current = *cur;
	previous = *prev;
	if (current->type != UNPARSED)
		return ;
	if (!ft_strncmp(current->token, "<", len))
		current->type = REDIR_INPUT;
	else if (!ft_strncmp(current->token, ">", len))
		current->type = REDIR_OUTPUT;
	else if (!ft_strncmp(current->token, "<<", len))
		current->type = HEREDOC;
	else if (!ft_strncmp(current->token, ">>", len))
		current->type = REDIR_OUTPUT_APPEND;
	else if (previous->type == REDIR_INPUT)
		current->type = INPUT_FILE;
	else if (previous->type == REDIR_OUTPUT)
		current->type = OUTPUT_FILE;
	else if (previous->type == REDIR_OUTPUT_APPEND)
		current->type = OUTPUT_FILE_APPEND;
	else if (previous->type == HEREDOC)
		current->type = HEREDOC_DELIM;
}

void	ft_lexer(t_cmd **cmd, t_tools *tools)
{
	t_cmd	*current;
	t_cmd	*previous;
	t_cmd	*head;
	size_t	len;

	current = *cmd;
	previous = current;
	head = *cmd;
	len = 0;
	while (current != NULL)
	{
		if (current->type == UNPARSED)
		{
			len = ft_strlen(current->token);
			input_and_output(&current, &previous, len);
			pipe_checker(&current, len);
			rest_are_word(&current, tools);
		}
		current->previous = previous;
		previous = current;
		current = current->next;
	}
	find_cmd(&head);
}
