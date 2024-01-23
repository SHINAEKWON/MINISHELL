/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:21:46 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 12:40:20 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../libft/libft.h"
#include "../minishell.h"

/*exit function shall cause the shell to exit from its current environment*/
/*exit status : 
	1- n if specified [n] is unsigned decimal integer
	2- undefined if specified [n] is not unsigned integer or > 255
	3- the exit value of the last command executed 
	4- 0 if no command was executed
	5- NOT SO CLEAR 
	5- hen exit is executed
       in a trap action, the last command is considered to be the command that
		executed  immediately preceding the trap action.
	*/
static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_number(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (is_digit(*str))
			str++;
		else
			return (0);
	}
	return (1);
}

static long long	ft_atoi_exit(t_tools *tools, const char *nptr)
{
	int					i;
	unsigned long long	nb;
	int					neg;

	i = 0;
	nb = 0;
	neg = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			neg *= -1;
	nb = 0;
	while (is_digit(nptr[i]))
	{
		nb = (nb * 10) + (nptr[i++] - 48);
		if ((nb > LLONG_MAX && neg > 0) || (neg < 0 && (long long)(nb
				* neg) < LLONG_MIN))
		{
			err_msg_exit("exit: ", (char *)nptr, ": numeric argument required",
				2);
			ft_exit(tools, 2);
		}
	}
	return (nb * neg);
}

static int	do_exit(t_tools *tools, char **cmd)
{
	long long	n;

	n = ft_atoi_exit(tools, cmd[1]) % 256;
	if (n < 0)
	{
		n *= -1;
		if (n < 256)
			n = 256 - n;
	}
	ft_exit(tools, n);
	return (n);
}

int	built_in_exit(t_tools *tools, char **cmd)
{
	if (!cmd[1])
	{
		ft_putstr_fd("exit\n", 1);
		ft_exit(tools, 0);
	}
	if (cmd[1])
	{
		if (!is_number(cmd[1]))
		{
			err_msg_exit("exit: ", cmd[1], ": numeric argument required", 2);
			ft_exit(tools, 2);
		}
	}
	if (cmd[2])
		return (err_msg_cmd("exit", "too many arguments", 1));
	else
		return (do_exit(tools, cmd));
}
