/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:51:31 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/02 19:36:08 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

bool	is_db_spc(char *cmd, size_t i)
{
	return (ft_isspace(cmd[i]) && ft_isspace(cmd[i + 1]));
}

bool	not_in_quotes(t_cmdpos_elem **elem)
{
	return (!(*elem)->in_sq && !(*elem)->in_dq);
}

void	check_start_pos(t_cmdpos_elem ***elem1, size_t *i)
{
	t_cmdpos_elem	*elem;

	elem = **elem1;
	if (elem->started == 0)
	{
		elem->start_pos = *i;
		elem->started = 1;
	}
}

void	free_cmdpos(t_cmdpos *to_free)
{
	t_cmdpos	*temp;
	t_cmdpos	*current;

	current = to_free;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}
