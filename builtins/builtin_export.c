/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:53:04 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 17:46:42 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*in minishell subject export is used with no option
use : export name[=word]
*/

#include "../minishell.h"

void	update_arr_env(t_tools *tools)
{
	int		len;
	t_env	*tmp;
	int		i;

	tmp = *(tools->chl_env);
	len = 0;
	while (tmp)
	{
		len++;
		tmp = (tmp)->next;
	}
	free_table(tools->arr_env);
	tools->arr_env = malloc((len + 1) * sizeof(char *));
	if (!tools->arr_env)
		return ;
	i = 0;
	tmp = *(tools->chl_env);
	while (tmp)
	{
		tools->arr_env[i] = ft_strdup((tmp)->k_eq_v);
		i++;
		tmp = (tmp)->next;
	}
	tools->arr_env[i] = NULL;
}

void	update_chl_env(t_tools *tools, t_env *env_node)
{
	t_env	*tmp_env;
	t_env	*to_be_replaced;

	tmp_env = *tools->chl_env;
	while (tmp_env->next)
	{
		if (!ft_strncmp(tmp_env->next->key, env_node->key,
				ft_strlen(tmp_env->next->key)))
		{
			to_be_replaced = tmp_env->next;
			tmp_env->next = env_node;
			env_node->next = to_be_replaced->next;
			return ;
		}
		else
			tmp_env = tmp_env->next;
	}
	if (!tmp_env->next)
		tmp_env->next = env_node;
}

t_env	*set_env_var(char *cmd_arg)
{
	t_env	*env_node;
	int		i;
	int		j;

	env_node = NULL;
	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (0);
	env_node->k_eq_v = ft_strdup(cmd_arg);
	i = 0;
	while (cmd_arg[i] && cmd_arg[i] != '=')
		i++;
	env_node->key = ft_substr(env_node->k_eq_v, 0, i);
	if (cmd_arg[i] == '\0')
		env_node->value = NULL;
	else if (cmd_arg[i] == '=')
	{
		j = i + 1;
		while (cmd_arg[i])
			i++;
		env_node->value = ft_substr(env_node->k_eq_v, j, i - j);
	}
	env_node->next = NULL;
	return (env_node);
}

/*	return 0 if all variables are added 
	returns 1 if at least one fails*/

static void	complex_export(char *cmd_args, t_tools *tools)
{
	t_env	*env_node;

	env_node = set_env_var(cmd_args);
	update_chl_env(tools, env_node);
	update_arr_env(tools);
}

int	built_in_export(char **cmd_args, t_tools *tools)
{
	int	k;
	int	ret;
	int	ret1;

	k = 1;
	ret1 = 0;
	ret = EXIT_SUCCESS;
	if (!cmd_args[k])
		return (simple_export(tools));
	while (cmd_args[k])
	{
		ret = invalid_option(cmd_args[k]);
		if (ret)
			return (ret);
		if (!is_valid_var(cmd_args[k]))
			ret1 = err_msg("export", cmd_args[k], " : not a valid identifier",
					EXIT_FAILURE);
		else
			complex_export(cmd_args[k], tools);
		k++;
	}
	if (ret1 != 0)
		return (ret1);
	return (ret);
}
