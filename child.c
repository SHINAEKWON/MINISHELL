/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:16:35 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 18:31:11 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_all(t_tools *tools, t_exec *temp, int i)
{
	t_exec	*ex;

	ex = tools->exec;
	while (ex)
	{
		ft_close(&ex->fd_in);
		ft_close(&ex->fd_out);
		ex = ex->next;
	}
	ft_close(&tools->pipes[(i + 1) % 2][0]);
	ft_close(&tools->pipes[(i + 1) % 2][1]);
	ft_close(&tools->pipes[i % 2][0]);
	ft_close(&tools->pipes[i % 2][1]);
	ft_close(&temp->fd_in);
	ft_close(&temp->fd_out);
}

static void	ft_redir_pipe(t_tools *tools, t_exec *temp, int i)
{
	if (!i)
	{
		if (dup2(tools->pipes[i][1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
	else if (i)
	{
		if (dup2(tools->pipes[(i + 1) % 2][0], STDIN_FILENO) < 0)
			perror("dup2");
	}
	if (temp->next)
	{
		if (dup2(tools->pipes[i % 2][1], STDOUT_FILENO) < 0)
			perror("dup2");
	}
}

static void	ft_redir_files(t_exec *temp)
{
	if (temp->save_failed_file)
	{
		err_msg_cmd(temp->save_failed_file, "no such file or directory", errno);
		exit(EXIT_FAILURE);
	}
	if (temp->fd_in > 2)
	{
		if (dup2(temp->fd_in, STDIN_FILENO) == -1)
			perror("dup2");
	}
	if (temp->fd_out > 2)
	{
		if (dup2(temp->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
	}
}

static void	ex_with_path(t_exec *temp, t_tools *tools)
{
	{
		temp->cmd_path = get_absolute_path(temp->cmd_args, tools);
		if (!temp->cmd_path)
		{
			err_msg_cmd(temp->cmd_args[0], "command not found", 127);
			ft_exit(tools, 127);
		}
		exec_simple_cmd(temp, tools);
		ft_exit(tools, EXIT_SUCCESS);
	}
}

void	exec_child(t_tools *tools, t_exec *temp, int i)
{
	ft_redir_pipe(tools, temp, i);
	if (!temp->cmd_args || temp->cmd_args[0][0] == '\0')
	{
		if (temp->save_failed_file)
			ft_exit(tools, (err_msg_cmd(temp->save_failed_file,
						"no such file or directory", EXIT_FAILURE)));
		ft_exit(tools, EXIT_SUCCESS);
	}
	ft_redir_files(temp);
	close_all(tools, temp, i);
	if (is_built_in(temp->cmd_args[0]) == true)
	{
		exec_simple_builtin(temp, tools);
		ft_exit(tools, EXIT_SUCCESS);
	}
	else
		ex_with_path(temp, tools);
}
