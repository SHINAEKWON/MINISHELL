/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:56:44 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 15:15:19 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_node(char *key, char *value)
{
	t_env	*temp;
	char	*var;

	var = NULL;
	if (key)
		var = ft_strdup(key);
	if (var && value)
		var = ft_strjoin(var, "=");
	if (value)
		var = ft_strjoin(var, value);
	temp = set_env_var(var);
	free(var);
	temp->next = NULL;
	return (temp);
}

static int	insert_node(t_tools *tools, t_env *new)
{
	t_env	*temp;

	if (!tools || !new)
	{
		err_msg_cmd("insert_node", "Invalid arguments", EXIT_FAILURE);
		return (0);
	}
	if (!*(tools->chl_env))
		*(tools->chl_env) = new;
	else
	{
		temp = *tools->chl_env;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return (1);
}

void	add_vars(t_tools *tools)
{
	char	buff[PATH_MAX];
	char	*cwd;

	insert_node(tools, create_node("OLDPWD", NULL));
	cwd = getcwd(buff, PATH_MAX);
	if (!cwd || !insert_node(tools, create_node("PWD", cwd)))
	{
		err_msg_cmd("getcwd", strerror(errno), errno);
		return ;
	}
	if (!insert_node(tools, create_node("SHLVL", "1")))
	{
		err_msg_cmd("insert_node", strerror(errno), errno);
		return ;
	}
	if (!insert_node(tools, create_node("_", "/usr/bin/env")))
	{
		err_msg_cmd("insert_node", strerror(errno), errno);
		return ;
	}
}
