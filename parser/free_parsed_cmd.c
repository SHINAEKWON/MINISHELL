/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsed_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:16:36 by shikwon           #+#    #+#             */
/*   Updated: 2023/10/21 13:43:25 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

void	free_parsed_cmd(t_cmd *to_free)
{
	t_cmd	*current;
	t_cmd	*temp;

	current = to_free;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->token);
		free(temp);
	}
}
