/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:51:31 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 19:45:29 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

t_cmdpos	*create_cmdpos(size_t start_pos, size_t i)
{
	t_cmdpos	*new;

	new = (t_cmdpos *)malloc(1 * sizeof(t_cmdpos));
	if (!new)
		return (free(new), NULL);
	new->start = start_pos;
	new->end = i;
	new->next = NULL;
	return (new);
}

void	insert_cmdpos(t_cmdpos **head, size_t start_pos, size_t i)
{
	t_cmdpos	*new;
	t_cmdpos	*current;

	new = create_cmdpos(start_pos, i);
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	bracket_seperation(char *cmd, t_cmdpos **cmd_pos, \
size_t *i, size_t *start_pos)
{
	char	ref;

	ref = cmd[*i];
	if (*start_pos <= *i - 1)
		insert_cmdpos(&(*cmd_pos), *start_pos, *i - 1);
	*start_pos = *i;
	if (cmd[*i + 1] && cmd[*i + 1] == ref)
	{
		while (cmd[*i] && cmd[*i + 1] == ref)
		{
			(*i)++;
			if (cmd[*i + 1] != ref)
				insert_cmdpos(&(*cmd_pos), *start_pos, *i);
		}
	}
	else
		insert_cmdpos(&(*cmd_pos), *start_pos, *i);
}

void	cmd_tokenizer_elem_init(t_cmdpos_elem **elem)
{
	*elem = (t_cmdpos_elem *)malloc((sizeof(t_cmdpos_elem) * 1));
	(*elem)->in_dq = 0;
	(*elem)->in_sq = 0;
	(*elem)->started = 0;
	(*elem)->start_pos = 0;
}

t_cmdpos	*cmd_tokenizer(char *cmd, const char delim)
{
	t_cmdpos_elem	*elem;
	t_cmdpos		*cmd_pos;

	(void)delim;
	cmd_tokenizer_elem_init(&elem);
	cmd_pos = cmd_tokenizer_loop(&elem, cmd);
	free(elem);
	return (cmd_pos);
}
