/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:32:44 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 14:32:58 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free(tmp);
	return (str);
}

int	err_msg_cmd(char *cmd, char *detail, int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = join_strs(msg, cmd);
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, detail);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (error_nb);
}

int	err_msg_exit(char *cmd, char *detail1, char *detail2, int error_nb)
{
	char	*msg;

	ft_putstr_fd("exit\n", 2);
	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = join_strs(msg, cmd);
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, detail1);
	msg = join_strs(msg, detail2);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (error_nb);
}

int	invalid_option(char *cmd_arg)
{
	int		ret;
	char	*err;

	if (cmd_arg && (ft_strncmp(cmd_arg, "--", 3)) && (cmd_arg[0] == '-'
			&& cmd_arg[1] != '\0'))
	{
		err = ft_substr(cmd_arg, 0, 2);
		ret = err_msg_cmd(err, ": invalid option", 2);
		free(err);
		return (ret);
	}
	return (0);
}

int	err_msg(char *cmd, char *detail1, char *detail2, int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = join_strs(msg, cmd);
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, detail1);
	msg = join_strs(msg, detail2);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (error_nb);
}
