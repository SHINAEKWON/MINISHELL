/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:06:37 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 18:31:31 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipes(t_tools *tools, t_exec *exec, int i)
{
	if (exec->next)
	{
		if (pipe(tools->pipes[i % 2]) == -1)
		{
			return (err_msg_cmd("pipe", strerror(errno), errno));
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	ex(t_tools *tools)
{
	int		i;
	t_exec	*exec;
	pid_t	last_pid;

	i = 0;
	exec = tools->exec;
	while (exec)
	{
		if (create_pipes(tools, exec, i))
			return (EXIT_FAILURE);
		last_pid = fork();
		if (last_pid == -1)
			return (err_msg_cmd("fork", strerror(errno), EXIT_FAILURE));
		if (!last_pid)
			exec_child(tools, exec, i);
		else
		{
			close_pipes(tools, exec, i);
			ft_close(&exec->fd_in);
			ft_close(&exec->fd_out);
			exec = exec->next;
			i++;
		}
	}
	return (exit_status(last_pid));
}

int	exec_multi_cmds(t_tools *tools)
{
	init_pipes(tools);
	return (ex(tools));
}

void	exec_simple_cmd(t_exec *exec, t_tools *tools)
{
	if (execve(exec->cmd_path, exec->cmd_args, tools->arr_env) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(exec->cmd_args[0]);
		ft_exit(tools, 127);
	}
}

/*
	void inc_shelvl()
	{
		char *cmd_args[3]
		
		cmd_args[0] = ft_strdup(export);
		SHLVL=2\0
		cmd_args[1] = ft_calloc(7*sizeof(char))
		cmd_args[1][6] = 1;
		cmd_args[2] = NULL;
		built_in_export(cmd_args, tools);
	}

	void dec_shelvl()
	{
		char *cmd_args[3]
		
		cmd_args[0] = ft_strdup(export);
		SHLVL=2\0
		cmd_args[1] = ft_calloc(7*sizeof(char))
		cmd_args[1][6] = -1??;
		cmd_args[2] = NULL;
		
		cmd_args[1] = tools->chl_env->k_eq_v + ft_itoa(-1);
		built_in_export(cmd_args, tools);
	}
*/