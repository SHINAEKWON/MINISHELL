/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:52:54 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 12:08:09 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_env(char **cmd_args, t_env **chl_env)
{
	t_env	*tmp;

	(void)cmd_args;
	if (cmd_args && cmd_args[1])
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	tmp = *chl_env;
	while (tmp)
	{
		if (strchr(tmp->k_eq_v, '='))
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
