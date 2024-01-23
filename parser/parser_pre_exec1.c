/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pre_exec1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:20:44 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 19:46:08 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

static void	set_type_put_at_end(int *type, t_sub_pre_execcmd **current, \
t_sub_pre_execcmd **new)
{
	if (*type)
		(*new)->type = 1;
	while ((*current)->next != NULL)
		(*current) = (*current)->next;
	(*current)->next = *new;
}

void	add_sub_pre_execcmd(t_sub_pre_execcmd **sub_element, \
char *input, int type)
{
	t_sub_pre_execcmd	*new;
	t_sub_pre_execcmd	*current;

	current = NULL;
	new = (t_sub_pre_execcmd *)malloc(1 * sizeof(t_sub_pre_execcmd));
	sub_pre_execcmd_init2(&new);
	if (type == 0)
		(void)type;
	if (!new)
		return (free(new));
	if (*sub_element == NULL)
	{
		*sub_element = new;
		new->content = ft_strdup(input);
		if (type)
			new->type = 1;
	}
	else
	{
		current = *sub_element;
		new->content = ft_strdup(input);
		set_type_put_at_end(&type, &current, &new);
	}
	new->next = NULL;
}

static void	parser_pre_exec_continue(t_cmd **splcmd_input, \
t_pre_execcmd **reparsed_input)
{
	t_cmd			*splcmd;
	t_pre_execcmd	*reparsed;

	splcmd = *splcmd_input;
	reparsed = *reparsed_input;
	if (splcmd->type == CMD)
		reparsed->cmd = ft_strdup(splcmd->token);
	else if (splcmd->type == WORD || splcmd->type == SQ || splcmd->type == DQ)
		add_sub_pre_execcmd(&(reparsed->argument), splcmd->token, 0);
	else if (splcmd->type == HEREDOC_DELIM)
		add_sub_pre_execcmd(&(reparsed->redir_in), splcmd->token, 1);
	else if (splcmd->type == INPUT_FILE)
		add_sub_pre_execcmd(&(reparsed->redir_in), splcmd->token, 0);
	else if (splcmd->type == OUTPUT_FILE)
		add_sub_pre_execcmd(&(reparsed->redir_out), splcmd->token, 0);
	else if (splcmd->type == OUTPUT_FILE_APPEND)
		add_sub_pre_execcmd(&(reparsed->redir_out), splcmd->token, 1);
}

static void	parser_pre_exec_null(t_pre_execcmd **reparsed, t_pre_execcmd **head)
{
	*reparsed = NULL;
	*head = NULL;
}

t_pre_execcmd	*parser_pre_exec(t_cmd *splcmd)
{
	t_pre_execcmd	*reparsed;
	t_pre_execcmd	*head;

	parser_pre_exec_null(&reparsed, &head);
	pre_execcmd_init(&reparsed);
	while (splcmd != NULL)
	{
		if (reparsed == NULL)
		{
			reparsed = (t_pre_execcmd *)malloc(1 * sizeof(t_pre_execcmd));
			pre_execcmd_init(&reparsed);
			head = reparsed;
		}
		if (splcmd->type == PIPE)
		{
			reparsed->next = (t_pre_execcmd *)malloc(1 * sizeof(t_pre_execcmd));
			pre_execcmd_init(&reparsed->next);
			reparsed = reparsed->next;
		}
		else
			parser_pre_exec_continue(&splcmd, &reparsed);
		splcmd = splcmd->next;
	}
	reparsed->next = NULL;
	return (head);
}
