/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:54:37 by anouri            #+#    #+#             */
/*   Updated: 2023/12/01 14:59:05 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirect_io(t_tools *tools, t_exec *exec)
{
	if (exec->fd_in > 2)
	{
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (false);
		}
	}
	else
		ft_close(&tools->std_io[0]);
	if (exec->fd_out > 2)
	{
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (false);
		}
	}
	else
		ft_close(&(tools->std_io[1]));
	return (true);
}

bool	restore_io(t_tools *tools, t_exec *exec)
{
	if (exec->fd_in > 2)
	{
		if (dup2(tools->std_io[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (false);
		}
		ft_close(&exec->fd_in);
		ft_close(&tools->std_io[0]);
	}
	if (exec->fd_out > 2)
	{
		if (dup2(tools->std_io[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (false);
		}
		ft_close(&exec->fd_out);
		ft_close(&tools->std_io[1]);
	}
	return (true);
}

bool	save_std_io(t_tools *tools)
{
	tools->std_io[0] = dup(STDIN_FILENO);
	tools->std_io[1] = dup(STDOUT_FILENO);
	return (true);
}
