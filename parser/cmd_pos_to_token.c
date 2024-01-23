/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pos_to_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:10:19 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/02 19:37:56 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

t_cmd	*create_token(char *cmd, t_cmdpos **tmp_cmdpos)
{
	t_cmd		*new;
	t_cmdpos	*temp;

	temp = *tmp_cmdpos;
	new = (t_cmd *)malloc(1 * sizeof(t_cmd));
	if (!new || temp->end < temp->start || \
	temp->start > ft_strlen(cmd) - 1 || temp->end > ft_strlen(cmd) - 1)
		return (free(new), NULL);
	new->token = malloc_position(cmd, temp->start, temp->end);
	if (!new->token)
		return (free(new), NULL);
	new->type = 0;
	new->next = NULL;
	return (new);
}

void	insert_token(t_cmd **head, char *cmd, t_cmdpos **tmp_cmdpos)
{
	t_cmd		*new;
	t_cmd		*current;
	t_cmdpos	*temp;

	temp = *tmp_cmdpos;
	new = create_token(cmd, &temp);
	if (!new || !head)
		return ;
	if (!(*head))
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

t_cmd	*cmd_pos_to_token(char *malloc_cmd, t_cmdpos *cmd_pos)
{
	t_cmd		*spl;
	t_cmd		*trimmed;
	t_cmdpos	*tmp_cmdpos;

	tmp_cmdpos = cmd_pos;
	spl = NULL;
	trimmed = spl;
	while (tmp_cmdpos != NULL)
	{
		insert_token(&spl, malloc_cmd, &tmp_cmdpos);
		tmp_cmdpos = tmp_cmdpos->next;
	}
	return (spl);
}
