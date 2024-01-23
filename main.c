/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:56:57 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 15:16:38 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

void	init_tools(t_tools *tools, char *envp[])
{
	tools->arr_env = NULL;
	(tools->chl_env) = NULL;
	if (!envp || !envp[0])
	{
		tools->ig_env = 1;
		create_restricted_env(tools);
	}
	else
	{
		tools->ig_env = 0;
		tools->chl_env = cpy_chl_env(envp);
		tools->arr_env = cpy_arr_env(envp);
	}
	tools->temp_path = NULL;
	tools->exec = NULL;
	tools->cmd_line = NULL;
}

// if (isatty(STDERR_FILENO))
// 	return(printf("bash: echo: write error: No space left on device"));

int	main(int argc, char *argv[], char *envp[])
{
	t_tools	*tools;

	tools = malloc(1 * sizeof(t_tools));
	if (!tools)
		return (err_msg_cmd("malloc", strerror(errno), errno));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_ctrlc);
	if (argc != 1 || argv[1])
	{
		printf(ERR_ARGS);
		exit(0);
	}
	init_tools(tools, envp);
	minishell_loop(tools);
	free_tools(tools);
}
