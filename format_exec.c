/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:48:51 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 19:42:34 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**count_args(t_pre_execcmd *node)
{
	int					nb;
	char				**cmd_args;
	t_sub_pre_execcmd	*temp;

	cmd_args = NULL;
	nb = 0;
	temp = NULL;
	cmd_args = NULL;
	if (node->argument)
		temp = node->argument;
	while (temp)
	{
		nb++;
		temp = temp->next;
	}
	cmd_args = malloc((nb + 2) * sizeof(char *));
	if (!cmd_args)
	{
		perror("malloc");
		return (NULL);
	}
	return (cmd_args);
}

static char	**get_cmd_args(t_pre_execcmd *node)
{
	int					i;
	char				**cmd_args;
	t_sub_pre_execcmd	*temp;

	i = 1;
	cmd_args = count_args(node);
	if (!cmd_args)
		return (NULL);
	cmd_args[0] = ft_strdup(node->cmd);
	temp = node->argument;
	while (temp)
	{
		cmd_args[i] = ft_strdup(temp->content);
		temp = temp->next;
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

t_exec	*format_exec(t_pre_execcmd *node)
{
	t_exec	*exec;

	if (!node)
		return (NULL);
	exec = malloc(1 * sizeof(t_exec));
	if (!exec)
	{
		perror("malloc");
		return (NULL);
	}
	exec->fd_in = 0;
	exec->fd_out = 1;
	exec->heredoc_filename = NULL;
	exec->save_failed_file = NULL;
	exec->cmd_path = NULL;
	exec->cmd_args = NULL;
	exec->next = NULL;
	if (node->cmd)
		exec->cmd_args = get_cmd_args(node);
	exec->fd_in = open_all_keep_last_in(exec, node);
	exec->fd_out = open_all_keep_last_out(node);
	return (exec);
}

/*I need to cearet a whole linked list of execution,
	so ya ahlouma ya ballouma lets begin*/

int	create_execution_list(t_tools *tools)
{
	t_exec			*new;
	t_exec			*temp;
	t_pre_execcmd	*node;

	temp = NULL;
	if (!tools || !tools->cmd_line)
		return (1);
	node = tools->cmd_line;
	while (node)
	{
		new = format_exec(node);
		if (!(tools->exec))
			tools->exec = new;
		else
		{
			temp = tools->exec;
			while (temp->next)
				temp = temp->next;
			temp->next = new;
		}
		node = node->next;
	}
	free_cmd_line_all(tools);
	tools->cmd_line = NULL;
	return (0);
}
