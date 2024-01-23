/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_restricted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:30:18 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 15:15:52 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*in case of env -i, minishell created its one restricted en containg : */
/*
	if (!envp)
	create the three environment variables
		PWD=/mnt/nfs/homes/anouri
		SHLVL=1
	_	=/usr/bin/env
	*/
static void	create_list(t_tools *tools)
{
	tools->chl_env = malloc(sizeof(t_env *));
	if (!tools->chl_env)
	{
		err_msg_cmd("malloc", strerror(errno), errno);
		return ;
	}
	*(tools->chl_env) = NULL;
	add_vars(tools);
}

static void	create_array(t_tools *tools)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = *tools->chl_env;
	tools->arr_env = malloc(5 * sizeof(char *));
	if (!tools->arr_env)
		err_msg_cmd("malloc", strerror(errno), EXIT_FAILURE);
	while (temp)
	{
		tools->arr_env[i] = ft_strdup(temp->k_eq_v);
		temp = temp->next;
		i++;
	}
	tools->arr_env[i] = NULL;
}

int	create_restricted_env(t_tools *tools)
{
	create_list(tools);
	create_array(tools);
	return (0);
}
