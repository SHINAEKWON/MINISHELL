/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:10:06 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 14:36:11 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env *node)
{
	if (node)
	{
		free((node)->key);
		free((node)->value);
		free((node)->k_eq_v);
		free(node);
		node = NULL;
	}
}

void	free_env_list(t_env **env)
{
	t_env	*tmp;

	if (env)
	{
		while (*env)
		{
			tmp = *env;
			*env = (*env)->next;
			free_env_node(tmp);
		}
		free(env);
		env = NULL;
	}
}

void	free_table(char **tab)
{
	int	i;

	if (tab)
	{
		if (*tab)
		{
			i = 0;
			while (tab[i])
			{
				free(tab[i]);
				tab[i] = NULL;
				i++;
			}
		}
		free(tab);
	}
	tab = NULL;
}

void	free_tools(t_tools *tools)
{
	if (tools)
	{
		if (tools->chl_env)
			free_env_list(tools->chl_env);
		if (tools->arr_env)
			free_table(tools->arr_env);
		if (tools->exec)
			free_exec(tools->exec);
		if (tools->cmd_line)
			free_cmd_line_all(tools);
		free(tools);
	}
	tools = NULL;
}
