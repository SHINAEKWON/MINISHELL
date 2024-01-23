/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:05:08 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 19:51:38 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_tools *tools)
{
	t_exec	*temp;
	int		ret;

	ret = 127;
	if (tools->exec)
	{
		temp = tools->exec;
		if (!temp->cmd_args)
		{
			if (temp->save_failed_file)
				return (err_msg_cmd(temp->save_failed_file,
						"no such file or directory",
						EXIT_FAILURE));
		}
		else if (!temp->next && is_built_in(temp->cmd_args[0]) == true)
		{
			save_std_io(tools);
			redirect_io(tools, temp);
			ret = exec_simple_builtin(temp, tools);
			restore_io(tools, temp);
		}
		else
			ret = exec_multi_cmds(tools);
	}
	return (ret);
}

static void	minishell(char *line, t_tools *tools)
{
	int	ret_pars;

	ret_pars = 0;
	ret_pars = ft_parser(line, tools);
	add_history(line);
	if (!ret_pars)
	{
		if (!create_execution_list(tools))
		{
			if (!tools || !tools->exec)
				g_exit_status = EXIT_SUCCESS;
			else
				g_exit_status = execute(tools);
		}
		free_exec(tools->exec);
		tools->exec = NULL;
		tools->cmd_line = NULL;
	}
}

int	minishell_loop(t_tools *tools)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (line)
			free(line);
		line = readline(PROPMPT_MSG);
		if (!line)
			break ;
		else if (line[0] != 0)
			minishell(line, tools);
	}
	return (g_exit_status);
}
