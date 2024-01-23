/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:00:31 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 17:19:39 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_exec1(t_exec *exec)
{
	if (exec)
	{
		if ((exec)->heredoc_filename)
		{
			unlink((exec)->heredoc_filename);
			free(exec->heredoc_filename);
		}
		if (exec->save_failed_file)
			free(exec->save_failed_file);
		free_table(exec->cmd_args);
		if (exec->cmd_path)
			free(exec->cmd_path);
		free(exec);
		exec = NULL;
	}
}

void	free_exec(t_exec *exec)
{
	t_exec	*temp;

	if (exec)
	{
		while (exec)
		{
			temp = exec;
			exec = exec->next;
			free_exec1(temp);
		}
	}
}

static void	free_sub_pre_exec(t_sub_pre_execcmd *sp_cmd)
{
	t_sub_pre_execcmd	*temp;

	while (sp_cmd)
	{
		temp = sp_cmd;
		sp_cmd = sp_cmd->next;
		free(temp->content);
		temp->content = NULL;
		free(temp);
		temp = NULL;
	}
	free(sp_cmd);
	sp_cmd = NULL;
}

static void	free_cmd_line(t_pre_execcmd *node)
{
	if (node)
	{
		if (node->cmd)
			free(node->cmd);
		node->cmd = NULL;
		free_sub_pre_exec(node->argument);
		free_sub_pre_exec(node->redir_in);
		free_sub_pre_exec(node->redir_out);
		free(node);
		node = NULL;
	}
}

void	free_cmd_line_all(t_tools *tools)
{
	t_pre_execcmd	*temp;

	if (tools->cmd_line)
	{
		while (tools->cmd_line)
		{
			temp = tools->cmd_line->next;
			free_cmd_line(tools->cmd_line);
			tools->cmd_line = temp;
		}
		free(tools->cmd_line);
		tools->cmd_line = NULL;
	}
}
