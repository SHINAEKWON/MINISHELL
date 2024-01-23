/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:04:10 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 16:11:13 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_simple_builtin(t_exec *exec, t_tools *tools)
{
	int	ret;

	ret = 127;
	if (exec->save_failed_file)
		return (err_msg_cmd(exec->save_failed_file, "no such file or directory",
				EXIT_FAILURE));
	if (!ft_strncmp("pwd", exec->cmd_args[0], 4))
		ret = built_in_pwd(exec->cmd_args, tools);
	if (!ft_strncmp("cd", exec->cmd_args[0], 3))
		ret = built_in_cd(exec->cmd_args, tools->chl_env);
	if (!ft_strncmp("env", exec->cmd_args[0], 4))
		ret = built_in_env(exec->cmd_args, tools->chl_env);
	if (!ft_strncmp("exit", exec->cmd_args[0], 5))
		ret = built_in_exit(tools, exec->cmd_args);
	if (!ft_strncmp("export", exec->cmd_args[0], 7))
		ret = built_in_export(exec->cmd_args, tools);
	if (!ft_strncmp("echo", exec->cmd_args[0], 5))
		ret = built_in_echo(exec->cmd_args);
	if (!ft_strncmp("unset", exec->cmd_args[0], 6))
		ret = built_in_unset(exec->cmd_args, tools);
	return (ret);
}
