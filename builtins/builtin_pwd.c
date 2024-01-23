/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:51:41 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 14:12:05 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_pwd(char **cmd_args, t_tools *tools)
{
	int		ret;
	char	*cwd;
	char	buff[PATH_MAX];

	(void)tools;
	ret = invalid_option(cmd_args[1]);
	if (ret)
		return (ret);
	cwd = getcwd(buff, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("getcwd()");
		return (EXIT_FAILURE);
	}
}
