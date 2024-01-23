/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:01:05 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 12:07:27 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	serch for flag -n, ignore all flags -n that come after it, and write
	from first non flag argument till the end"
	
*/

static int	is_nflag(char *arg)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (arg[0] == '-')
	{
		i++;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static int	is_eflag(char *arg)
{
	if (!ft_strncmp(arg, "-e", 3) || !ft_strncmp(arg, "-E", 3))
		return (1);
	return (0);
}

int	built_in_echo(char **cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while ((cmd[i] && (is_nflag(cmd[i]))) || (cmd[i] && is_eflag(cmd[i])))
	{
		if (is_nflag(cmd[i]))
			n_flag = 1;
		i++;
	}
	while (cmd[i])
	{
		if (cmd[i][0] != '\0')
		{
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
			if (cmd[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
