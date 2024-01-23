/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pre_exec2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:20:44 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/01 19:37:42 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

void	sub_pre_execcmd_init(t_sub_pre_execcmd ***spec)
{
	t_sub_pre_execcmd	*current;

	current = **spec;
	current->content = NULL;
	current->type = 0;
	current->next = NULL;
	current = current->next;
}

void	sub_pre_execcmd_init2(t_sub_pre_execcmd **spec)
{
	t_sub_pre_execcmd	*current;

	current = *spec;
	current->content = NULL;
	current->type = 0;
	current->next = NULL;
}

void	pre_execcmd_init(t_pre_execcmd **cmd)
{
	t_pre_execcmd	*current;

	if (cmd == NULL || *cmd == NULL)
		return ;
	current = *cmd;
	while (current != NULL)
	{
		current->cmd = NULL;
		current->redir_in = NULL;
		current->redir_out = NULL;
		current->argument = NULL;
		current->next = NULL;
		current = current->next;
	}
}
